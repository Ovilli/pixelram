#!/usr/bin/env python3
from pathlib import Path
import sys
root=Path(sys.argv[1]); p=root/'src/menu.c'; s=p.read_text()
inc='#ifdef __EMSCRIPTEN__\n#include <emscripten/emscripten.h>\n#endif\n'
if inc not in s: s=s.replace('#include "common.h"\n','#include "common.h"\n'+inc,1)
sig='void read_mouse_state(void)'; start=s.find(sig); brace=s.find('{',start); depth=0; end=None
for i in range(brace,len(s)):
    if s[i]=='{': depth+=1
    elif s[i]=='}':
        depth-=1
        if depth==0: end=i+1; break
if start<0 or end is None: raise RuntimeError('read_mouse_state not found')
old=s[start:end]
if 'PIXELRAM_POINTER_X' not in old:
    native=old[old.find('{')+1:-1]
    web='''\n#ifdef __EMSCRIPTEN__\n    int last_mouse_x = mouse_x, last_mouse_y = mouse_y;\n    mouse_x = EM_ASM_INT({ return Number.isFinite(window.PIXELRAM_POINTER_X) ? window.PIXELRAM_POINTER_X : 0; });\n    mouse_y = EM_ASM_INT({ return Number.isFinite(window.PIXELRAM_POINTER_Y) ? window.PIXELRAM_POINTER_Y : 0; });\n    mouse_moved = (last_mouse_x != mouse_x || last_mouse_y != mouse_y);\n#else'''
    s=s[:start]+sig+' {'+web+native+'\n#endif\n}'+s[end:]
p.write_text(s)
