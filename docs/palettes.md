---
title: Palettes
layout: page
nav_order: 2
---

# Palettes

PixelRAM contains the same predefined palette collection as Pixelflow Canvas. The default is `vga`. A named palette replaces all 256 entries; unused entries become black.

```c
use_palette("aap_64");
```

You can also change any palette entry directly. Because indexed pixels store only an index, changing a palette color immediately changes every pixel using that index:

```c
set_palette(1, 255, 0, 0);
```

The built-in names are:

## 1Bit Monitor Glow

`use_palette("1bit_monitor_glow")` — 2 colors

<div class="palette">
<span class="swatch" title="0: #222323" style="background:#222323"></span>
<span class="swatch" title="1: #f0f6f0" style="background:#f0f6f0"></span>
</div>

## Aap 64

`use_palette("aap_64")` — 64 colors

<div class="palette">
<span class="swatch" title="0: #060608" style="background:#060608"></span>
<span class="swatch" title="1: #141013" style="background:#141013"></span>
<span class="swatch" title="2: #3b1725" style="background:#3b1725"></span>
<span class="swatch" title="3: #73172d" style="background:#73172d"></span>
<span class="swatch" title="4: #b4202a" style="background:#b4202a"></span>
<span class="swatch" title="5: #df3e23" style="background:#df3e23"></span>
<span class="swatch" title="6: #fa6a0a" style="background:#fa6a0a"></span>
<span class="swatch" title="7: #f9a31b" style="background:#f9a31b"></span>
<span class="swatch" title="8: #ffd541" style="background:#ffd541"></span>
<span class="swatch" title="9: #fffc40" style="background:#fffc40"></span>
<span class="swatch" title="10: #d6f264" style="background:#d6f264"></span>
<span class="swatch" title="11: #9cdb43" style="background:#9cdb43"></span>
<span class="swatch" title="12: #59c135" style="background:#59c135"></span>
<span class="swatch" title="13: #14a02e" style="background:#14a02e"></span>
<span class="swatch" title="14: #1a7a3e" style="background:#1a7a3e"></span>
<span class="swatch" title="15: #24523b" style="background:#24523b"></span>
<span class="swatch" title="16: #122020" style="background:#122020"></span>
<span class="swatch" title="17: #143464" style="background:#143464"></span>
<span class="swatch" title="18: #285cc4" style="background:#285cc4"></span>
<span class="swatch" title="19: #249fde" style="background:#249fde"></span>
<span class="swatch" title="20: #20d6c7" style="background:#20d6c7"></span>
<span class="swatch" title="21: #a6fcdb" style="background:#a6fcdb"></span>
<span class="swatch" title="22: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="23: #fef3c0" style="background:#fef3c0"></span>
<span class="swatch" title="24: #fad6b8" style="background:#fad6b8"></span>
<span class="swatch" title="25: #f5a097" style="background:#f5a097"></span>
<span class="swatch" title="26: #e86a73" style="background:#e86a73"></span>
<span class="swatch" title="27: #bc4a9b" style="background:#bc4a9b"></span>
<span class="swatch" title="28: #793a80" style="background:#793a80"></span>
<span class="swatch" title="29: #403353" style="background:#403353"></span>
<span class="swatch" title="30: #242234" style="background:#242234"></span>
<span class="swatch" title="31: #221c1a" style="background:#221c1a"></span>
<span class="swatch" title="32: #322b28" style="background:#322b28"></span>
<span class="swatch" title="33: #71413b" style="background:#71413b"></span>
<span class="swatch" title="34: #bb7547" style="background:#bb7547"></span>
<span class="swatch" title="35: #dba463" style="background:#dba463"></span>
<span class="swatch" title="36: #f4d29c" style="background:#f4d29c"></span>
<span class="swatch" title="37: #dae0ea" style="background:#dae0ea"></span>
<span class="swatch" title="38: #b3b9d1" style="background:#b3b9d1"></span>
<span class="swatch" title="39: #8b93af" style="background:#8b93af"></span>
<span class="swatch" title="40: #6d758d" style="background:#6d758d"></span>
<span class="swatch" title="41: #4a5462" style="background:#4a5462"></span>
<span class="swatch" title="42: #333941" style="background:#333941"></span>
<span class="swatch" title="43: #422433" style="background:#422433"></span>
<span class="swatch" title="44: #5b3138" style="background:#5b3138"></span>
<span class="swatch" title="45: #8e5252" style="background:#8e5252"></span>
<span class="swatch" title="46: #ba756a" style="background:#ba756a"></span>
<span class="swatch" title="47: #e9b5a3" style="background:#e9b5a3"></span>
<span class="swatch" title="48: #e3e6ff" style="background:#e3e6ff"></span>
<span class="swatch" title="49: #b9bffb" style="background:#b9bffb"></span>
<span class="swatch" title="50: #849be4" style="background:#849be4"></span>
<span class="swatch" title="51: #588dbe" style="background:#588dbe"></span>
<span class="swatch" title="52: #477d85" style="background:#477d85"></span>
<span class="swatch" title="53: #23674e" style="background:#23674e"></span>
<span class="swatch" title="54: #328464" style="background:#328464"></span>
<span class="swatch" title="55: #5daf8d" style="background:#5daf8d"></span>
<span class="swatch" title="56: #92dcba" style="background:#92dcba"></span>
<span class="swatch" title="57: #cdf7e2" style="background:#cdf7e2"></span>
<span class="swatch" title="58: #e4d2aa" style="background:#e4d2aa"></span>
<span class="swatch" title="59: #c7b08b" style="background:#c7b08b"></span>
<span class="swatch" title="60: #a08662" style="background:#a08662"></span>
<span class="swatch" title="61: #796755" style="background:#796755"></span>
<span class="swatch" title="62: #5a4e44" style="background:#5a4e44"></span>
<span class="swatch" title="63: #423934" style="background:#423934"></span>
</div>

## Aerugo

`use_palette("aerugo")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #2f1e1a" style="background:#2f1e1a"></span>
<span class="swatch" title="1: #4f3322" style="background:#4f3322"></span>
<span class="swatch" title="2: #723627" style="background:#723627"></span>
<span class="swatch" title="3: #95392c" style="background:#95392c"></span>
<span class="swatch" title="4: #c75533" style="background:#c75533"></span>
<span class="swatch" title="5: #e76d46" style="background:#e76d46"></span>
<span class="swatch" title="6: #934e28" style="background:#934e28"></span>
<span class="swatch" title="7: #a2663c" style="background:#a2663c"></span>
<span class="swatch" title="8: #c87d40" style="background:#c87d40"></span>
<span class="swatch" title="9: #f5a95b" style="background:#f5a95b"></span>
<span class="swatch" title="10: #6b8b8c" style="background:#6b8b8c"></span>
<span class="swatch" title="11: #81a38e" style="background:#81a38e"></span>
<span class="swatch" title="12: #aac39e" style="background:#aac39e"></span>
<span class="swatch" title="13: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="14: #d1d0ce" style="background:#d1d0ce"></span>
<span class="swatch" title="15: #bab7b2" style="background:#bab7b2"></span>
<span class="swatch" title="16: #898a8a" style="background:#898a8a"></span>
<span class="swatch" title="17: #686461" style="background:#686461"></span>
<span class="swatch" title="18: #554d4b" style="background:#554d4b"></span>
<span class="swatch" title="19: #3c3d3b" style="background:#3c3d3b"></span>
<span class="swatch" title="20: #343230" style="background:#343230"></span>
<span class="swatch" title="21: #87d1ef" style="background:#87d1ef"></span>
<span class="swatch" title="22: #64a1c2" style="background:#64a1c2"></span>
<span class="swatch" title="23: #466480" style="background:#466480"></span>
<span class="swatch" title="24: #2f485c" style="background:#2f485c"></span>
<span class="swatch" title="25: #242e35" style="background:#242e35"></span>
<span class="swatch" title="26: #1b2026" style="background:#1b2026"></span>
<span class="swatch" title="27: #aa9c8a" style="background:#aa9c8a"></span>
<span class="swatch" title="28: #917f6d" style="background:#917f6d"></span>
<span class="swatch" title="29: #86624a" style="background:#86624a"></span>
<span class="swatch" title="30: #715b48" style="background:#715b48"></span>
<span class="swatch" title="31: #5e4835" style="background:#5e4835"></span>
</div>

## Apollo

`use_palette("apollo")` — 46 colors

<div class="palette">
<span class="swatch" title="0: #172038" style="background:#172038"></span>
<span class="swatch" title="1: #253a5e" style="background:#253a5e"></span>
<span class="swatch" title="2: #3c5e8b" style="background:#3c5e8b"></span>
<span class="swatch" title="3: #4f8fba" style="background:#4f8fba"></span>
<span class="swatch" title="4: #73bed3" style="background:#73bed3"></span>
<span class="swatch" title="5: #a4dddb" style="background:#a4dddb"></span>
<span class="swatch" title="6: #19332d" style="background:#19332d"></span>
<span class="swatch" title="7: #25562e" style="background:#25562e"></span>
<span class="swatch" title="8: #468232" style="background:#468232"></span>
<span class="swatch" title="9: #75a743" style="background:#75a743"></span>
<span class="swatch" title="10: #a8ca58" style="background:#a8ca58"></span>
<span class="swatch" title="11: #d0da91" style="background:#d0da91"></span>
<span class="swatch" title="12: #4d2b32" style="background:#4d2b32"></span>
<span class="swatch" title="13: #7a4841" style="background:#7a4841"></span>
<span class="swatch" title="14: #ad7757" style="background:#ad7757"></span>
<span class="swatch" title="15: #c09473" style="background:#c09473"></span>
<span class="swatch" title="16: #d7b594" style="background:#d7b594"></span>
<span class="swatch" title="17: #e7d5b3" style="background:#e7d5b3"></span>
<span class="swatch" title="18: #341c27" style="background:#341c27"></span>
<span class="swatch" title="19: #602c2c" style="background:#602c2c"></span>
<span class="swatch" title="20: #884b2b" style="background:#884b2b"></span>
<span class="swatch" title="21: #be772b" style="background:#be772b"></span>
<span class="swatch" title="22: #de9e41" style="background:#de9e41"></span>
<span class="swatch" title="23: #e8c170" style="background:#e8c170"></span>
<span class="swatch" title="24: #241527" style="background:#241527"></span>
<span class="swatch" title="25: #411d31" style="background:#411d31"></span>
<span class="swatch" title="26: #752438" style="background:#752438"></span>
<span class="swatch" title="27: #a53030" style="background:#a53030"></span>
<span class="swatch" title="28: #cf573c" style="background:#cf573c"></span>
<span class="swatch" title="29: #da863e" style="background:#da863e"></span>
<span class="swatch" title="30: #1e1d39" style="background:#1e1d39"></span>
<span class="swatch" title="31: #402751" style="background:#402751"></span>
<span class="swatch" title="32: #7a367b" style="background:#7a367b"></span>
<span class="swatch" title="33: #a23e8c" style="background:#a23e8c"></span>
<span class="swatch" title="34: #c65197" style="background:#c65197"></span>
<span class="swatch" title="35: #df84a5" style="background:#df84a5"></span>
<span class="swatch" title="36: #090a14" style="background:#090a14"></span>
<span class="swatch" title="37: #10141f" style="background:#10141f"></span>
<span class="swatch" title="38: #151d28" style="background:#151d28"></span>
<span class="swatch" title="39: #202e37" style="background:#202e37"></span>
<span class="swatch" title="40: #394a50" style="background:#394a50"></span>
<span class="swatch" title="41: #577277" style="background:#577277"></span>
<span class="swatch" title="42: #819796" style="background:#819796"></span>
<span class="swatch" title="43: #a8b5b2" style="background:#a8b5b2"></span>
<span class="swatch" title="44: #c7cfcc" style="background:#c7cfcc"></span>
<span class="swatch" title="45: #ebede9" style="background:#ebede9"></span>
</div>

## Blk Neo

`use_palette("blk_neo")` — 46 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #12173d" style="background:#12173d"></span>
<span class="swatch" title="2: #293268" style="background:#293268"></span>
<span class="swatch" title="3: #464b8c" style="background:#464b8c"></span>
<span class="swatch" title="4: #6b74b2" style="background:#6b74b2"></span>
<span class="swatch" title="5: #909edd" style="background:#909edd"></span>
<span class="swatch" title="6: #c1d9f2" style="background:#c1d9f2"></span>
<span class="swatch" title="7: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="8: #ffccd0" style="background:#ffccd0"></span>
<span class="swatch" title="9: #f29faa" style="background:#f29faa"></span>
<span class="swatch" title="10: #c37289" style="background:#c37289"></span>
<span class="swatch" title="11: #994c69" style="background:#994c69"></span>
<span class="swatch" title="12: #723352" style="background:#723352"></span>
<span class="swatch" title="13: #3f1f3c" style="background:#3f1f3c"></span>
<span class="swatch" title="14: #b22e69" style="background:#b22e69"></span>
<span class="swatch" title="15: #e54286" style="background:#e54286"></span>
<span class="swatch" title="16: #ff6eaf" style="background:#ff6eaf"></span>
<span class="swatch" title="17: #ffa5d5" style="background:#ffa5d5"></span>
<span class="swatch" title="18: #8cff9b" style="background:#8cff9b"></span>
<span class="swatch" title="19: #42bc7f" style="background:#42bc7f"></span>
<span class="swatch" title="20: #22896e" style="background:#22896e"></span>
<span class="swatch" title="21: #14665b" style="background:#14665b"></span>
<span class="swatch" title="22: #0f4a4c" style="background:#0f4a4c"></span>
<span class="swatch" title="23: #0a2a33" style="background:#0a2a33"></span>
<span class="swatch" title="24: #1d1a59" style="background:#1d1a59"></span>
<span class="swatch" title="25: #322d89" style="background:#322d89"></span>
<span class="swatch" title="26: #354ab2" style="background:#354ab2"></span>
<span class="swatch" title="27: #3e83d1" style="background:#3e83d1"></span>
<span class="swatch" title="28: #50b9eb" style="background:#50b9eb"></span>
<span class="swatch" title="29: #8cdaff" style="background:#8cdaff"></span>
<span class="swatch" title="30: #b483ef" style="background:#b483ef"></span>
<span class="swatch" title="31: #854cbf" style="background:#854cbf"></span>
<span class="swatch" title="32: #5d2f8c" style="background:#5d2f8c"></span>
<span class="swatch" title="33: #431e66" style="background:#431e66"></span>
<span class="swatch" title="34: #ffe091" style="background:#ffe091"></span>
<span class="swatch" title="35: #ffaa6e" style="background:#ffaa6e"></span>
<span class="swatch" title="36: #ff695a" style="background:#ff695a"></span>
<span class="swatch" title="37: #b23c40" style="background:#b23c40"></span>
<span class="swatch" title="38: #721c2f" style="background:#721c2f"></span>
<span class="swatch" title="39: #a52639" style="background:#a52639"></span>
<span class="swatch" title="40: #dd3745" style="background:#dd3745"></span>
<span class="swatch" title="41: #ff6675" style="background:#ff6675"></span>
<span class="swatch" title="42: #78fae6" style="background:#78fae6"></span>
<span class="swatch" title="43: #27d3cb" style="background:#27d3cb"></span>
<span class="swatch" title="44: #00aaa5" style="background:#00aaa5"></span>
<span class="swatch" title="45: #008782" style="background:#008782"></span>
</div>

## Calm Sunset

`use_palette("calm_sunset")` — 7 colors

<div class="palette">
<span class="swatch" title="0: #684971" style="background:#684971"></span>
<span class="swatch" title="1: #a06389" style="background:#a06389"></span>
<span class="swatch" title="2: #cb7ca2" style="background:#cb7ca2"></span>
<span class="swatch" title="3: #e1aea4" style="background:#e1aea4"></span>
<span class="swatch" title="4: #f9d8a1" style="background:#f9d8a1"></span>
<span class="swatch" title="5: #ffecb2" style="background:#ffecb2"></span>
<span class="swatch" title="6: #fffcf1" style="background:#fffcf1"></span>
</div>

## Carnival 32

`use_palette("carnival_32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #4d2235" style="background:#4d2235"></span>
<span class="swatch" title="1: #71282a" style="background:#71282a"></span>
<span class="swatch" title="2: #975638" style="background:#975638"></span>
<span class="swatch" title="3: #d0763e" style="background:#d0763e"></span>
<span class="swatch" title="4: #ebac4d" style="background:#ebac4d"></span>
<span class="swatch" title="5: #f2d08d" style="background:#f2d08d"></span>
<span class="swatch" title="6: #ddac88" style="background:#ddac88"></span>
<span class="swatch" title="7: #c68d80" style="background:#c68d80"></span>
<span class="swatch" title="8: #af6d77" style="background:#af6d77"></span>
<span class="swatch" title="9: #c74446" style="background:#c74446"></span>
<span class="swatch" title="10: #9f3847" style="background:#9f3847"></span>
<span class="swatch" title="11: #6e406d" style="background:#6e406d"></span>
<span class="swatch" title="12: #a7a758" style="background:#a7a758"></span>
<span class="swatch" title="13: #718141" style="background:#718141"></span>
<span class="swatch" title="14: #496541" style="background:#496541"></span>
<span class="swatch" title="15: #37433b" style="background:#37433b"></span>
<span class="swatch" title="16: #2a1c31" style="background:#2a1c31"></span>
<span class="swatch" title="17: #423157" style="background:#423157"></span>
<span class="swatch" title="18: #4d528a" style="background:#4d528a"></span>
<span class="swatch" title="19: #556a97" style="background:#556a97"></span>
<span class="swatch" title="20: #5c81a3" style="background:#5c81a3"></span>
<span class="swatch" title="21: #7dadc8" style="background:#7dadc8"></span>
<span class="swatch" title="22: #b0d6d9" style="background:#b0d6d9"></span>
<span class="swatch" title="23: #ece6df" style="background:#ece6df"></span>
<span class="swatch" title="24: #cfccca" style="background:#cfccca"></span>
<span class="swatch" title="25: #a6a6a6" style="background:#a6a6a6"></span>
<span class="swatch" title="26: #787878" style="background:#787878"></span>
<span class="swatch" title="27: #626262" style="background:#626262"></span>
<span class="swatch" title="28: #4a4a4a" style="background:#4a4a4a"></span>
<span class="swatch" title="29: #363636" style="background:#363636"></span>
<span class="swatch" title="30: #618c70" style="background:#618c70"></span>
<span class="swatch" title="31: #8b7463" style="background:#8b7463"></span>
</div>

## Cc 29

`use_palette("cc_29")` — 29 colors

<div class="palette">
<span class="swatch" title="0: #f2f0e5" style="background:#f2f0e5"></span>
<span class="swatch" title="1: #b8b5b9" style="background:#b8b5b9"></span>
<span class="swatch" title="2: #868188" style="background:#868188"></span>
<span class="swatch" title="3: #646365" style="background:#646365"></span>
<span class="swatch" title="4: #45444f" style="background:#45444f"></span>
<span class="swatch" title="5: #3a3858" style="background:#3a3858"></span>
<span class="swatch" title="6: #212123" style="background:#212123"></span>
<span class="swatch" title="7: #352b42" style="background:#352b42"></span>
<span class="swatch" title="8: #43436a" style="background:#43436a"></span>
<span class="swatch" title="9: #4b80ca" style="background:#4b80ca"></span>
<span class="swatch" title="10: #68c2d3" style="background:#68c2d3"></span>
<span class="swatch" title="11: #a2dcc7" style="background:#a2dcc7"></span>
<span class="swatch" title="12: #ede19e" style="background:#ede19e"></span>
<span class="swatch" title="13: #d3a068" style="background:#d3a068"></span>
<span class="swatch" title="14: #b45252" style="background:#b45252"></span>
<span class="swatch" title="15: #6a536e" style="background:#6a536e"></span>
<span class="swatch" title="16: #4b4158" style="background:#4b4158"></span>
<span class="swatch" title="17: #80493a" style="background:#80493a"></span>
<span class="swatch" title="18: #a77b5b" style="background:#a77b5b"></span>
<span class="swatch" title="19: #e5ceb4" style="background:#e5ceb4"></span>
<span class="swatch" title="20: #c2d368" style="background:#c2d368"></span>
<span class="swatch" title="21: #8ab060" style="background:#8ab060"></span>
<span class="swatch" title="22: #567b79" style="background:#567b79"></span>
<span class="swatch" title="23: #4e584a" style="background:#4e584a"></span>
<span class="swatch" title="24: #7b7243" style="background:#7b7243"></span>
<span class="swatch" title="25: #b2b47e" style="background:#b2b47e"></span>
<span class="swatch" title="26: #edc8c4" style="background:#edc8c4"></span>
<span class="swatch" title="27: #cf8acb" style="background:#cf8acb"></span>
<span class="swatch" title="28: #5f556a" style="background:#5f556a"></span>
</div>

## Cga Palette 1 High

`use_palette("cga_palette_1_high")` — 4 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #ff55ff" style="background:#ff55ff"></span>
<span class="swatch" title="2: #55ffff" style="background:#55ffff"></span>
<span class="swatch" title="3: #ffffff" style="background:#ffffff"></span>
</div>

## Cling

`use_palette("cling")` — 44 colors

<div class="palette">
<span class="swatch" title="0: #ffe617" style="background:#ffe617"></span>
<span class="swatch" title="1: #fad31c" style="background:#fad31c"></span>
<span class="swatch" title="2: #fdb717" style="background:#fdb717"></span>
<span class="swatch" title="3: #faaa21" style="background:#faaa21"></span>
<span class="swatch" title="4: #f1753f" style="background:#f1753f"></span>
<span class="swatch" title="5: #ed5724" style="background:#ed5724"></span>
<span class="swatch" title="6: #ef4538" style="background:#ef4538"></span>
<span class="swatch" title="7: #ea2830" style="background:#ea2830"></span>
<span class="swatch" title="8: #bc2326" style="background:#bc2326"></span>
<span class="swatch" title="9: #8c0c03" style="background:#8c0c03"></span>
<span class="swatch" title="10: #e5185d" style="background:#e5185d"></span>
<span class="swatch" title="11: #f384ae" style="background:#f384ae"></span>
<span class="swatch" title="12: #fac6d2" style="background:#fac6d2"></span>
<span class="swatch" title="13: #b296c7" style="background:#b296c7"></span>
<span class="swatch" title="14: #7b67ae" style="background:#7b67ae"></span>
<span class="swatch" title="15: #5f3577" style="background:#5f3577"></span>
<span class="swatch" title="16: #c1d18a" style="background:#c1d18a"></span>
<span class="swatch" title="17: #799155" style="background:#799155"></span>
<span class="swatch" title="18: #80bc42" style="background:#80bc42"></span>
<span class="swatch" title="19: #4aa03f" style="background:#4aa03f"></span>
<span class="swatch" title="20: #16884a" style="background:#16884a"></span>
<span class="swatch" title="21: #003f2e" style="background:#003f2e"></span>
<span class="swatch" title="22: #c3def1" style="background:#c3def1"></span>
<span class="swatch" title="23: #55beed" style="background:#55beed"></span>
<span class="swatch" title="24: #31a8e0" style="background:#31a8e0"></span>
<span class="swatch" title="25: #238acc" style="background:#238acc"></span>
<span class="swatch" title="26: #0d60ae" style="background:#0d60ae"></span>
<span class="swatch" title="27: #143b86" style="background:#143b86"></span>
<span class="swatch" title="28: #001b4a" style="background:#001b4a"></span>
<span class="swatch" title="29: #7dcdc2" style="background:#7dcdc2"></span>
<span class="swatch" title="30: #00a8a8" style="background:#00a8a8"></span>
<span class="swatch" title="31: #12959f" style="background:#12959f"></span>
<span class="swatch" title="32: #094e54" style="background:#094e54"></span>
<span class="swatch" title="33: #381e11" style="background:#381e11"></span>
<span class="swatch" title="34: #c05c20" style="background:#c05c20"></span>
<span class="swatch" title="35: #bf9b6b" style="background:#bf9b6b"></span>
<span class="swatch" title="36: #e9d4a7" style="background:#e9d4a7"></span>
<span class="swatch" title="37: #e7e6e1" style="background:#e7e6e1"></span>
<span class="swatch" title="38: #cfd0d2" style="background:#cfd0d2"></span>
<span class="swatch" title="39: #8a8b8f" style="background:#8a8b8f"></span>
<span class="swatch" title="40: #778590" style="background:#778590"></span>
<span class="swatch" title="41: #474d4d" style="background:#474d4d"></span>
<span class="swatch" title="42: #050608" style="background:#050608"></span>
<span class="swatch" title="43: #ffffff" style="background:#ffffff"></span>
</div>

## Cloudy 28

`use_palette("cloudy_28")` — 28 colors

<div class="palette">
<span class="swatch" title="0: #daddee" style="background:#daddee"></span>
<span class="swatch" title="1: #b6cde3" style="background:#b6cde3"></span>
<span class="swatch" title="2: #92bbcd" style="background:#92bbcd"></span>
<span class="swatch" title="3: #6ba9b4" style="background:#6ba9b4"></span>
<span class="swatch" title="4: #51887c" style="background:#51887c"></span>
<span class="swatch" title="5: #66a96d" style="background:#66a96d"></span>
<span class="swatch" title="6: #a6c87b" style="background:#a6c87b"></span>
<span class="swatch" title="7: #d9e68f" style="background:#d9e68f"></span>
<span class="swatch" title="8: #ecaa6d" style="background:#ecaa6d"></span>
<span class="swatch" title="9: #d56247" style="background:#d56247"></span>
<span class="swatch" title="10: #a43c3c" style="background:#a43c3c"></span>
<span class="swatch" title="11: #59160e" style="background:#59160e"></span>
<span class="swatch" title="12: #773c35" style="background:#773c35"></span>
<span class="swatch" title="13: #9e6257" style="background:#9e6257"></span>
<span class="swatch" title="14: #d3847a" style="background:#d3847a"></span>
<span class="swatch" title="15: #db96ad" style="background:#db96ad"></span>
<span class="swatch" title="16: #c277a3" style="background:#c277a3"></span>
<span class="swatch" title="17: #9b5d99" style="background:#9b5d99"></span>
<span class="swatch" title="18: #62417d" style="background:#62417d"></span>
<span class="swatch" title="19: #0c0f32" style="background:#0c0f32"></span>
<span class="swatch" title="20: #252a6f" style="background:#252a6f"></span>
<span class="swatch" title="21: #34539e" style="background:#34539e"></span>
<span class="swatch" title="22: #457bb4" style="background:#457bb4"></span>
<span class="swatch" title="23: #68a5d5" style="background:#68a5d5"></span>
<span class="swatch" title="24: #92cade" style="background:#92cade"></span>
<span class="swatch" title="25: #97a6b7" style="background:#97a6b7"></span>
<span class="swatch" title="26: #7b8aa4" style="background:#7b8aa4"></span>
<span class="swatch" title="27: #5a6685" style="background:#5a6685"></span>
</div>

## Color Graphics Adapter

`use_palette("color_graphics_adapter")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #555555" style="background:#555555"></span>
<span class="swatch" title="2: #aaaaaa" style="background:#aaaaaa"></span>
<span class="swatch" title="3: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="4: #0000aa" style="background:#0000aa"></span>
<span class="swatch" title="5: #5555ff" style="background:#5555ff"></span>
<span class="swatch" title="6: #00aa00" style="background:#00aa00"></span>
<span class="swatch" title="7: #55ff55" style="background:#55ff55"></span>
<span class="swatch" title="8: #00aaaa" style="background:#00aaaa"></span>
<span class="swatch" title="9: #55ffff" style="background:#55ffff"></span>
<span class="swatch" title="10: #aa0000" style="background:#aa0000"></span>
<span class="swatch" title="11: #ff5555" style="background:#ff5555"></span>
<span class="swatch" title="12: #aa00aa" style="background:#aa00aa"></span>
<span class="swatch" title="13: #ff55ff" style="background:#ff55ff"></span>
<span class="swatch" title="14: #aa5500" style="background:#aa5500"></span>
<span class="swatch" title="15: #ffff55" style="background:#ffff55"></span>
</div>

## Colordome 32

`use_palette("colordome_32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #0d0b0d" style="background:#0d0b0d"></span>
<span class="swatch" title="1: #fff8e1" style="background:#fff8e1"></span>
<span class="swatch" title="2: #c8b89f" style="background:#c8b89f"></span>
<span class="swatch" title="3: #987a68" style="background:#987a68"></span>
<span class="swatch" title="4: #674949" style="background:#674949"></span>
<span class="swatch" title="5: #3a3941" style="background:#3a3941"></span>
<span class="swatch" title="6: #6b6f72" style="background:#6b6f72"></span>
<span class="swatch" title="7: #adb9b8" style="background:#adb9b8"></span>
<span class="swatch" title="8: #add9b7" style="background:#add9b7"></span>
<span class="swatch" title="9: #6eb39d" style="background:#6eb39d"></span>
<span class="swatch" title="10: #30555b" style="background:#30555b"></span>
<span class="swatch" title="11: #1a1e2d" style="background:#1a1e2d"></span>
<span class="swatch" title="12: #284e43" style="background:#284e43"></span>
<span class="swatch" title="13: #467e3e" style="background:#467e3e"></span>
<span class="swatch" title="14: #93ab52" style="background:#93ab52"></span>
<span class="swatch" title="15: #f2cf5c" style="background:#f2cf5c"></span>
<span class="swatch" title="16: #ec773d" style="background:#ec773d"></span>
<span class="swatch" title="17: #b83530" style="background:#b83530"></span>
<span class="swatch" title="18: #722030" style="background:#722030"></span>
<span class="swatch" title="19: #281721" style="background:#281721"></span>
<span class="swatch" title="20: #6d2944" style="background:#6d2944"></span>
<span class="swatch" title="21: #c85257" style="background:#c85257"></span>
<span class="swatch" title="22: #ec9983" style="background:#ec9983"></span>
<span class="swatch" title="23: #dbaf77" style="background:#dbaf77"></span>
<span class="swatch" title="24: #b77854" style="background:#b77854"></span>
<span class="swatch" title="25: #833e35" style="background:#833e35"></span>
<span class="swatch" title="26: #50282f" style="background:#50282f"></span>
<span class="swatch" title="27: #65432f" style="background:#65432f"></span>
<span class="swatch" title="28: #7e6d37" style="background:#7e6d37"></span>
<span class="swatch" title="29: #6ebe70" style="background:#6ebe70"></span>
<span class="swatch" title="30: #b75834" style="background:#b75834"></span>
<span class="swatch" title="31: #d55c4d" style="background:#d55c4d"></span>
</div>

## Comicscapes 50

`use_palette("comicscapes_50")` — 50 colors

<div class="palette">
<span class="swatch" title="0: #8ec5b5" style="background:#8ec5b5"></span>
<span class="swatch" title="1: #70ada4" style="background:#70ada4"></span>
<span class="swatch" title="2: #5b9a9a" style="background:#5b9a9a"></span>
<span class="swatch" title="3: #4d7d8d" style="background:#4d7d8d"></span>
<span class="swatch" title="4: #365471" style="background:#365471"></span>
<span class="swatch" title="5: #2a4268" style="background:#2a4268"></span>
<span class="swatch" title="6: #192449" style="background:#192449"></span>
<span class="swatch" title="7: #150d37" style="background:#150d37"></span>
<span class="swatch" title="8: #140726" style="background:#140726"></span>
<span class="swatch" title="9: #0c1634" style="background:#0c1634"></span>
<span class="swatch" title="10: #102d40" style="background:#102d40"></span>
<span class="swatch" title="11: #16444d" style="background:#16444d"></span>
<span class="swatch" title="12: #1f605e" style="background:#1f605e"></span>
<span class="swatch" title="13: #2e8172" style="background:#2e8172"></span>
<span class="swatch" title="14: #409e74" style="background:#409e74"></span>
<span class="swatch" title="15: #62bb7d" style="background:#62bb7d"></span>
<span class="swatch" title="16: #79cd7a" style="background:#79cd7a"></span>
<span class="swatch" title="17: #240d39" style="background:#240d39"></span>
<span class="swatch" title="18: #38154e" style="background:#38154e"></span>
<span class="swatch" title="19: #551e66" style="background:#551e66"></span>
<span class="swatch" title="20: #712d7a" style="background:#712d7a"></span>
<span class="swatch" title="21: #92428f" style="background:#92428f"></span>
<span class="swatch" title="22: #ad608f" style="background:#ad608f"></span>
<span class="swatch" title="23: #92b5b8" style="background:#92b5b8"></span>
<span class="swatch" title="24: #869da2" style="background:#869da2"></span>
<span class="swatch" title="25: #79878e" style="background:#79878e"></span>
<span class="swatch" title="26: #676c78" style="background:#676c78"></span>
<span class="swatch" title="27: #595966" style="background:#595966"></span>
<span class="swatch" title="28: #47444e" style="background:#47444e"></span>
<span class="swatch" title="29: #3f3a43" style="background:#3f3a43"></span>
<span class="swatch" title="30: #362f37" style="background:#362f37"></span>
<span class="swatch" title="31: #2a2328" style="background:#2a2328"></span>
<span class="swatch" title="32: #0e020a" style="background:#0e020a"></span>
<span class="swatch" title="33: #340f21" style="background:#340f21"></span>
<span class="swatch" title="34: #4e1f32" style="background:#4e1f32"></span>
<span class="swatch" title="35: #743444" style="background:#743444"></span>
<span class="swatch" title="36: #8c454e" style="background:#8c454e"></span>
<span class="swatch" title="37: #a25959" style="background:#a25959"></span>
<span class="swatch" title="38: #b3736a" style="background:#b3736a"></span>
<span class="swatch" title="39: #c69580" style="background:#c69580"></span>
<span class="swatch" title="40: #d2ae91" style="background:#d2ae91"></span>
<span class="swatch" title="41: #e5ccab" style="background:#e5ccab"></span>
<span class="swatch" title="42: #f2e9cd" style="background:#f2e9cd"></span>
<span class="swatch" title="43: #f2dfa7" style="background:#f2dfa7"></span>
<span class="swatch" title="44: #dfb684" style="background:#dfb684"></span>
<span class="swatch" title="45: #d29567" style="background:#d29567"></span>
<span class="swatch" title="46: #bf6e50" style="background:#bf6e50"></span>
<span class="swatch" title="47: #b24e3d" style="background:#b24e3d"></span>
<span class="swatch" title="48: #a43045" style="background:#a43045"></span>
<span class="swatch" title="49: #952452" style="background:#952452"></span>
</div>

## Crimson

`use_palette("crimson")` — 4 colors

<div class="palette">
<span class="swatch" title="0: #eff9d6" style="background:#eff9d6"></span>
<span class="swatch" title="1: #ba5044" style="background:#ba5044"></span>
<span class="swatch" title="2: #7a1c4b" style="background:#7a1c4b"></span>
<span class="swatch" title="3: #1b0326" style="background:#1b0326"></span>
</div>

## Cryptic Ocean

`use_palette("cryptic_ocean")` — 6 colors

<div class="palette">
<span class="swatch" title="0: #2a173b" style="background:#2a173b"></span>
<span class="swatch" title="1: #3f2c5f" style="background:#3f2c5f"></span>
<span class="swatch" title="2: #443f7b" style="background:#443f7b"></span>
<span class="swatch" title="3: #4c5c87" style="background:#4c5c87"></span>
<span class="swatch" title="4: #69809e" style="background:#69809e"></span>
<span class="swatch" title="5: #95c5ac" style="background:#95c5ac"></span>
</div>

## Darkvania

`use_palette("darkvania")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #120e2f" style="background:#120e2f"></span>
<span class="swatch" title="1: #1b1b52" style="background:#1b1b52"></span>
<span class="swatch" title="2: #293377" style="background:#293377"></span>
<span class="swatch" title="3: #5670c2" style="background:#5670c2"></span>
<span class="swatch" title="4: #cfe8ff" style="background:#cfe8ff"></span>
<span class="swatch" title="5: #aabfe0" style="background:#aabfe0"></span>
<span class="swatch" title="6: #9b9ed2" style="background:#9b9ed2"></span>
<span class="swatch" title="7: #4d3c66" style="background:#4d3c66"></span>
<span class="swatch" title="8: #1d1023" style="background:#1d1023"></span>
<span class="swatch" title="9: #38173c" style="background:#38173c"></span>
<span class="swatch" title="10: #4e0b3c" style="background:#4e0b3c"></span>
<span class="swatch" title="11: #66123b" style="background:#66123b"></span>
<span class="swatch" title="12: #ad4557" style="background:#ad4557"></span>
<span class="swatch" title="13: #c9757e" style="background:#c9757e"></span>
<span class="swatch" title="14: #ebb1ae" style="background:#ebb1ae"></span>
<span class="swatch" title="15: #ffdcd6" style="background:#ffdcd6"></span>
<span class="swatch" title="16: #ecb78c" style="background:#ecb78c"></span>
<span class="swatch" title="17: #cb9367" style="background:#cb9367"></span>
<span class="swatch" title="18: #b8814f" style="background:#b8814f"></span>
<span class="swatch" title="19: #77491e" style="background:#77491e"></span>
<span class="swatch" title="20: #572b16" style="background:#572b16"></span>
<span class="swatch" title="21: #360c01" style="background:#360c01"></span>
<span class="swatch" title="22: #7b2f11" style="background:#7b2f11"></span>
<span class="swatch" title="23: #d6761c" style="background:#d6761c"></span>
<span class="swatch" title="24: #f69d18" style="background:#f69d18"></span>
<span class="swatch" title="25: #ffd21c" style="background:#ffd21c"></span>
<span class="swatch" title="26: #c7fba1" style="background:#c7fba1"></span>
<span class="swatch" title="27: #7ec177" style="background:#7ec177"></span>
<span class="swatch" title="28: #519a57" style="background:#519a57"></span>
<span class="swatch" title="29: #33694a" style="background:#33694a"></span>
<span class="swatch" title="30: #265448" style="background:#265448"></span>
<span class="swatch" title="31: #102f2e" style="background:#102f2e"></span>
</div>

## Daydream 20

`use_palette("daydream_20")` — 20 colors

<div class="palette">
<span class="swatch" title="0: #430f43" style="background:#430f43"></span>
<span class="swatch" title="1: #472561" style="background:#472561"></span>
<span class="swatch" title="2: #205973" style="background:#205973"></span>
<span class="swatch" title="3: #248077" style="background:#248077"></span>
<span class="swatch" title="4: #2d9a77" style="background:#2d9a77"></span>
<span class="swatch" title="5: #5ec688" style="background:#5ec688"></span>
<span class="swatch" title="6: #aae68f" style="background:#aae68f"></span>
<span class="swatch" title="7: #64154d" style="background:#64154d"></span>
<span class="swatch" title="8: #8e184b" style="background:#8e184b"></span>
<span class="swatch" title="9: #ba3155" style="background:#ba3155"></span>
<span class="swatch" title="10: #d9505e" style="background:#d9505e"></span>
<span class="swatch" title="11: #e3744f" style="background:#e3744f"></span>
<span class="swatch" title="12: #f29e64" style="background:#f29e64"></span>
<span class="swatch" title="13: #ffc477" style="background:#ffc477"></span>
<span class="swatch" title="14: #ffdd96" style="background:#ffdd96"></span>
<span class="swatch" title="15: #fff4b0" style="background:#fff4b0"></span>
<span class="swatch" title="16: #c22e35" style="background:#c22e35"></span>
<span class="swatch" title="17: #d24f38" style="background:#d24f38"></span>
<span class="swatch" title="18: #df6939" style="background:#df6939"></span>
<span class="swatch" title="19: #ed9b4a" style="background:#ed9b4a"></span>
</div>

## Dreamscape8

`use_palette("dreamscape8")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #c9cca1" style="background:#c9cca1"></span>
<span class="swatch" title="1: #caa05a" style="background:#caa05a"></span>
<span class="swatch" title="2: #ae6a47" style="background:#ae6a47"></span>
<span class="swatch" title="3: #8b4049" style="background:#8b4049"></span>
<span class="swatch" title="4: #543344" style="background:#543344"></span>
<span class="swatch" title="5: #515262" style="background:#515262"></span>
<span class="swatch" title="6: #63787d" style="background:#63787d"></span>
<span class="swatch" title="7: #8ea091" style="background:#8ea091"></span>
</div>

## Ega Com Extended

`use_palette("ega_com_extended")` — 20 colors

<div class="palette">
<span class="swatch" title="0: #292929" style="background:#292929"></span>
<span class="swatch" title="1: #52575c" style="background:#52575c"></span>
<span class="swatch" title="2: #94999e" style="background:#94999e"></span>
<span class="swatch" title="3: #deeedc" style="background:#deeedc"></span>
<span class="swatch" title="4: #7b2d2f" style="background:#7b2d2f"></span>
<span class="swatch" title="5: #d04043" style="background:#d04043"></span>
<span class="swatch" title="6: #cb8f21" style="background:#cb8f21"></span>
<span class="swatch" title="7: #e6c439" style="background:#e6c439"></span>
<span class="swatch" title="8: #6c4b37" style="background:#6c4b37"></span>
<span class="swatch" title="9: #8c6946" style="background:#8c6946"></span>
<span class="swatch" title="10: #538a6a" style="background:#538a6a"></span>
<span class="swatch" title="11: #63b465" style="background:#63b465"></span>
<span class="swatch" title="12: #2c4267" style="background:#2c4267"></span>
<span class="swatch" title="13: #38668b" style="background:#38668b"></span>
<span class="swatch" title="14: #775780" style="background:#775780"></span>
<span class="swatch" title="15: #f4a66c" style="background:#f4a66c"></span>
<span class="swatch" title="16: #576e54" style="background:#576e54"></span>
<span class="swatch" title="17: #82e8e8" style="background:#82e8e8"></span>
<span class="swatch" title="18: #9d446a" style="background:#9d446a"></span>
<span class="swatch" title="19: #eb7272" style="background:#eb7272"></span>
</div>

## Eggdealer6

`use_palette("eggdealer6")` — 6 colors

<div class="palette">
<span class="swatch" title="0: #47323b" style="background:#47323b"></span>
<span class="swatch" title="1: #5c4657" style="background:#5c4657"></span>
<span class="swatch" title="2: #735a55" style="background:#735a55"></span>
<span class="swatch" title="3: #b0764f" style="background:#b0764f"></span>
<span class="swatch" title="4: #baac81" style="background:#baac81"></span>
<span class="swatch" title="5: #e9d79d" style="background:#e9d79d"></span>
</div>

## Endesga 32

`use_palette("endesga_32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #be4a2f" style="background:#be4a2f"></span>
<span class="swatch" title="1: #d77643" style="background:#d77643"></span>
<span class="swatch" title="2: #ead4aa" style="background:#ead4aa"></span>
<span class="swatch" title="3: #e4a672" style="background:#e4a672"></span>
<span class="swatch" title="4: #b86f50" style="background:#b86f50"></span>
<span class="swatch" title="5: #733e39" style="background:#733e39"></span>
<span class="swatch" title="6: #3e2731" style="background:#3e2731"></span>
<span class="swatch" title="7: #a22633" style="background:#a22633"></span>
<span class="swatch" title="8: #e43b44" style="background:#e43b44"></span>
<span class="swatch" title="9: #f77622" style="background:#f77622"></span>
<span class="swatch" title="10: #feae34" style="background:#feae34"></span>
<span class="swatch" title="11: #fee761" style="background:#fee761"></span>
<span class="swatch" title="12: #63c74d" style="background:#63c74d"></span>
<span class="swatch" title="13: #3e8948" style="background:#3e8948"></span>
<span class="swatch" title="14: #265c42" style="background:#265c42"></span>
<span class="swatch" title="15: #193c3e" style="background:#193c3e"></span>
<span class="swatch" title="16: #124e89" style="background:#124e89"></span>
<span class="swatch" title="17: #0099db" style="background:#0099db"></span>
<span class="swatch" title="18: #2ce8f5" style="background:#2ce8f5"></span>
<span class="swatch" title="19: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="20: #c0cbdc" style="background:#c0cbdc"></span>
<span class="swatch" title="21: #8b9bb4" style="background:#8b9bb4"></span>
<span class="swatch" title="22: #5a6988" style="background:#5a6988"></span>
<span class="swatch" title="23: #3a4466" style="background:#3a4466"></span>
<span class="swatch" title="24: #262b44" style="background:#262b44"></span>
<span class="swatch" title="25: #181425" style="background:#181425"></span>
<span class="swatch" title="26: #ff0044" style="background:#ff0044"></span>
<span class="swatch" title="27: #68386c" style="background:#68386c"></span>
<span class="swatch" title="28: #b55088" style="background:#b55088"></span>
<span class="swatch" title="29: #f6757a" style="background:#f6757a"></span>
<span class="swatch" title="30: #e8b796" style="background:#e8b796"></span>
<span class="swatch" title="31: #c28569" style="background:#c28569"></span>
</div>

## Endesga 64

`use_palette("endesga_64")` — 64 colors

<div class="palette">
<span class="swatch" title="0: #ff0040" style="background:#ff0040"></span>
<span class="swatch" title="1: #131313" style="background:#131313"></span>
<span class="swatch" title="2: #1b1b1b" style="background:#1b1b1b"></span>
<span class="swatch" title="3: #272727" style="background:#272727"></span>
<span class="swatch" title="4: #3d3d3d" style="background:#3d3d3d"></span>
<span class="swatch" title="5: #5d5d5d" style="background:#5d5d5d"></span>
<span class="swatch" title="6: #858585" style="background:#858585"></span>
<span class="swatch" title="7: #b4b4b4" style="background:#b4b4b4"></span>
<span class="swatch" title="8: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="9: #c7cfdd" style="background:#c7cfdd"></span>
<span class="swatch" title="10: #92a1b9" style="background:#92a1b9"></span>
<span class="swatch" title="11: #657392" style="background:#657392"></span>
<span class="swatch" title="12: #424c6e" style="background:#424c6e"></span>
<span class="swatch" title="13: #2a2f4e" style="background:#2a2f4e"></span>
<span class="swatch" title="14: #1a1932" style="background:#1a1932"></span>
<span class="swatch" title="15: #0e071b" style="background:#0e071b"></span>
<span class="swatch" title="16: #1c121c" style="background:#1c121c"></span>
<span class="swatch" title="17: #391f21" style="background:#391f21"></span>
<span class="swatch" title="18: #5d2c28" style="background:#5d2c28"></span>
<span class="swatch" title="19: #8a4836" style="background:#8a4836"></span>
<span class="swatch" title="20: #bf6f4a" style="background:#bf6f4a"></span>
<span class="swatch" title="21: #e69c69" style="background:#e69c69"></span>
<span class="swatch" title="22: #f6ca9f" style="background:#f6ca9f"></span>
<span class="swatch" title="23: #f9e6cf" style="background:#f9e6cf"></span>
<span class="swatch" title="24: #edab50" style="background:#edab50"></span>
<span class="swatch" title="25: #e07438" style="background:#e07438"></span>
<span class="swatch" title="26: #c64524" style="background:#c64524"></span>
<span class="swatch" title="27: #8e251d" style="background:#8e251d"></span>
<span class="swatch" title="28: #ff5000" style="background:#ff5000"></span>
<span class="swatch" title="29: #ed7614" style="background:#ed7614"></span>
<span class="swatch" title="30: #ffa214" style="background:#ffa214"></span>
<span class="swatch" title="31: #ffc825" style="background:#ffc825"></span>
<span class="swatch" title="32: #ffeb57" style="background:#ffeb57"></span>
<span class="swatch" title="33: #d3fc7e" style="background:#d3fc7e"></span>
<span class="swatch" title="34: #99e65f" style="background:#99e65f"></span>
<span class="swatch" title="35: #5ac54f" style="background:#5ac54f"></span>
<span class="swatch" title="36: #33984b" style="background:#33984b"></span>
<span class="swatch" title="37: #1e6f50" style="background:#1e6f50"></span>
<span class="swatch" title="38: #134c4c" style="background:#134c4c"></span>
<span class="swatch" title="39: #0c2e44" style="background:#0c2e44"></span>
<span class="swatch" title="40: #00396d" style="background:#00396d"></span>
<span class="swatch" title="41: #0069aa" style="background:#0069aa"></span>
<span class="swatch" title="42: #0098dc" style="background:#0098dc"></span>
<span class="swatch" title="43: #00cdf9" style="background:#00cdf9"></span>
<span class="swatch" title="44: #0cf1ff" style="background:#0cf1ff"></span>
<span class="swatch" title="45: #94fdff" style="background:#94fdff"></span>
<span class="swatch" title="46: #fdd2ed" style="background:#fdd2ed"></span>
<span class="swatch" title="47: #f389f5" style="background:#f389f5"></span>
<span class="swatch" title="48: #db3ffd" style="background:#db3ffd"></span>
<span class="swatch" title="49: #7a09fa" style="background:#7a09fa"></span>
<span class="swatch" title="50: #3003d9" style="background:#3003d9"></span>
<span class="swatch" title="51: #0c0293" style="background:#0c0293"></span>
<span class="swatch" title="52: #03193f" style="background:#03193f"></span>
<span class="swatch" title="53: #3b1443" style="background:#3b1443"></span>
<span class="swatch" title="54: #622461" style="background:#622461"></span>
<span class="swatch" title="55: #93388f" style="background:#93388f"></span>
<span class="swatch" title="56: #ca52c9" style="background:#ca52c9"></span>
<span class="swatch" title="57: #c85086" style="background:#c85086"></span>
<span class="swatch" title="58: #f68187" style="background:#f68187"></span>
<span class="swatch" title="59: #f5555d" style="background:#f5555d"></span>
<span class="swatch" title="60: #ea323c" style="background:#ea323c"></span>
<span class="swatch" title="61: #c42430" style="background:#c42430"></span>
<span class="swatch" title="62: #891e2b" style="background:#891e2b"></span>
<span class="swatch" title="63: #571c27" style="background:#571c27"></span>
</div>

## Eroge Copper

`use_palette("eroge_copper")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #0d080d" style="background:#0d080d"></span>
<span class="swatch" title="1: #4f2b24" style="background:#4f2b24"></span>
<span class="swatch" title="2: #825b31" style="background:#825b31"></span>
<span class="swatch" title="3: #c59154" style="background:#c59154"></span>
<span class="swatch" title="4: #f0bd77" style="background:#f0bd77"></span>
<span class="swatch" title="5: #fbdf9b" style="background:#fbdf9b"></span>
<span class="swatch" title="6: #fff9e4" style="background:#fff9e4"></span>
<span class="swatch" title="7: #bebbb2" style="background:#bebbb2"></span>
<span class="swatch" title="8: #7bb24e" style="background:#7bb24e"></span>
<span class="swatch" title="9: #74adbb" style="background:#74adbb"></span>
<span class="swatch" title="10: #4180a0" style="background:#4180a0"></span>
<span class="swatch" title="11: #32535f" style="background:#32535f"></span>
<span class="swatch" title="12: #2a2349" style="background:#2a2349"></span>
<span class="swatch" title="13: #7d3840" style="background:#7d3840"></span>
<span class="swatch" title="14: #c16c5b" style="background:#c16c5b"></span>
<span class="swatch" title="15: #e89973" style="background:#e89973"></span>
</div>

## Famicube

`use_palette("famicube")` — 64 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #e03c28" style="background:#e03c28"></span>
<span class="swatch" title="2: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="3: #d7d7d7" style="background:#d7d7d7"></span>
<span class="swatch" title="4: #a8a8a8" style="background:#a8a8a8"></span>
<span class="swatch" title="5: #7b7b7b" style="background:#7b7b7b"></span>
<span class="swatch" title="6: #343434" style="background:#343434"></span>
<span class="swatch" title="7: #151515" style="background:#151515"></span>
<span class="swatch" title="8: #0d2030" style="background:#0d2030"></span>
<span class="swatch" title="9: #415d66" style="background:#415d66"></span>
<span class="swatch" title="10: #71a6a1" style="background:#71a6a1"></span>
<span class="swatch" title="11: #bdffca" style="background:#bdffca"></span>
<span class="swatch" title="12: #25e2cd" style="background:#25e2cd"></span>
<span class="swatch" title="13: #0a98ac" style="background:#0a98ac"></span>
<span class="swatch" title="14: #005280" style="background:#005280"></span>
<span class="swatch" title="15: #00604b" style="background:#00604b"></span>
<span class="swatch" title="16: #20b562" style="background:#20b562"></span>
<span class="swatch" title="17: #58d332" style="background:#58d332"></span>
<span class="swatch" title="18: #139d08" style="background:#139d08"></span>
<span class="swatch" title="19: #004e00" style="background:#004e00"></span>
<span class="swatch" title="20: #172808" style="background:#172808"></span>
<span class="swatch" title="21: #376d03" style="background:#376d03"></span>
<span class="swatch" title="22: #6ab417" style="background:#6ab417"></span>
<span class="swatch" title="23: #8cd612" style="background:#8cd612"></span>
<span class="swatch" title="24: #beeb71" style="background:#beeb71"></span>
<span class="swatch" title="25: #eeffa9" style="background:#eeffa9"></span>
<span class="swatch" title="26: #b6c121" style="background:#b6c121"></span>
<span class="swatch" title="27: #939717" style="background:#939717"></span>
<span class="swatch" title="28: #cc8f15" style="background:#cc8f15"></span>
<span class="swatch" title="29: #ffbb31" style="background:#ffbb31"></span>
<span class="swatch" title="30: #ffe737" style="background:#ffe737"></span>
<span class="swatch" title="31: #f68f37" style="background:#f68f37"></span>
<span class="swatch" title="32: #ad4e1a" style="background:#ad4e1a"></span>
<span class="swatch" title="33: #231712" style="background:#231712"></span>
<span class="swatch" title="34: #5c3c0d" style="background:#5c3c0d"></span>
<span class="swatch" title="35: #ae6c37" style="background:#ae6c37"></span>
<span class="swatch" title="36: #c59782" style="background:#c59782"></span>
<span class="swatch" title="37: #e2d7b5" style="background:#e2d7b5"></span>
<span class="swatch" title="38: #4f1507" style="background:#4f1507"></span>
<span class="swatch" title="39: #823c3d" style="background:#823c3d"></span>
<span class="swatch" title="40: #da655e" style="background:#da655e"></span>
<span class="swatch" title="41: #e18289" style="background:#e18289"></span>
<span class="swatch" title="42: #f5b784" style="background:#f5b784"></span>
<span class="swatch" title="43: #ffe9c5" style="background:#ffe9c5"></span>
<span class="swatch" title="44: #ff82ce" style="background:#ff82ce"></span>
<span class="swatch" title="45: #cf3c71" style="background:#cf3c71"></span>
<span class="swatch" title="46: #871646" style="background:#871646"></span>
<span class="swatch" title="47: #a328b3" style="background:#a328b3"></span>
<span class="swatch" title="48: #cc69e4" style="background:#cc69e4"></span>
<span class="swatch" title="49: #d59cfc" style="background:#d59cfc"></span>
<span class="swatch" title="50: #fec9ed" style="background:#fec9ed"></span>
<span class="swatch" title="51: #e2c9ff" style="background:#e2c9ff"></span>
<span class="swatch" title="52: #a675fe" style="background:#a675fe"></span>
<span class="swatch" title="53: #6a31ca" style="background:#6a31ca"></span>
<span class="swatch" title="54: #5a1991" style="background:#5a1991"></span>
<span class="swatch" title="55: #211640" style="background:#211640"></span>
<span class="swatch" title="56: #3d34a5" style="background:#3d34a5"></span>
<span class="swatch" title="57: #6264dc" style="background:#6264dc"></span>
<span class="swatch" title="58: #9ba0ef" style="background:#9ba0ef"></span>
<span class="swatch" title="59: #98dcff" style="background:#98dcff"></span>
<span class="swatch" title="60: #5ba8ff" style="background:#5ba8ff"></span>
<span class="swatch" title="61: #0a89ff" style="background:#0a89ff"></span>
<span class="swatch" title="62: #024aca" style="background:#024aca"></span>
<span class="swatch" title="63: #00177d" style="background:#00177d"></span>
</div>

## Fantasy 24

`use_palette("fantasy_24")` — 24 colors

<div class="palette">
<span class="swatch" title="0: #1f240a" style="background:#1f240a"></span>
<span class="swatch" title="1: #39571c" style="background:#39571c"></span>
<span class="swatch" title="2: #a58c27" style="background:#a58c27"></span>
<span class="swatch" title="3: #efac28" style="background:#efac28"></span>
<span class="swatch" title="4: #efd8a1" style="background:#efd8a1"></span>
<span class="swatch" title="5: #ab5c1c" style="background:#ab5c1c"></span>
<span class="swatch" title="6: #183f39" style="background:#183f39"></span>
<span class="swatch" title="7: #ef692f" style="background:#ef692f"></span>
<span class="swatch" title="8: #efb775" style="background:#efb775"></span>
<span class="swatch" title="9: #a56243" style="background:#a56243"></span>
<span class="swatch" title="10: #773421" style="background:#773421"></span>
<span class="swatch" title="11: #724113" style="background:#724113"></span>
<span class="swatch" title="12: #2a1d0d" style="background:#2a1d0d"></span>
<span class="swatch" title="13: #392a1c" style="background:#392a1c"></span>
<span class="swatch" title="14: #684c3c" style="background:#684c3c"></span>
<span class="swatch" title="15: #927e6a" style="background:#927e6a"></span>
<span class="swatch" title="16: #276468" style="background:#276468"></span>
<span class="swatch" title="17: #ef3a0c" style="background:#ef3a0c"></span>
<span class="swatch" title="18: #45230d" style="background:#45230d"></span>
<span class="swatch" title="19: #3c9f9c" style="background:#3c9f9c"></span>
<span class="swatch" title="20: #9b1a0a" style="background:#9b1a0a"></span>
<span class="swatch" title="21: #36170c" style="background:#36170c"></span>
<span class="swatch" title="22: #550f0a" style="background:#550f0a"></span>
<span class="swatch" title="23: #300f0a" style="background:#300f0a"></span>
</div>

## Faraway48

`use_palette("faraway48")` — 48 colors

<div class="palette">
<span class="swatch" title="0: #0d0709" style="background:#0d0709"></span>
<span class="swatch" title="1: #220915" style="background:#220915"></span>
<span class="swatch" title="2: #3d0518" style="background:#3d0518"></span>
<span class="swatch" title="3: #ad1818" style="background:#ad1818"></span>
<span class="swatch" title="4: #d94f0c" style="background:#d94f0c"></span>
<span class="swatch" title="5: #ff980e" style="background:#ff980e"></span>
<span class="swatch" title="6: #fff959" style="background:#fff959"></span>
<span class="swatch" title="7: #d6f668" style="background:#d6f668"></span>
<span class="swatch" title="8: #8ffa37" style="background:#8ffa37"></span>
<span class="swatch" title="9: #169e26" style="background:#169e26"></span>
<span class="swatch" title="10: #1c5d2a" style="background:#1c5d2a"></span>
<span class="swatch" title="11: #0d3822" style="background:#0d3822"></span>
<span class="swatch" title="12: #0d1d1f" style="background:#0d1d1f"></span>
<span class="swatch" title="13: #00191f" style="background:#00191f"></span>
<span class="swatch" title="14: #003138" style="background:#003138"></span>
<span class="swatch" title="15: #006457" style="background:#006457"></span>
<span class="swatch" title="16: #008d6d" style="background:#008d6d"></span>
<span class="swatch" title="17: #08c49f" style="background:#08c49f"></span>
<span class="swatch" title="18: #59dfb0" style="background:#59dfb0"></span>
<span class="swatch" title="19: #aae8ca" style="background:#aae8ca"></span>
<span class="swatch" title="20: #45c5d9" style="background:#45c5d9"></span>
<span class="swatch" title="21: #2595cf" style="background:#2595cf"></span>
<span class="swatch" title="22: #025999" style="background:#025999"></span>
<span class="swatch" title="23: #193a91" style="background:#193a91"></span>
<span class="swatch" title="24: #101438" style="background:#101438"></span>
<span class="swatch" title="25: #090d19" style="background:#090d19"></span>
<span class="swatch" title="26: #151538" style="background:#151538"></span>
<span class="swatch" title="27: #2e264d" style="background:#2e264d"></span>
<span class="swatch" title="28: #562e73" style="background:#562e73"></span>
<span class="swatch" title="29: #a03a9e" style="background:#a03a9e"></span>
<span class="swatch" title="30: #c8658f" style="background:#c8658f"></span>
<span class="swatch" title="31: #edafb9" style="background:#edafb9"></span>
<span class="swatch" title="32: #f7c8d9" style="background:#f7c8d9"></span>
<span class="swatch" title="33: #f7f3ce" style="background:#f7f3ce"></span>
<span class="swatch" title="34: #f1e4af" style="background:#f1e4af"></span>
<span class="swatch" title="35: #e7cc93" style="background:#e7cc93"></span>
<span class="swatch" title="36: #d19e71" style="background:#d19e71"></span>
<span class="swatch" title="37: #9e6d4f" style="background:#9e6d4f"></span>
<span class="swatch" title="38: #73322e" style="background:#73322e"></span>
<span class="swatch" title="39: #4d2630" style="background:#4d2630"></span>
<span class="swatch" title="40: #241720" style="background:#241720"></span>
<span class="swatch" title="41: #1c1216" style="background:#1c1216"></span>
<span class="swatch" title="42: #101112" style="background:#101112"></span>
<span class="swatch" title="43: #202223" style="background:#202223"></span>
<span class="swatch" title="44: #586162" style="background:#586162"></span>
<span class="swatch" title="45: #a9b0b0" style="background:#a9b0b0"></span>
<span class="swatch" title="46: #d2d6d7" style="background:#d2d6d7"></span>
<span class="swatch" title="47: #f1f2f1" style="background:#f1f2f1"></span>
</div>

## Fleja Master Palette

`use_palette("fleja_master_palette")` — 33 colors

<div class="palette">
<span class="swatch" title="0: #1f1833" style="background:#1f1833"></span>
<span class="swatch" title="1: #2b2e42" style="background:#2b2e42"></span>
<span class="swatch" title="2: #414859" style="background:#414859"></span>
<span class="swatch" title="3: #68717a" style="background:#68717a"></span>
<span class="swatch" title="4: #90a1a8" style="background:#90a1a8"></span>
<span class="swatch" title="5: #b6cbcf" style="background:#b6cbcf"></span>
<span class="swatch" title="6: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="7: #fcbf8a" style="background:#fcbf8a"></span>
<span class="swatch" title="8: #b58057" style="background:#b58057"></span>
<span class="swatch" title="9: #8a503e" style="background:#8a503e"></span>
<span class="swatch" title="10: #5c3a41" style="background:#5c3a41"></span>
<span class="swatch" title="11: #c93038" style="background:#c93038"></span>
<span class="swatch" title="12: #de6a38" style="background:#de6a38"></span>
<span class="swatch" title="13: #ffad3b" style="background:#ffad3b"></span>
<span class="swatch" title="14: #ffe596" style="background:#ffe596"></span>
<span class="swatch" title="15: #fcf960" style="background:#fcf960"></span>
<span class="swatch" title="16: #b4d645" style="background:#b4d645"></span>
<span class="swatch" title="17: #51c43f" style="background:#51c43f"></span>
<span class="swatch" title="18: #309c63" style="background:#309c63"></span>
<span class="swatch" title="19: #236d7a" style="background:#236d7a"></span>
<span class="swatch" title="20: #264f6e" style="background:#264f6e"></span>
<span class="swatch" title="21: #233663" style="background:#233663"></span>
<span class="swatch" title="22: #417291" style="background:#417291"></span>
<span class="swatch" title="23: #4c93ad" style="background:#4c93ad"></span>
<span class="swatch" title="24: #63c2c9" style="background:#63c2c9"></span>
<span class="swatch" title="25: #94d2d4" style="background:#94d2d4"></span>
<span class="swatch" title="26: #b8fdff" style="background:#b8fdff"></span>
<span class="swatch" title="27: #3c2940" style="background:#3c2940"></span>
<span class="swatch" title="28: #46275c" style="background:#46275c"></span>
<span class="swatch" title="29: #826481" style="background:#826481"></span>
<span class="swatch" title="30: #f7a48b" style="background:#f7a48b"></span>
<span class="swatch" title="31: #c27182" style="background:#c27182"></span>
<span class="swatch" title="32: #852d66" style="background:#852d66"></span>
</div>

## Florentine24

`use_palette("florentine24")` — 24 colors

<div class="palette">
<span class="swatch" title="0: #175145" style="background:#175145"></span>
<span class="swatch" title="1: #2e8065" style="background:#2e8065"></span>
<span class="swatch" title="2: #51b341" style="background:#51b341"></span>
<span class="swatch" title="3: #9bd547" style="background:#9bd547"></span>
<span class="swatch" title="4: #fff971" style="background:#fff971"></span>
<span class="swatch" title="5: #ff7f4f" style="background:#ff7f4f"></span>
<span class="swatch" title="6: #ff4f4f" style="background:#ff4f4f"></span>
<span class="swatch" title="7: #ee3046" style="background:#ee3046"></span>
<span class="swatch" title="8: #df426e" style="background:#df426e"></span>
<span class="swatch" title="9: #a62654" style="background:#a62654"></span>
<span class="swatch" title="10: #621b52" style="background:#621b52"></span>
<span class="swatch" title="11: #371848" style="background:#371848"></span>
<span class="swatch" title="12: #0c082a" style="background:#0c082a"></span>
<span class="swatch" title="13: #261152" style="background:#261152"></span>
<span class="swatch" title="14: #272573" style="background:#272573"></span>
<span class="swatch" title="15: #4876bb" style="background:#4876bb"></span>
<span class="swatch" title="16: #7fd3e6" style="background:#7fd3e6"></span>
<span class="swatch" title="17: #c7f7f2" style="background:#c7f7f2"></span>
<span class="swatch" title="18: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="19: #d29c8a" style="background:#d29c8a"></span>
<span class="swatch" title="20: #9e4d4d" style="background:#9e4d4d"></span>
<span class="swatch" title="21: #712835" style="background:#712835"></span>
<span class="swatch" title="22: #5d1835" style="background:#5d1835"></span>
<span class="swatch" title="23: #35082a" style="background:#35082a"></span>
</div>

## Funny31

`use_palette("funny31")` — 31 colors

<div class="palette">
<span class="swatch" title="0: #180a24" style="background:#180a24"></span>
<span class="swatch" title="1: #3b3542" style="background:#3b3542"></span>
<span class="swatch" title="2: #565466" style="background:#565466"></span>
<span class="swatch" title="3: #757785" style="background:#757785"></span>
<span class="swatch" title="4: #929ca3" style="background:#929ca3"></span>
<span class="swatch" title="5: #bdc4c9" style="background:#bdc4c9"></span>
<span class="swatch" title="6: #fff8f0" style="background:#fff8f0"></span>
<span class="swatch" title="7: #ebd2a7" style="background:#ebd2a7"></span>
<span class="swatch" title="8: #e6ad87" style="background:#e6ad87"></span>
<span class="swatch" title="9: #d97368" style="background:#d97368"></span>
<span class="swatch" title="10: #c94556" style="background:#c94556"></span>
<span class="swatch" title="11: #a12758" style="background:#a12758"></span>
<span class="swatch" title="12: #701664" style="background:#701664"></span>
<span class="swatch" title="13: #94357b" style="background:#94357b"></span>
<span class="swatch" title="14: #b05674" style="background:#b05674"></span>
<span class="swatch" title="15: #c2808b" style="background:#c2808b"></span>
<span class="swatch" title="16: #d6a9a9" style="background:#d6a9a9"></span>
<span class="swatch" title="17: #b37254" style="background:#b37254"></span>
<span class="swatch" title="18: #9e5542" style="background:#9e5542"></span>
<span class="swatch" title="19: #783838" style="background:#783838"></span>
<span class="swatch" title="20: #521e2f" style="background:#521e2f"></span>
<span class="swatch" title="21: #101657" style="background:#101657"></span>
<span class="swatch" title="22: #263973" style="background:#263973"></span>
<span class="swatch" title="23: #385382" style="background:#385382"></span>
<span class="swatch" title="24: #286c78" style="background:#286c78"></span>
<span class="swatch" title="25: #4b798f" style="background:#4b798f"></span>
<span class="swatch" title="26: #649da1" style="background:#649da1"></span>
<span class="swatch" title="27: #bbc499" style="background:#bbc499"></span>
<span class="swatch" title="28: #89a66d" style="background:#89a66d"></span>
<span class="swatch" title="29: #509950" style="background:#509950"></span>
<span class="swatch" title="30: #39825b" style="background:#39825b"></span>
</div>

## Galaxy Flame

`use_palette("galaxy_flame")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #699fad" style="background:#699fad"></span>
<span class="swatch" title="1: #3a708e" style="background:#3a708e"></span>
<span class="swatch" title="2: #2b454f" style="background:#2b454f"></span>
<span class="swatch" title="3: #111215" style="background:#111215"></span>
<span class="swatch" title="4: #151d1a" style="background:#151d1a"></span>
<span class="swatch" title="5: #1d3230" style="background:#1d3230"></span>
<span class="swatch" title="6: #314e3f" style="background:#314e3f"></span>
<span class="swatch" title="7: #4f5d42" style="background:#4f5d42"></span>
<span class="swatch" title="8: #9a9f87" style="background:#9a9f87"></span>
<span class="swatch" title="9: #ede6cb" style="background:#ede6cb"></span>
<span class="swatch" title="10: #f5d893" style="background:#f5d893"></span>
<span class="swatch" title="11: #e8b26f" style="background:#e8b26f"></span>
<span class="swatch" title="12: #b6834c" style="background:#b6834c"></span>
<span class="swatch" title="13: #704d2b" style="background:#704d2b"></span>
<span class="swatch" title="14: #40231e" style="background:#40231e"></span>
<span class="swatch" title="15: #151015" style="background:#151015"></span>
</div>

## Gob 48

`use_palette("gob_48")` — 48 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #140f24" style="background:#140f24"></span>
<span class="swatch" title="2: #221f3e" style="background:#221f3e"></span>
<span class="swatch" title="3: #34315b" style="background:#34315b"></span>
<span class="swatch" title="4: #3b486d" style="background:#3b486d"></span>
<span class="swatch" title="5: #4c6589" style="background:#4c6589"></span>
<span class="swatch" title="6: #60839c" style="background:#60839c"></span>
<span class="swatch" title="7: #7aa2b0" style="background:#7aa2b0"></span>
<span class="swatch" title="8: #9cbbc1" style="background:#9cbbc1"></span>
<span class="swatch" title="9: #c0dadc" style="background:#c0dadc"></span>
<span class="swatch" title="10: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="11: #aaf8ff" style="background:#aaf8ff"></span>
<span class="swatch" title="12: #75d1e4" style="background:#75d1e4"></span>
<span class="swatch" title="13: #5aa6bf" style="background:#5aa6bf"></span>
<span class="swatch" title="14: #5a8cb0" style="background:#5a8cb0"></span>
<span class="swatch" title="15: #483b6d" style="background:#483b6d"></span>
<span class="swatch" title="16: #66408d" style="background:#66408d"></span>
<span class="swatch" title="17: #964fad" style="background:#964fad"></span>
<span class="swatch" title="18: #c26cc9" style="background:#c26cc9"></span>
<span class="swatch" title="19: #e089e0" style="background:#e089e0"></span>
<span class="swatch" title="20: #ffc3f0" style="background:#ffc3f0"></span>
<span class="swatch" title="21: #203040" style="background:#203040"></span>
<span class="swatch" title="22: #174646" style="background:#174646"></span>
<span class="swatch" title="23: #206437" style="background:#206437"></span>
<span class="swatch" title="24: #3a892a" style="background:#3a892a"></span>
<span class="swatch" title="25: #5bb031" style="background:#5bb031"></span>
<span class="swatch" title="26: #9bd32c" style="background:#9bd32c"></span>
<span class="swatch" title="27: #cced27" style="background:#cced27"></span>
<span class="swatch" title="28: #fff15e" style="background:#fff15e"></span>
<span class="swatch" title="29: #ffce3b" style="background:#ffce3b"></span>
<span class="swatch" title="30: #e49b35" style="background:#e49b35"></span>
<span class="swatch" title="31: #cc702f" style="background:#cc702f"></span>
<span class="swatch" title="32: #b14926" style="background:#b14926"></span>
<span class="swatch" title="33: #952008" style="background:#952008"></span>
<span class="swatch" title="34: #760811" style="background:#760811"></span>
<span class="swatch" title="35: #490a15" style="background:#490a15"></span>
<span class="swatch" title="36: #2e040f" style="background:#2e040f"></span>
<span class="swatch" title="37: #a00c0c" style="background:#a00c0c"></span>
<span class="swatch" title="38: #be3333" style="background:#be3333"></span>
<span class="swatch" title="39: #d35858" style="background:#d35858"></span>
<span class="swatch" title="40: #dd9393" style="background:#dd9393"></span>
<span class="swatch" title="41: #581d17" style="background:#581d17"></span>
<span class="swatch" title="42: #72311b" style="background:#72311b"></span>
<span class="swatch" title="43: #954f2c" style="background:#954f2c"></span>
<span class="swatch" title="44: #a76b3f" style="background:#a76b3f"></span>
<span class="swatch" title="45: #c18c56" style="background:#c18c56"></span>
<span class="swatch" title="46: #dcab7a" style="background:#dcab7a"></span>
<span class="swatch" title="47: #edd5a5" style="background:#edd5a5"></span>
</div>

## Gora63

`use_palette("gora63")` — 63 colors

<div class="palette">
<span class="swatch" title="0: #141b27" style="background:#141b27"></span>
<span class="swatch" title="1: #1e2734" style="background:#1e2734"></span>
<span class="swatch" title="2: #2b3545" style="background:#2b3545"></span>
<span class="swatch" title="3: #3a4959" style="background:#3a4959"></span>
<span class="swatch" title="4: #506275" style="background:#506275"></span>
<span class="swatch" title="5: #6c8294" style="background:#6c8294"></span>
<span class="swatch" title="6: #859aa9" style="background:#859aa9"></span>
<span class="swatch" title="7: #b3c2ca" style="background:#b3c2ca"></span>
<span class="swatch" title="8: #dae1e5" style="background:#dae1e5"></span>
<span class="swatch" title="9: #121532" style="background:#121532"></span>
<span class="swatch" title="10: #1b2343" style="background:#1b2343"></span>
<span class="swatch" title="11: #203457" style="background:#203457"></span>
<span class="swatch" title="12: #264a71" style="background:#264a71"></span>
<span class="swatch" title="13: #2d5b85" style="background:#2d5b85"></span>
<span class="swatch" title="14: #3483b0" style="background:#3483b0"></span>
<span class="swatch" title="15: #49b2d3" style="background:#49b2d3"></span>
<span class="swatch" title="16: #82d8e9" style="background:#82d8e9"></span>
<span class="swatch" title="17: #bdeef7" style="background:#bdeef7"></span>
<span class="swatch" title="18: #142427" style="background:#142427"></span>
<span class="swatch" title="19: #1c3030" style="background:#1c3030"></span>
<span class="swatch" title="20: #224635" style="background:#224635"></span>
<span class="swatch" title="21: #286345" style="background:#286345"></span>
<span class="swatch" title="22: #2a7148" style="background:#2a7148"></span>
<span class="swatch" title="23: #2c9f4c" style="background:#2c9f4c"></span>
<span class="swatch" title="24: #68d150" style="background:#68d150"></span>
<span class="swatch" title="25: #c5f57d" style="background:#c5f57d"></span>
<span class="swatch" title="26: #e8fab6" style="background:#e8fab6"></span>
<span class="swatch" title="27: #2b1424" style="background:#2b1424"></span>
<span class="swatch" title="28: #361b28" style="background:#361b28"></span>
<span class="swatch" title="29: #4e2c32" style="background:#4e2c32"></span>
<span class="swatch" title="30: #754442" style="background:#754442"></span>
<span class="swatch" title="31: #884e48" style="background:#884e48"></span>
<span class="swatch" title="32: #9b614f" style="background:#9b614f"></span>
<span class="swatch" title="33: #bb885a" style="background:#bb885a"></span>
<span class="swatch" title="34: #dfbb89" style="background:#dfbb89"></span>
<span class="swatch" title="35: #f0e0b8" style="background:#f0e0b8"></span>
<span class="swatch" title="36: #301723" style="background:#301723"></span>
<span class="swatch" title="37: #3d1f28" style="background:#3d1f28"></span>
<span class="swatch" title="38: #4d282c" style="background:#4d282c"></span>
<span class="swatch" title="39: #6f3b31" style="background:#6f3b31"></span>
<span class="swatch" title="40: #8e4e30" style="background:#8e4e30"></span>
<span class="swatch" title="41: #b46a29" style="background:#b46a29"></span>
<span class="swatch" title="42: #e19f3e" style="background:#e19f3e"></span>
<span class="swatch" title="43: #f0c069" style="background:#f0c069"></span>
<span class="swatch" title="44: #f7e198" style="background:#f7e198"></span>
<span class="swatch" title="45: #2c1329" style="background:#2c1329"></span>
<span class="swatch" title="46: #361630" style="background:#361630"></span>
<span class="swatch" title="47: #521e3a" style="background:#521e3a"></span>
<span class="swatch" title="48: #7b2536" style="background:#7b2536"></span>
<span class="swatch" title="49: #a8372d" style="background:#a8372d"></span>
<span class="swatch" title="50: #d85f28" style="background:#d85f28"></span>
<span class="swatch" title="51: #f08e39" style="background:#f08e39"></span>
<span class="swatch" title="52: #fbc85e" style="background:#fbc85e"></span>
<span class="swatch" title="53: #fce886" style="background:#fce886"></span>
<span class="swatch" title="54: #1c1729" style="background:#1c1729"></span>
<span class="swatch" title="55: #2a2135" style="background:#2a2135"></span>
<span class="swatch" title="56: #3e2a49" style="background:#3e2a49"></span>
<span class="swatch" title="57: #65335f" style="background:#65335f"></span>
<span class="swatch" title="58: #9d3a78" style="background:#9d3a78"></span>
<span class="swatch" title="59: #c64782" style="background:#c64782"></span>
<span class="swatch" title="60: #d86a9f" style="background:#d86a9f"></span>
<span class="swatch" title="61: #e7a0b4" style="background:#e7a0b4"></span>
<span class="swatch" title="62: #f2cdce" style="background:#f2cdce"></span>
</div>

## Hept32

`use_palette("hept32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #180d2f" style="background:#180d2f"></span>
<span class="swatch" title="2: #353658" style="background:#353658"></span>
<span class="swatch" title="3: #686b72" style="background:#686b72"></span>
<span class="swatch" title="4: #8b97b6" style="background:#8b97b6"></span>
<span class="swatch" title="5: #c5cddb" style="background:#c5cddb"></span>
<span class="swatch" title="6: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="7: #5ee9e9" style="background:#5ee9e9"></span>
<span class="swatch" title="8: #2890dc" style="background:#2890dc"></span>
<span class="swatch" title="9: #1831a7" style="background:#1831a7"></span>
<span class="swatch" title="10: #053239" style="background:#053239"></span>
<span class="swatch" title="11: #005f41" style="background:#005f41"></span>
<span class="swatch" title="12: #08b23b" style="background:#08b23b"></span>
<span class="swatch" title="13: #47f641" style="background:#47f641"></span>
<span class="swatch" title="14: #e8ff75" style="background:#e8ff75"></span>
<span class="swatch" title="15: #fbbe82" style="background:#fbbe82"></span>
<span class="swatch" title="16: #de9751" style="background:#de9751"></span>
<span class="swatch" title="17: #b66831" style="background:#b66831"></span>
<span class="swatch" title="18: #8a4926" style="background:#8a4926"></span>
<span class="swatch" title="19: #461c14" style="background:#461c14"></span>
<span class="swatch" title="20: #1e090d" style="background:#1e090d"></span>
<span class="swatch" title="21: #720d0d" style="background:#720d0d"></span>
<span class="swatch" title="22: #813704" style="background:#813704"></span>
<span class="swatch" title="23: #da2424" style="background:#da2424"></span>
<span class="swatch" title="24: #ef6e10" style="background:#ef6e10"></span>
<span class="swatch" title="25: #ecab11" style="background:#ecab11"></span>
<span class="swatch" title="26: #ece910" style="background:#ece910"></span>
<span class="swatch" title="27: #f78d8d" style="background:#f78d8d"></span>
<span class="swatch" title="28: #f94e6d" style="background:#f94e6d"></span>
<span class="swatch" title="29: #c12458" style="background:#c12458"></span>
<span class="swatch" title="30: #841252" style="background:#841252"></span>
<span class="swatch" title="31: #3d083b" style="background:#3d083b"></span>
</div>

## Hot Sand 6

`use_palette("hot_sand_6")` — 6 colors

<div class="palette">
<span class="swatch" title="0: #3a0000" style="background:#3a0000"></span>
<span class="swatch" title="1: #590000" style="background:#590000"></span>
<span class="swatch" title="2: #7c0300" style="background:#7c0300"></span>
<span class="swatch" title="3: #c02b18" style="background:#c02b18"></span>
<span class="swatch" title="4: #e04217" style="background:#e04217"></span>
<span class="swatch" title="5: #f26d1f" style="background:#f26d1f"></span>
</div>

## Ice Cream Gb

`use_palette("ice_cream_gb")` — 4 colors

<div class="palette">
<span class="swatch" title="0: #7c3f58" style="background:#7c3f58"></span>
<span class="swatch" title="1: #eb6b6f" style="background:#eb6b6f"></span>
<span class="swatch" title="2: #f9a875" style="background:#f9a875"></span>
<span class="swatch" title="3: #fff6d3" style="background:#fff6d3"></span>
</div>

## Inkpink

`use_palette("inkpink")` — 6 colors

<div class="palette">
<span class="swatch" title="0: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="1: #fe6c90" style="background:#fe6c90"></span>
<span class="swatch" title="2: #d03791" style="background:#d03791"></span>
<span class="swatch" title="3: #87286a" style="background:#87286a"></span>
<span class="swatch" title="4: #452459" style="background:#452459"></span>
<span class="swatch" title="5: #260d34" style="background:#260d34"></span>
</div>

## Journey

`use_palette("journey")` — 64 colors

<div class="palette">
<span class="swatch" title="0: #050914" style="background:#050914"></span>
<span class="swatch" title="1: #110524" style="background:#110524"></span>
<span class="swatch" title="2: #3b063a" style="background:#3b063a"></span>
<span class="swatch" title="3: #691749" style="background:#691749"></span>
<span class="swatch" title="4: #9c3247" style="background:#9c3247"></span>
<span class="swatch" title="5: #d46453" style="background:#d46453"></span>
<span class="swatch" title="6: #f5a15d" style="background:#f5a15d"></span>
<span class="swatch" title="7: #ffcf8e" style="background:#ffcf8e"></span>
<span class="swatch" title="8: #ff7a7d" style="background:#ff7a7d"></span>
<span class="swatch" title="9: #ff417d" style="background:#ff417d"></span>
<span class="swatch" title="10: #d61a88" style="background:#d61a88"></span>
<span class="swatch" title="11: #94007a" style="background:#94007a"></span>
<span class="swatch" title="12: #42004e" style="background:#42004e"></span>
<span class="swatch" title="13: #220029" style="background:#220029"></span>
<span class="swatch" title="14: #100726" style="background:#100726"></span>
<span class="swatch" title="15: #25082c" style="background:#25082c"></span>
<span class="swatch" title="16: #3d1132" style="background:#3d1132"></span>
<span class="swatch" title="17: #73263d" style="background:#73263d"></span>
<span class="swatch" title="18: #bd4035" style="background:#bd4035"></span>
<span class="swatch" title="19: #ed7b39" style="background:#ed7b39"></span>
<span class="swatch" title="20: #ffb84a" style="background:#ffb84a"></span>
<span class="swatch" title="21: #fff540" style="background:#fff540"></span>
<span class="swatch" title="22: #c6d831" style="background:#c6d831"></span>
<span class="swatch" title="23: #77b02a" style="background:#77b02a"></span>
<span class="swatch" title="24: #429058" style="background:#429058"></span>
<span class="swatch" title="25: #2c645e" style="background:#2c645e"></span>
<span class="swatch" title="26: #153c4a" style="background:#153c4a"></span>
<span class="swatch" title="27: #052137" style="background:#052137"></span>
<span class="swatch" title="28: #0e0421" style="background:#0e0421"></span>
<span class="swatch" title="29: #0c0b42" style="background:#0c0b42"></span>
<span class="swatch" title="30: #032769" style="background:#032769"></span>
<span class="swatch" title="31: #144491" style="background:#144491"></span>
<span class="swatch" title="32: #488bd4" style="background:#488bd4"></span>
<span class="swatch" title="33: #78d7ff" style="background:#78d7ff"></span>
<span class="swatch" title="34: #b0fff1" style="background:#b0fff1"></span>
<span class="swatch" title="35: #faffff" style="background:#faffff"></span>
<span class="swatch" title="36: #c7d4e1" style="background:#c7d4e1"></span>
<span class="swatch" title="37: #928fb8" style="background:#928fb8"></span>
<span class="swatch" title="38: #5b537d" style="background:#5b537d"></span>
<span class="swatch" title="39: #392946" style="background:#392946"></span>
<span class="swatch" title="40: #24142c" style="background:#24142c"></span>
<span class="swatch" title="41: #0e0f2c" style="background:#0e0f2c"></span>
<span class="swatch" title="42: #132243" style="background:#132243"></span>
<span class="swatch" title="43: #1a466b" style="background:#1a466b"></span>
<span class="swatch" title="44: #10908e" style="background:#10908e"></span>
<span class="swatch" title="45: #28c074" style="background:#28c074"></span>
<span class="swatch" title="46: #3dff6e" style="background:#3dff6e"></span>
<span class="swatch" title="47: #f8ffb8" style="background:#f8ffb8"></span>
<span class="swatch" title="48: #f0c297" style="background:#f0c297"></span>
<span class="swatch" title="49: #cf968c" style="background:#cf968c"></span>
<span class="swatch" title="50: #8f5765" style="background:#8f5765"></span>
<span class="swatch" title="51: #52294b" style="background:#52294b"></span>
<span class="swatch" title="52: #0f022e" style="background:#0f022e"></span>
<span class="swatch" title="53: #35003b" style="background:#35003b"></span>
<span class="swatch" title="54: #64004c" style="background:#64004c"></span>
<span class="swatch" title="55: #9b0e3e" style="background:#9b0e3e"></span>
<span class="swatch" title="56: #d41e3c" style="background:#d41e3c"></span>
<span class="swatch" title="57: #ed4c40" style="background:#ed4c40"></span>
<span class="swatch" title="58: #ff9757" style="background:#ff9757"></span>
<span class="swatch" title="59: #d4662f" style="background:#d4662f"></span>
<span class="swatch" title="60: #9c341a" style="background:#9c341a"></span>
<span class="swatch" title="61: #691b22" style="background:#691b22"></span>
<span class="swatch" title="62: #450c28" style="background:#450c28"></span>
<span class="swatch" title="63: #2d002e" style="background:#2d002e"></span>
</div>

## Juice56

`use_palette("juice56")` — 56 colors

<div class="palette">
<span class="swatch" title="0: #000005" style="background:#000005"></span>
<span class="swatch" title="1: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="2: #c8e1eb" style="background:#c8e1eb"></span>
<span class="swatch" title="3: #a5becd" style="background:#a5becd"></span>
<span class="swatch" title="4: #7891a5" style="background:#7891a5"></span>
<span class="swatch" title="5: #55647d" style="background:#55647d"></span>
<span class="swatch" title="6: #37415a" style="background:#37415a"></span>
<span class="swatch" title="7: #191e3c" style="background:#191e3c"></span>
<span class="swatch" title="8: #14465a" style="background:#14465a"></span>
<span class="swatch" title="9: #0f7373" style="background:#0f7373"></span>
<span class="swatch" title="10: #0fa569" style="background:#0fa569"></span>
<span class="swatch" title="11: #41cd73" style="background:#41cd73"></span>
<span class="swatch" title="12: #73ff73" style="background:#73ff73"></span>
<span class="swatch" title="13: #dc9b78" style="background:#dc9b78"></span>
<span class="swatch" title="14: #b26247" style="background:#b26247"></span>
<span class="swatch" title="15: #8c3c32" style="background:#8c3c32"></span>
<span class="swatch" title="16: #5a1423" style="background:#5a1423"></span>
<span class="swatch" title="17: #370a14" style="background:#370a14"></span>
<span class="swatch" title="18: #ffd2a5" style="background:#ffd2a5"></span>
<span class="swatch" title="19: #f5a56e" style="background:#f5a56e"></span>
<span class="swatch" title="20: #e66e46" style="background:#e66e46"></span>
<span class="swatch" title="21: #c3412d" style="background:#c3412d"></span>
<span class="swatch" title="22: #8c2323" style="background:#8c2323"></span>
<span class="swatch" title="23: #410041" style="background:#410041"></span>
<span class="swatch" title="24: #7d0041" style="background:#7d0041"></span>
<span class="swatch" title="25: #aa143c" style="background:#aa143c"></span>
<span class="swatch" title="26: #d72d2d" style="background:#d72d2d"></span>
<span class="swatch" title="27: #f06923" style="background:#f06923"></span>
<span class="swatch" title="28: #ffaa32" style="background:#ffaa32"></span>
<span class="swatch" title="29: #ffe65a" style="background:#ffe65a"></span>
<span class="swatch" title="30: #bed72d" style="background:#bed72d"></span>
<span class="swatch" title="31: #64a51e" style="background:#64a51e"></span>
<span class="swatch" title="32: #237d14" style="background:#237d14"></span>
<span class="swatch" title="33: #0f5519" style="background:#0f5519"></span>
<span class="swatch" title="34: #0f3223" style="background:#0f3223"></span>
<span class="swatch" title="35: #82ffe1" style="background:#82ffe1"></span>
<span class="swatch" title="36: #41d7d7" style="background:#41d7d7"></span>
<span class="swatch" title="37: #14a0cd" style="background:#14a0cd"></span>
<span class="swatch" title="38: #1469c3" style="background:#1469c3"></span>
<span class="swatch" title="39: #0f379b" style="background:#0f379b"></span>
<span class="swatch" title="40: #0f0f69" style="background:#0f0f69"></span>
<span class="swatch" title="41: #3c1e8c" style="background:#3c1e8c"></span>
<span class="swatch" title="42: #642db4" style="background:#642db4"></span>
<span class="swatch" title="43: #a041d7" style="background:#a041d7"></span>
<span class="swatch" title="44: #e65ae6" style="background:#e65ae6"></span>
<span class="swatch" title="45: #ff8cc8" style="background:#ff8cc8"></span>
<span class="swatch" title="46: #4b143c" style="background:#4b143c"></span>
<span class="swatch" title="47: #820a64" style="background:#820a64"></span>
<span class="swatch" title="48: #b4236e" style="background:#b4236e"></span>
<span class="swatch" title="49: #e65078" style="background:#e65078"></span>
<span class="swatch" title="50: #ff8c8c" style="background:#ff8c8c"></span>
<span class="swatch" title="51: #ffcdb4" style="background:#ffcdb4"></span>
<span class="swatch" title="52: #e69b96" style="background:#e69b96"></span>
<span class="swatch" title="53: #be6973" style="background:#be6973"></span>
<span class="swatch" title="54: #96465f" style="background:#96465f"></span>
<span class="swatch" title="55: #6e2850" style="background:#6e2850"></span>
</div>

## Kawaii16

`use_palette("kawaii16")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #65471e" style="background:#65471e"></span>
<span class="swatch" title="1: #b57075" style="background:#b57075"></span>
<span class="swatch" title="2: #dcab80" style="background:#dcab80"></span>
<span class="swatch" title="3: #f8d8ab" style="background:#f8d8ab"></span>
<span class="swatch" title="4: #b8aaaa" style="background:#b8aaaa"></span>
<span class="swatch" title="5: #fff5f5" style="background:#fff5f5"></span>
<span class="swatch" title="6: #fca5c2" style="background:#fca5c2"></span>
<span class="swatch" title="7: #ec4646" style="background:#ec4646"></span>
<span class="swatch" title="8: #ffa322" style="background:#ffa322"></span>
<span class="swatch" title="9: #f9fa93" style="background:#f9fa93"></span>
<span class="swatch" title="10: #7bc188" style="background:#7bc188"></span>
<span class="swatch" title="11: #8ed3f8" style="background:#8ed3f8"></span>
<span class="swatch" title="12: #5989a3" style="background:#5989a3"></span>
<span class="swatch" title="13: #d793fa" style="background:#d793fa"></span>
<span class="swatch" title="14: #74518e" style="background:#74518e"></span>
<span class="swatch" title="15: #1d173c" style="background:#1d173c"></span>
</div>

## Koni32

`use_palette("koni32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #0b0a0d" style="background:#0b0a0d"></span>
<span class="swatch" title="2: #161524" style="background:#161524"></span>
<span class="swatch" title="3: #222640" style="background:#222640"></span>
<span class="swatch" title="4: #2b4057" style="background:#2b4057"></span>
<span class="swatch" title="5: #306566" style="background:#306566"></span>
<span class="swatch" title="6: #34a870" style="background:#34a870"></span>
<span class="swatch" title="7: #49f25a" style="background:#49f25a"></span>
<span class="swatch" title="8: #a4ff63" style="background:#a4ff63"></span>
<span class="swatch" title="9: #fff240" style="background:#fff240"></span>
<span class="swatch" title="10: #f2a53f" style="background:#f2a53f"></span>
<span class="swatch" title="11: #cc7a47" style="background:#cc7a47"></span>
<span class="swatch" title="12: #f54025" style="background:#f54025"></span>
<span class="swatch" title="13: #a63a3a" style="background:#a63a3a"></span>
<span class="swatch" title="14: #995348" style="background:#995348"></span>
<span class="swatch" title="15: #733758" style="background:#733758"></span>
<span class="swatch" title="16: #4d2a49" style="background:#4d2a49"></span>
<span class="swatch" title="17: #46346a" style="background:#46346a"></span>
<span class="swatch" title="18: #8c2eb8" style="background:#8c2eb8"></span>
<span class="swatch" title="19: #f261da" style="background:#f261da"></span>
<span class="swatch" title="20: #ffa8d4" style="background:#ffa8d4"></span>
<span class="swatch" title="21: #b3dfff" style="background:#b3dfff"></span>
<span class="swatch" title="22: #70a5fa" style="background:#70a5fa"></span>
<span class="swatch" title="23: #407cff" style="background:#407cff"></span>
<span class="swatch" title="24: #1f50cc" style="background:#1f50cc"></span>
<span class="swatch" title="25: #213ea6" style="background:#213ea6"></span>
<span class="swatch" title="26: #272f66" style="background:#272f66"></span>
<span class="swatch" title="27: #414558" style="background:#414558"></span>
<span class="swatch" title="28: #6d7078" style="background:#6d7078"></span>
<span class="swatch" title="29: #898b8c" style="background:#898b8c"></span>
<span class="swatch" title="30: #bbbdbf" style="background:#bbbdbf"></span>
<span class="swatch" title="31: #ffffff" style="background:#ffffff"></span>
</div>

## Linear Color Palette Basic

`use_palette("linear_color_palette_basic")` — 31 colors

<div class="palette">
<span class="swatch" title="0: #0e0c0c" style="background:#0e0c0c"></span>
<span class="swatch" title="1: #5f2d56" style="background:#5f2d56"></span>
<span class="swatch" title="2: #993970" style="background:#993970"></span>
<span class="swatch" title="3: #dc4a7b" style="background:#dc4a7b"></span>
<span class="swatch" title="4: #f78697" style="background:#f78697"></span>
<span class="swatch" title="5: #9f294e" style="background:#9f294e"></span>
<span class="swatch" title="6: #62232f" style="background:#62232f"></span>
<span class="swatch" title="7: #8f4029" style="background:#8f4029"></span>
<span class="swatch" title="8: #c56025" style="background:#c56025"></span>
<span class="swatch" title="9: #ee8e2e" style="background:#ee8e2e"></span>
<span class="swatch" title="10: #fccba3" style="background:#fccba3"></span>
<span class="swatch" title="11: #da4e38" style="background:#da4e38"></span>
<span class="swatch" title="12: #facb3e" style="background:#facb3e"></span>
<span class="swatch" title="13: #97da3f" style="background:#97da3f"></span>
<span class="swatch" title="14: #4ba747" style="background:#4ba747"></span>
<span class="swatch" title="15: #3d734f" style="background:#3d734f"></span>
<span class="swatch" title="16: #314152" style="background:#314152"></span>
<span class="swatch" title="17: #417089" style="background:#417089"></span>
<span class="swatch" title="18: #49a790" style="background:#49a790"></span>
<span class="swatch" title="19: #72d6ce" style="background:#72d6ce"></span>
<span class="swatch" title="20: #5698cc" style="background:#5698cc"></span>
<span class="swatch" title="21: #5956bd" style="background:#5956bd"></span>
<span class="swatch" title="22: #473579" style="background:#473579"></span>
<span class="swatch" title="23: #8156aa" style="background:#8156aa"></span>
<span class="swatch" title="24: #c278d0" style="background:#c278d0"></span>
<span class="swatch" title="25: #f0b3dd" style="background:#f0b3dd"></span>
<span class="swatch" title="26: #fdf7ed" style="background:#fdf7ed"></span>
<span class="swatch" title="27: #d3bfa9" style="background:#d3bfa9"></span>
<span class="swatch" title="28: #aa8d7a" style="background:#aa8d7a"></span>
<span class="swatch" title="29: #775c55" style="background:#775c55"></span>
<span class="swatch" title="30: #483b3a" style="background:#483b3a"></span>
</div>

## Lospec500

`use_palette("lospec500")` — 42 colors

<div class="palette">
<span class="swatch" title="0: #10121c" style="background:#10121c"></span>
<span class="swatch" title="1: #2c1e31" style="background:#2c1e31"></span>
<span class="swatch" title="2: #6b2643" style="background:#6b2643"></span>
<span class="swatch" title="3: #ac2847" style="background:#ac2847"></span>
<span class="swatch" title="4: #ec273f" style="background:#ec273f"></span>
<span class="swatch" title="5: #94493a" style="background:#94493a"></span>
<span class="swatch" title="6: #de5d3a" style="background:#de5d3a"></span>
<span class="swatch" title="7: #e98537" style="background:#e98537"></span>
<span class="swatch" title="8: #f3a833" style="background:#f3a833"></span>
<span class="swatch" title="9: #4d3533" style="background:#4d3533"></span>
<span class="swatch" title="10: #6e4c30" style="background:#6e4c30"></span>
<span class="swatch" title="11: #a26d3f" style="background:#a26d3f"></span>
<span class="swatch" title="12: #ce9248" style="background:#ce9248"></span>
<span class="swatch" title="13: #dab163" style="background:#dab163"></span>
<span class="swatch" title="14: #e8d282" style="background:#e8d282"></span>
<span class="swatch" title="15: #f7f3b7" style="background:#f7f3b7"></span>
<span class="swatch" title="16: #1e4044" style="background:#1e4044"></span>
<span class="swatch" title="17: #006554" style="background:#006554"></span>
<span class="swatch" title="18: #26854c" style="background:#26854c"></span>
<span class="swatch" title="19: #5ab552" style="background:#5ab552"></span>
<span class="swatch" title="20: #9de64e" style="background:#9de64e"></span>
<span class="swatch" title="21: #008b8b" style="background:#008b8b"></span>
<span class="swatch" title="22: #62a477" style="background:#62a477"></span>
<span class="swatch" title="23: #a6cb96" style="background:#a6cb96"></span>
<span class="swatch" title="24: #d3eed3" style="background:#d3eed3"></span>
<span class="swatch" title="25: #3e3b65" style="background:#3e3b65"></span>
<span class="swatch" title="26: #3859b3" style="background:#3859b3"></span>
<span class="swatch" title="27: #3388de" style="background:#3388de"></span>
<span class="swatch" title="28: #36c5f4" style="background:#36c5f4"></span>
<span class="swatch" title="29: #6dead6" style="background:#6dead6"></span>
<span class="swatch" title="30: #5e5b8c" style="background:#5e5b8c"></span>
<span class="swatch" title="31: #8c78a5" style="background:#8c78a5"></span>
<span class="swatch" title="32: #b0a7b8" style="background:#b0a7b8"></span>
<span class="swatch" title="33: #deceed" style="background:#deceed"></span>
<span class="swatch" title="34: #9a4d76" style="background:#9a4d76"></span>
<span class="swatch" title="35: #c878af" style="background:#c878af"></span>
<span class="swatch" title="36: #cc99ff" style="background:#cc99ff"></span>
<span class="swatch" title="37: #fa6e79" style="background:#fa6e79"></span>
<span class="swatch" title="38: #ffa2ac" style="background:#ffa2ac"></span>
<span class="swatch" title="39: #ffd1d5" style="background:#ffd1d5"></span>
<span class="swatch" title="40: #f6e8e0" style="background:#f6e8e0"></span>
<span class="swatch" title="41: #ffffff" style="background:#ffffff"></span>
</div>

## Lost Century

`use_palette("lost_century")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #d1b187" style="background:#d1b187"></span>
<span class="swatch" title="1: #c77b58" style="background:#c77b58"></span>
<span class="swatch" title="2: #ae5d40" style="background:#ae5d40"></span>
<span class="swatch" title="3: #79444a" style="background:#79444a"></span>
<span class="swatch" title="4: #4b3d44" style="background:#4b3d44"></span>
<span class="swatch" title="5: #ba9158" style="background:#ba9158"></span>
<span class="swatch" title="6: #927441" style="background:#927441"></span>
<span class="swatch" title="7: #4d4539" style="background:#4d4539"></span>
<span class="swatch" title="8: #77743b" style="background:#77743b"></span>
<span class="swatch" title="9: #b3a555" style="background:#b3a555"></span>
<span class="swatch" title="10: #d2c9a5" style="background:#d2c9a5"></span>
<span class="swatch" title="11: #8caba1" style="background:#8caba1"></span>
<span class="swatch" title="12: #4b726e" style="background:#4b726e"></span>
<span class="swatch" title="13: #574852" style="background:#574852"></span>
<span class="swatch" title="14: #847875" style="background:#847875"></span>
<span class="swatch" title="15: #ab9b8e" style="background:#ab9b8e"></span>
</div>

## Lux2K

`use_palette("lux2k")` — 36 colors

<div class="palette">
<span class="swatch" title="0: #25131a" style="background:#25131a"></span>
<span class="swatch" title="1: #3d253b" style="background:#3d253b"></span>
<span class="swatch" title="2: #523b40" style="background:#523b40"></span>
<span class="swatch" title="3: #1f3736" style="background:#1f3736"></span>
<span class="swatch" title="4: #2a5a39" style="background:#2a5a39"></span>
<span class="swatch" title="5: #427f3b" style="background:#427f3b"></span>
<span class="swatch" title="6: #80a53f" style="background:#80a53f"></span>
<span class="swatch" title="7: #bbc44e" style="background:#bbc44e"></span>
<span class="swatch" title="8: #96c641" style="background:#96c641"></span>
<span class="swatch" title="9: #ccf61f" style="background:#ccf61f"></span>
<span class="swatch" title="10: #8a961f" style="background:#8a961f"></span>
<span class="swatch" title="11: #5c6b53" style="background:#5c6b53"></span>
<span class="swatch" title="12: #895a45" style="background:#895a45"></span>
<span class="swatch" title="13: #d1851e" style="background:#d1851e"></span>
<span class="swatch" title="14: #ffd569" style="background:#ffd569"></span>
<span class="swatch" title="15: #bf704d" style="background:#bf704d"></span>
<span class="swatch" title="16: #e1a171" style="background:#e1a171"></span>
<span class="swatch" title="17: #e6deca" style="background:#e6deca"></span>
<span class="swatch" title="18: #9b4c51" style="background:#9b4c51"></span>
<span class="swatch" title="19: #802954" style="background:#802954"></span>
<span class="swatch" title="20: #d01946" style="background:#d01946"></span>
<span class="swatch" title="21: #e84444" style="background:#e84444"></span>
<span class="swatch" title="22: #40369f" style="background:#40369f"></span>
<span class="swatch" title="23: #7144ff" style="background:#7144ff"></span>
<span class="swatch" title="24: #af69bf" style="background:#af69bf"></span>
<span class="swatch" title="25: #eaa5ff" style="background:#eaa5ff"></span>
<span class="swatch" title="26: #5880cc" style="background:#5880cc"></span>
<span class="swatch" title="27: #62abd4" style="background:#62abd4"></span>
<span class="swatch" title="28: #9bf0fd" style="background:#9bf0fd"></span>
<span class="swatch" title="29: #cae6f5" style="background:#cae6f5"></span>
<span class="swatch" title="30: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="31: #a7acba" style="background:#a7acba"></span>
<span class="swatch" title="32: #606060" style="background:#606060"></span>
<span class="swatch" title="33: #56587b" style="background:#56587b"></span>
<span class="swatch" title="34: #9a8571" style="background:#9a8571"></span>
<span class="swatch" title="35: #dfbbb3" style="background:#dfbbb3"></span>
</div>

## Lux3K

`use_palette("lux3k")` — 38 colors

<div class="palette">
<span class="swatch" title="0: #ce3b26" style="background:#ce3b26"></span>
<span class="swatch" title="1: #f7872a" style="background:#f7872a"></span>
<span class="swatch" title="2: #fcd56b" style="background:#fcd56b"></span>
<span class="swatch" title="3: #e7952e" style="background:#e7952e"></span>
<span class="swatch" title="4: #f9b857" style="background:#f9b857"></span>
<span class="swatch" title="5: #f0c209" style="background:#f0c209"></span>
<span class="swatch" title="6: #b16e45" style="background:#b16e45"></span>
<span class="swatch" title="7: #f4b27a" style="background:#f4b27a"></span>
<span class="swatch" title="8: #f0d89d" style="background:#f0d89d"></span>
<span class="swatch" title="9: #f9f5d2" style="background:#f9f5d2"></span>
<span class="swatch" title="10: #8f4349" style="background:#8f4349"></span>
<span class="swatch" title="11: #ffa686" style="background:#ffa686"></span>
<span class="swatch" title="12: #fdceab" style="background:#fdceab"></span>
<span class="swatch" title="13: #5cac48" style="background:#5cac48"></span>
<span class="swatch" title="14: #8cce6c" style="background:#8cce6c"></span>
<span class="swatch" title="15: #c1ec48" style="background:#c1ec48"></span>
<span class="swatch" title="16: #060329" style="background:#060329"></span>
<span class="swatch" title="17: #1c2833" style="background:#1c2833"></span>
<span class="swatch" title="18: #145041" style="background:#145041"></span>
<span class="swatch" title="19: #231618" style="background:#231618"></span>
<span class="swatch" title="20: #521e23" style="background:#521e23"></span>
<span class="swatch" title="21: #832121" style="background:#832121"></span>
<span class="swatch" title="22: #ff804a" style="background:#ff804a"></span>
<span class="swatch" title="23: #e16169" style="background:#e16169"></span>
<span class="swatch" title="24: #ee8095" style="background:#ee8095"></span>
<span class="swatch" title="25: #7b3781" style="background:#7b3781"></span>
<span class="swatch" title="26: #b64d75" style="background:#b64d75"></span>
<span class="swatch" title="27: #a07385" style="background:#a07385"></span>
<span class="swatch" title="28: #44050b" style="background:#44050b"></span>
<span class="swatch" title="29: #6d2a41" style="background:#6d2a41"></span>
<span class="swatch" title="30: #962c52" style="background:#962c52"></span>
<span class="swatch" title="31: #e53366" style="background:#e53366"></span>
<span class="swatch" title="32: #6e5657" style="background:#6e5657"></span>
<span class="swatch" title="33: #a7acba" style="background:#a7acba"></span>
<span class="swatch" title="34: #accdec" style="background:#accdec"></span>
<span class="swatch" title="35: #1c5c83" style="background:#1c5c83"></span>
<span class="swatch" title="36: #2ba8b5" style="background:#2ba8b5"></span>
<span class="swatch" title="37: #46dccd" style="background:#46dccd"></span>
</div>

## Midnight Ablaze

`use_palette("midnight_ablaze")` — 7 colors

<div class="palette">
<span class="swatch" title="0: #ff8274" style="background:#ff8274"></span>
<span class="swatch" title="1: #d53c6a" style="background:#d53c6a"></span>
<span class="swatch" title="2: #7c183c" style="background:#7c183c"></span>
<span class="swatch" title="3: #460e2b" style="background:#460e2b"></span>
<span class="swatch" title="4: #31051e" style="background:#31051e"></span>
<span class="swatch" title="5: #1f0510" style="background:#1f0510"></span>
<span class="swatch" title="6: #130208" style="background:#130208"></span>
</div>

## Mojave20

`use_palette("mojave20")` — 20 colors

<div class="palette">
<span class="swatch" title="0: #dcd1b8" style="background:#dcd1b8"></span>
<span class="swatch" title="1: #c8b496" style="background:#c8b496"></span>
<span class="swatch" title="2: #aeb0b2" style="background:#aeb0b2"></span>
<span class="swatch" title="3: #9196a0" style="background:#9196a0"></span>
<span class="swatch" title="4: #60606a" style="background:#60606a"></span>
<span class="swatch" title="5: #403f4a" style="background:#403f4a"></span>
<span class="swatch" title="6: #38353e" style="background:#38353e"></span>
<span class="swatch" title="7: #4b444c" style="background:#4b444c"></span>
<span class="swatch" title="8: #79625d" style="background:#79625d"></span>
<span class="swatch" title="9: #9e8676" style="background:#9e8676"></span>
<span class="swatch" title="10: #be9668" style="background:#be9668"></span>
<span class="swatch" title="11: #a46848" style="background:#a46848"></span>
<span class="swatch" title="12: #715a3b" style="background:#715a3b"></span>
<span class="swatch" title="13: #453e2a" style="background:#453e2a"></span>
<span class="swatch" title="14: #3f2926" style="background:#3f2926"></span>
<span class="swatch" title="15: #2e1515" style="background:#2e1515"></span>
<span class="swatch" title="16: #17090c" style="background:#17090c"></span>
<span class="swatch" title="17: #541e13" style="background:#541e13"></span>
<span class="swatch" title="18: #d03c32" style="background:#d03c32"></span>
<span class="swatch" title="19: #fba64c" style="background:#fba64c"></span>
</div>

## Mort Vs Zughy

`use_palette("mort_vs_zughy")` — 47 colors

<div class="palette">
<span class="swatch" title="0: #f8f8f8" style="background:#f8f8f8"></span>
<span class="swatch" title="1: #bcb7c5" style="background:#bcb7c5"></span>
<span class="swatch" title="2: #8d87a2" style="background:#8d87a2"></span>
<span class="swatch" title="3: #50576b" style="background:#50576b"></span>
<span class="swatch" title="4: #2e3740" style="background:#2e3740"></span>
<span class="swatch" title="5: #101e29" style="background:#101e29"></span>
<span class="swatch" title="6: #302c2e" style="background:#302c2e"></span>
<span class="swatch" title="7: #5a5353" style="background:#5a5353"></span>
<span class="swatch" title="8: #7d7071" style="background:#7d7071"></span>
<span class="swatch" title="9: #a0938e" style="background:#a0938e"></span>
<span class="swatch" title="10: #cfc6b8" style="background:#cfc6b8"></span>
<span class="swatch" title="11: #f4cca1" style="background:#f4cca1"></span>
<span class="swatch" title="12: #eea160" style="background:#eea160"></span>
<span class="swatch" title="13: #bf7958" style="background:#bf7958"></span>
<span class="swatch" title="14: #a05b53" style="background:#a05b53"></span>
<span class="swatch" title="15: #7a444a" style="background:#7a444a"></span>
<span class="swatch" title="16: #5e3643" style="background:#5e3643"></span>
<span class="swatch" title="17: #472d3c" style="background:#472d3c"></span>
<span class="swatch" title="18: #39314b" style="background:#39314b"></span>
<span class="swatch" title="19: #64468d" style="background:#64468d"></span>
<span class="swatch" title="20: #8e478c" style="background:#8e478c"></span>
<span class="swatch" title="21: #ae57a4" style="background:#ae57a4"></span>
<span class="swatch" title="22: #ea71bd" style="background:#ea71bd"></span>
<span class="swatch" title="23: #ffaeb6" style="background:#ffaeb6"></span>
<span class="swatch" title="24: #ff8b9c" style="background:#ff8b9c"></span>
<span class="swatch" title="25: #e1534a" style="background:#e1534a"></span>
<span class="swatch" title="26: #a93b3b" style="background:#a93b3b"></span>
<span class="swatch" title="27: #f47e1b" style="background:#f47e1b"></span>
<span class="swatch" title="28: #f4b41b" style="background:#f4b41b"></span>
<span class="swatch" title="29: #ffce00" style="background:#ffce00"></span>
<span class="swatch" title="30: #fbfcaa" style="background:#fbfcaa"></span>
<span class="swatch" title="31: #b6d53c" style="background:#b6d53c"></span>
<span class="swatch" title="32: #71aa34" style="background:#71aa34"></span>
<span class="swatch" title="33: #3f7e00" style="background:#3f7e00"></span>
<span class="swatch" title="34: #005f1b" style="background:#005f1b"></span>
<span class="swatch" title="35: #00635c" style="background:#00635c"></span>
<span class="swatch" title="36: #00a383" style="background:#00a383"></span>
<span class="swatch" title="37: #3fc778" style="background:#3fc778"></span>
<span class="swatch" title="38: #a1ef79" style="background:#a1ef79"></span>
<span class="swatch" title="39: #dff6f5" style="background:#dff6f5"></span>
<span class="swatch" title="40: #92f4ff" style="background:#92f4ff"></span>
<span class="swatch" title="41: #42cafd" style="background:#42cafd"></span>
<span class="swatch" title="42: #3978a8" style="background:#3978a8"></span>
<span class="swatch" title="43: #243f72" style="background:#243f72"></span>
<span class="swatch" title="44: #564064" style="background:#564064"></span>
<span class="swatch" title="45: #827094" style="background:#827094"></span>
<span class="swatch" title="46: #4f546b" style="background:#4f546b"></span>
</div>

## Mulfok32

`use_palette("mulfok32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #5ba675" style="background:#5ba675"></span>
<span class="swatch" title="1: #6bc96c" style="background:#6bc96c"></span>
<span class="swatch" title="2: #abdd64" style="background:#abdd64"></span>
<span class="swatch" title="3: #fcef8d" style="background:#fcef8d"></span>
<span class="swatch" title="4: #ffb879" style="background:#ffb879"></span>
<span class="swatch" title="5: #ea6262" style="background:#ea6262"></span>
<span class="swatch" title="6: #cc425e" style="background:#cc425e"></span>
<span class="swatch" title="7: #a32858" style="background:#a32858"></span>
<span class="swatch" title="8: #751756" style="background:#751756"></span>
<span class="swatch" title="9: #390947" style="background:#390947"></span>
<span class="swatch" title="10: #611851" style="background:#611851"></span>
<span class="swatch" title="11: #873555" style="background:#873555"></span>
<span class="swatch" title="12: #a6555f" style="background:#a6555f"></span>
<span class="swatch" title="13: #c97373" style="background:#c97373"></span>
<span class="swatch" title="14: #f2ae99" style="background:#f2ae99"></span>
<span class="swatch" title="15: #ffc3f2" style="background:#ffc3f2"></span>
<span class="swatch" title="16: #ee8fcb" style="background:#ee8fcb"></span>
<span class="swatch" title="17: #d46eb3" style="background:#d46eb3"></span>
<span class="swatch" title="18: #873e84" style="background:#873e84"></span>
<span class="swatch" title="19: #1f102a" style="background:#1f102a"></span>
<span class="swatch" title="20: #4a3052" style="background:#4a3052"></span>
<span class="swatch" title="21: #7b5480" style="background:#7b5480"></span>
<span class="swatch" title="22: #a6859f" style="background:#a6859f"></span>
<span class="swatch" title="23: #d9bdc8" style="background:#d9bdc8"></span>
<span class="swatch" title="24: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="25: #aee2ff" style="background:#aee2ff"></span>
<span class="swatch" title="26: #8db7ff" style="background:#8db7ff"></span>
<span class="swatch" title="27: #6d80fa" style="background:#6d80fa"></span>
<span class="swatch" title="28: #8465ec" style="background:#8465ec"></span>
<span class="swatch" title="29: #834dc4" style="background:#834dc4"></span>
<span class="swatch" title="30: #7d2da0" style="background:#7d2da0"></span>
<span class="swatch" title="31: #4e187c" style="background:#4e187c"></span>
</div>

## Na16

`use_palette("na16")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #8c8fae" style="background:#8c8fae"></span>
<span class="swatch" title="1: #584563" style="background:#584563"></span>
<span class="swatch" title="2: #3e2137" style="background:#3e2137"></span>
<span class="swatch" title="3: #9a6348" style="background:#9a6348"></span>
<span class="swatch" title="4: #d79b7d" style="background:#d79b7d"></span>
<span class="swatch" title="5: #f5edba" style="background:#f5edba"></span>
<span class="swatch" title="6: #c0c741" style="background:#c0c741"></span>
<span class="swatch" title="7: #647d34" style="background:#647d34"></span>
<span class="swatch" title="8: #e4943a" style="background:#e4943a"></span>
<span class="swatch" title="9: #9d303b" style="background:#9d303b"></span>
<span class="swatch" title="10: #d26471" style="background:#d26471"></span>
<span class="swatch" title="11: #70377f" style="background:#70377f"></span>
<span class="swatch" title="12: #7ec4c1" style="background:#7ec4c1"></span>
<span class="swatch" title="13: #34859d" style="background:#34859d"></span>
<span class="swatch" title="14: #17434b" style="background:#17434b"></span>
<span class="swatch" title="15: #1f0e1c" style="background:#1f0e1c"></span>
</div>

## Nanner 16

`use_palette("nanner_16")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #7acccc" style="background:#7acccc"></span>
<span class="swatch" title="1: #627db3" style="background:#627db3"></span>
<span class="swatch" title="2: #554080" style="background:#554080"></span>
<span class="swatch" title="3: #592858" style="background:#592858"></span>
<span class="swatch" title="4: #804055" style="background:#804055"></span>
<span class="swatch" title="5: #b37d62" style="background:#b37d62"></span>
<span class="swatch" title="6: #ccc97a" style="background:#ccc97a"></span>
<span class="swatch" title="7: #70b362" style="background:#70b362"></span>
<span class="swatch" title="8: #40806a" style="background:#40806a"></span>
<span class="swatch" title="9: #274457" style="background:#274457"></span>
<span class="swatch" title="10: #cccccc" style="background:#cccccc"></span>
<span class="swatch" title="11: #999491" style="background:#999491"></span>
<span class="swatch" title="12: #665c5f" style="background:#665c5f"></span>
<span class="swatch" title="13: #332b33" style="background:#332b33"></span>
<span class="swatch" title="14: #804e46" style="background:#804e46"></span>
<span class="swatch" title="15: #4d2a2a" style="background:#4d2a2a"></span>
</div>

## Nanner Pancakes

`use_palette("nanner_pancakes")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #a0ddd3" style="background:#a0ddd3"></span>
<span class="swatch" title="1: #6fb0b7" style="background:#6fb0b7"></span>
<span class="swatch" title="2: #577f9d" style="background:#577f9d"></span>
<span class="swatch" title="3: #4a5786" style="background:#4a5786"></span>
<span class="swatch" title="4: #3e3b66" style="background:#3e3b66"></span>
<span class="swatch" title="5: #392945" style="background:#392945"></span>
<span class="swatch" title="6: #2d1e2f" style="background:#2d1e2f"></span>
<span class="swatch" title="7: #452e3f" style="background:#452e3f"></span>
<span class="swatch" title="8: #5d4550" style="background:#5d4550"></span>
<span class="swatch" title="9: #7b6268" style="background:#7b6268"></span>
<span class="swatch" title="10: #9c807e" style="background:#9c807e"></span>
<span class="swatch" title="11: #c3a79c" style="background:#c3a79c"></span>
<span class="swatch" title="12: #dbc9b4" style="background:#dbc9b4"></span>
<span class="swatch" title="13: #fcecd1" style="background:#fcecd1"></span>
<span class="swatch" title="14: #aad795" style="background:#aad795"></span>
<span class="swatch" title="15: #64b082" style="background:#64b082"></span>
<span class="swatch" title="16: #488885" style="background:#488885"></span>
<span class="swatch" title="17: #3f5b74" style="background:#3f5b74"></span>
<span class="swatch" title="18: #ebc8a7" style="background:#ebc8a7"></span>
<span class="swatch" title="19: #d3a084" style="background:#d3a084"></span>
<span class="swatch" title="20: #b87e6c" style="background:#b87e6c"></span>
<span class="swatch" title="21: #8f5252" style="background:#8f5252"></span>
<span class="swatch" title="22: #6a3948" style="background:#6a3948"></span>
<span class="swatch" title="23: #c57f79" style="background:#c57f79"></span>
<span class="swatch" title="24: #ab597d" style="background:#ab597d"></span>
<span class="swatch" title="25: #7c3d64" style="background:#7c3d64"></span>
<span class="swatch" title="26: #4e2b45" style="background:#4e2b45"></span>
<span class="swatch" title="27: #7a3b4f" style="background:#7a3b4f"></span>
<span class="swatch" title="28: #a94b54" style="background:#a94b54"></span>
<span class="swatch" title="29: #d8725e" style="background:#d8725e"></span>
<span class="swatch" title="30: #f09f71" style="background:#f09f71"></span>
<span class="swatch" title="31: #f7cf91" style="background:#f7cf91"></span>
</div>

## Nes Advanced

`use_palette("nes_advanced")` — 55 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #26232f" style="background:#26232f"></span>
<span class="swatch" title="2: #314047" style="background:#314047"></span>
<span class="swatch" title="3: #596d62" style="background:#596d62"></span>
<span class="swatch" title="4: #929c74" style="background:#929c74"></span>
<span class="swatch" title="5: #c8c5a3" style="background:#c8c5a3"></span>
<span class="swatch" title="6: #fcfcfc" style="background:#fcfcfc"></span>
<span class="swatch" title="7: #1b377f" style="background:#1b377f"></span>
<span class="swatch" title="8: #147abf" style="background:#147abf"></span>
<span class="swatch" title="9: #40afdd" style="background:#40afdd"></span>
<span class="swatch" title="10: #b2dbf4" style="background:#b2dbf4"></span>
<span class="swatch" title="11: #181667" style="background:#181667"></span>
<span class="swatch" title="12: #3b2c96" style="background:#3b2c96"></span>
<span class="swatch" title="13: #706ae1" style="background:#706ae1"></span>
<span class="swatch" title="14: #8f95ee" style="background:#8f95ee"></span>
<span class="swatch" title="15: #440a41" style="background:#440a41"></span>
<span class="swatch" title="16: #812593" style="background:#812593"></span>
<span class="swatch" title="17: #cc4bb9" style="background:#cc4bb9"></span>
<span class="swatch" title="18: #ec99db" style="background:#ec99db"></span>
<span class="swatch" title="19: #3f0011" style="background:#3f0011"></span>
<span class="swatch" title="20: #b31c35" style="background:#b31c35"></span>
<span class="swatch" title="21: #ef2064" style="background:#ef2064"></span>
<span class="swatch" title="22: #f26282" style="background:#f26282"></span>
<span class="swatch" title="23: #960811" style="background:#960811"></span>
<span class="swatch" title="24: #e81813" style="background:#e81813"></span>
<span class="swatch" title="25: #a75d69" style="background:#a75d69"></span>
<span class="swatch" title="26: #ec9ea4" style="background:#ec9ea4"></span>
<span class="swatch" title="27: #560d04" style="background:#560d04"></span>
<span class="swatch" title="28: #c43611" style="background:#c43611"></span>
<span class="swatch" title="29: #e26a12" style="background:#e26a12"></span>
<span class="swatch" title="30: #f0af66" style="background:#f0af66"></span>
<span class="swatch" title="31: #2a1a14" style="background:#2a1a14"></span>
<span class="swatch" title="32: #5d342a" style="background:#5d342a"></span>
<span class="swatch" title="33: #a66e46" style="background:#a66e46"></span>
<span class="swatch" title="34: #df9c6e" style="background:#df9c6e"></span>
<span class="swatch" title="35: #8e4e11" style="background:#8e4e11"></span>
<span class="swatch" title="36: #d89511" style="background:#d89511"></span>
<span class="swatch" title="37: #ead11e" style="background:#ead11e"></span>
<span class="swatch" title="38: #f5eb6b" style="background:#f5eb6b"></span>
<span class="swatch" title="39: #2f541c" style="background:#2f541c"></span>
<span class="swatch" title="40: #5a831b" style="background:#5a831b"></span>
<span class="swatch" title="41: #a2bb1e" style="background:#a2bb1e"></span>
<span class="swatch" title="42: #c6df6b" style="background:#c6df6b"></span>
<span class="swatch" title="43: #0f450f" style="background:#0f450f"></span>
<span class="swatch" title="44: #008b12" style="background:#008b12"></span>
<span class="swatch" title="45: #0bcb12" style="background:#0bcb12"></span>
<span class="swatch" title="46: #3ef33f" style="background:#3ef33f"></span>
<span class="swatch" title="47: #115153" style="background:#115153"></span>
<span class="swatch" title="48: #0c8563" style="background:#0c8563"></span>
<span class="swatch" title="49: #04bf79" style="background:#04bf79"></span>
<span class="swatch" title="50: #6ae6aa" style="background:#6ae6aa"></span>
<span class="swatch" title="51: #262726" style="background:#262726"></span>
<span class="swatch" title="52: #514f4c" style="background:#514f4c"></span>
<span class="swatch" title="53: #887e83" style="background:#887e83"></span>
<span class="swatch" title="54: #b3aac0" style="background:#b3aac0"></span>
</div>

## Nirvana 7

`use_palette("nirvana_7")` — 7 colors

<div class="palette">
<span class="swatch" title="0: #1e0b37" style="background:#1e0b37"></span>
<span class="swatch" title="1: #45176e" style="background:#45176e"></span>
<span class="swatch" title="2: #8e20a7" style="background:#8e20a7"></span>
<span class="swatch" title="3: #d53be3" style="background:#d53be3"></span>
<span class="swatch" title="4: #ef7bdd" style="background:#ef7bdd"></span>
<span class="swatch" title="5: #f6b7d6" style="background:#f6b7d6"></span>
<span class="swatch" title="6: #fcf2de" style="background:#fcf2de"></span>
</div>

## Nyx8

`use_palette("nyx8")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #08141e" style="background:#08141e"></span>
<span class="swatch" title="1: #0f2a3f" style="background:#0f2a3f"></span>
<span class="swatch" title="2: #20394f" style="background:#20394f"></span>
<span class="swatch" title="3: #f6d6bd" style="background:#f6d6bd"></span>
<span class="swatch" title="4: #c3a38a" style="background:#c3a38a"></span>
<span class="swatch" title="5: #997577" style="background:#997577"></span>
<span class="swatch" title="6: #816271" style="background:#816271"></span>
<span class="swatch" title="7: #4e495f" style="background:#4e495f"></span>
</div>

## Oil 6

`use_palette("oil_6")` — 6 colors

<div class="palette">
<span class="swatch" title="0: #fbf5ef" style="background:#fbf5ef"></span>
<span class="swatch" title="1: #f2d3ab" style="background:#f2d3ab"></span>
<span class="swatch" title="2: #c69fa5" style="background:#c69fa5"></span>
<span class="swatch" title="3: #8b6d9c" style="background:#8b6d9c"></span>
<span class="swatch" title="4: #494d7e" style="background:#494d7e"></span>
<span class="swatch" title="5: #272744" style="background:#272744"></span>
</div>

## Paper 8

`use_palette("paper_8")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #1f244b" style="background:#1f244b"></span>
<span class="swatch" title="1: #654053" style="background:#654053"></span>
<span class="swatch" title="2: #a8605d" style="background:#a8605d"></span>
<span class="swatch" title="3: #d1a67e" style="background:#d1a67e"></span>
<span class="swatch" title="4: #f6e79c" style="background:#f6e79c"></span>
<span class="swatch" title="5: #b6cf8e" style="background:#b6cf8e"></span>
<span class="swatch" title="6: #60ae7b" style="background:#60ae7b"></span>
<span class="swatch" title="7: #3c6b64" style="background:#3c6b64"></span>
</div>

## Paradise 30

`use_palette("paradise_30")` — 30 colors

<div class="palette">
<span class="swatch" title="0: #1a0e14" style="background:#1a0e14"></span>
<span class="swatch" title="1: #321921" style="background:#321921"></span>
<span class="swatch" title="2: #4d292d" style="background:#4d292d"></span>
<span class="swatch" title="3: #70483c" style="background:#70483c"></span>
<span class="swatch" title="4: #96705a" style="background:#96705a"></span>
<span class="swatch" title="5: #b59571" style="background:#b59571"></span>
<span class="swatch" title="6: #e0c892" style="background:#e0c892"></span>
<span class="swatch" title="7: #fff4b0" style="background:#fff4b0"></span>
<span class="swatch" title="8: #4c2126" style="background:#4c2126"></span>
<span class="swatch" title="9: #70282b" style="background:#70282b"></span>
<span class="swatch" title="10: #993833" style="background:#993833"></span>
<span class="swatch" title="11: #bd4c35" style="background:#bd4c35"></span>
<span class="swatch" title="12: #d9643d" style="background:#d9643d"></span>
<span class="swatch" title="13: #f0824b" style="background:#f0824b"></span>
<span class="swatch" title="14: #fba75d" style="background:#fba75d"></span>
<span class="swatch" title="15: #ffc973" style="background:#ffc973"></span>
<span class="swatch" title="16: #ffe08a" style="background:#ffe08a"></span>
<span class="swatch" title="17: #bf2b29" style="background:#bf2b29"></span>
<span class="swatch" title="18: #e64e47" style="background:#e64e47"></span>
<span class="swatch" title="19: #ed572d" style="background:#ed572d"></span>
<span class="swatch" title="20: #ff9130" style="background:#ff9130"></span>
<span class="swatch" title="21: #ffbd40" style="background:#ffbd40"></span>
<span class="swatch" title="22: #364121" style="background:#364121"></span>
<span class="swatch" title="23: #5a7a22" style="background:#5a7a22"></span>
<span class="swatch" title="24: #b3a720" style="background:#b3a720"></span>
<span class="swatch" title="25: #402b50" style="background:#402b50"></span>
<span class="swatch" title="26: #4e59c2" style="background:#4e59c2"></span>
<span class="swatch" title="27: #48ace0" style="background:#48ace0"></span>
<span class="swatch" title="28: #863ba1" style="background:#863ba1"></span>
<span class="swatch" title="29: #d663d7" style="background:#d663d7"></span>
</div>

## Pastel Qt

`use_palette("pastel_qt")` — 7 colors

<div class="palette">
<span class="swatch" title="0: #cb8175" style="background:#cb8175"></span>
<span class="swatch" title="1: #e2a97e" style="background:#e2a97e"></span>
<span class="swatch" title="2: #f0cf8e" style="background:#f0cf8e"></span>
<span class="swatch" title="3: #f6edcd" style="background:#f6edcd"></span>
<span class="swatch" title="4: #a8c8a6" style="background:#a8c8a6"></span>
<span class="swatch" title="5: #6d8d8a" style="background:#6d8d8a"></span>
<span class="swatch" title="6: #655057" style="background:#655057"></span>
</div>

## Pax 24

`use_palette("pax_24")` — 24 colors

<div class="palette">
<span class="swatch" title="0: #f4f5ef" style="background:#f4f5ef"></span>
<span class="swatch" title="1: #f8c7a4" style="background:#f8c7a4"></span>
<span class="swatch" title="2: #e784a8" style="background:#e784a8"></span>
<span class="swatch" title="3: #eb9d45" style="background:#eb9d45"></span>
<span class="swatch" title="4: #bb9a3e" style="background:#bb9a3e"></span>
<span class="swatch" title="5: #f6e455" style="background:#f6e455"></span>
<span class="swatch" title="6: #c8dbdf" style="background:#c8dbdf"></span>
<span class="swatch" title="7: #a146aa" style="background:#a146aa"></span>
<span class="swatch" title="8: #d74d4c" style="background:#d74d4c"></span>
<span class="swatch" title="9: #a65d35" style="background:#a65d35"></span>
<span class="swatch" title="10: #8fcb62" style="background:#8fcb62"></span>
<span class="swatch" title="11: #35884e" style="background:#35884e"></span>
<span class="swatch" title="12: #a0abb1" style="background:#a0abb1"></span>
<span class="swatch" title="13: #962f2c" style="background:#962f2c"></span>
<span class="swatch" title="14: #682d2c" style="background:#682d2c"></span>
<span class="swatch" title="15: #85dfeb" style="background:#85dfeb"></span>
<span class="swatch" title="16: #339ca3" style="background:#339ca3"></span>
<span class="swatch" title="17: #1b4c5a" style="background:#1b4c5a"></span>
<span class="swatch" title="18: #5e6a82" style="background:#5e6a82"></span>
<span class="swatch" title="19: #191023" style="background:#191023"></span>
<span class="swatch" title="20: #72adee" style="background:#72adee"></span>
<span class="swatch" title="21: #435edb" style="background:#435edb"></span>
<span class="swatch" title="22: #474394" style="background:#474394"></span>
<span class="swatch" title="23: #322d4d" style="background:#322d4d"></span>
</div>

## Pear36

`use_palette("pear36")` — 36 colors

<div class="palette">
<span class="swatch" title="0: #5e315b" style="background:#5e315b"></span>
<span class="swatch" title="1: #8c3f5d" style="background:#8c3f5d"></span>
<span class="swatch" title="2: #ba6156" style="background:#ba6156"></span>
<span class="swatch" title="3: #f2a65e" style="background:#f2a65e"></span>
<span class="swatch" title="4: #ffe478" style="background:#ffe478"></span>
<span class="swatch" title="5: #cfff70" style="background:#cfff70"></span>
<span class="swatch" title="6: #8fde5d" style="background:#8fde5d"></span>
<span class="swatch" title="7: #3ca370" style="background:#3ca370"></span>
<span class="swatch" title="8: #3d6e70" style="background:#3d6e70"></span>
<span class="swatch" title="9: #323e4f" style="background:#323e4f"></span>
<span class="swatch" title="10: #322947" style="background:#322947"></span>
<span class="swatch" title="11: #473b78" style="background:#473b78"></span>
<span class="swatch" title="12: #4b5bab" style="background:#4b5bab"></span>
<span class="swatch" title="13: #4da6ff" style="background:#4da6ff"></span>
<span class="swatch" title="14: #66ffe3" style="background:#66ffe3"></span>
<span class="swatch" title="15: #ffffeb" style="background:#ffffeb"></span>
<span class="swatch" title="16: #c2c2d1" style="background:#c2c2d1"></span>
<span class="swatch" title="17: #7e7e8f" style="background:#7e7e8f"></span>
<span class="swatch" title="18: #606070" style="background:#606070"></span>
<span class="swatch" title="19: #43434f" style="background:#43434f"></span>
<span class="swatch" title="20: #272736" style="background:#272736"></span>
<span class="swatch" title="21: #3e2347" style="background:#3e2347"></span>
<span class="swatch" title="22: #57294b" style="background:#57294b"></span>
<span class="swatch" title="23: #964253" style="background:#964253"></span>
<span class="swatch" title="24: #e36956" style="background:#e36956"></span>
<span class="swatch" title="25: #ffb570" style="background:#ffb570"></span>
<span class="swatch" title="26: #ff9166" style="background:#ff9166"></span>
<span class="swatch" title="27: #eb564b" style="background:#eb564b"></span>
<span class="swatch" title="28: #b0305c" style="background:#b0305c"></span>
<span class="swatch" title="29: #73275c" style="background:#73275c"></span>
<span class="swatch" title="30: #422445" style="background:#422445"></span>
<span class="swatch" title="31: #5a265e" style="background:#5a265e"></span>
<span class="swatch" title="32: #80366b" style="background:#80366b"></span>
<span class="swatch" title="33: #bd4882" style="background:#bd4882"></span>
<span class="swatch" title="34: #ff6b97" style="background:#ff6b97"></span>
<span class="swatch" title="35: #ffb5b5" style="background:#ffb5b5"></span>
</div>

## Pico 8

`use_palette("pico_8")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #1d2b53" style="background:#1d2b53"></span>
<span class="swatch" title="2: #7e2553" style="background:#7e2553"></span>
<span class="swatch" title="3: #008751" style="background:#008751"></span>
<span class="swatch" title="4: #ab5236" style="background:#ab5236"></span>
<span class="swatch" title="5: #5f574f" style="background:#5f574f"></span>
<span class="swatch" title="6: #c2c3c7" style="background:#c2c3c7"></span>
<span class="swatch" title="7: #fff1e8" style="background:#fff1e8"></span>
<span class="swatch" title="8: #ff004d" style="background:#ff004d"></span>
<span class="swatch" title="9: #ffa300" style="background:#ffa300"></span>
<span class="swatch" title="10: #ffec27" style="background:#ffec27"></span>
<span class="swatch" title="11: #00e436" style="background:#00e436"></span>
<span class="swatch" title="12: #29adff" style="background:#29adff"></span>
<span class="swatch" title="13: #83769c" style="background:#83769c"></span>
<span class="swatch" title="14: #ff77a8" style="background:#ff77a8"></span>
<span class="swatch" title="15: #ffccaa" style="background:#ffccaa"></span>
</div>

## Pineapple 32

`use_palette("pineapple_32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #43002a" style="background:#43002a"></span>
<span class="swatch" title="1: #890027" style="background:#890027"></span>
<span class="swatch" title="2: #d9243c" style="background:#d9243c"></span>
<span class="swatch" title="3: #ff6157" style="background:#ff6157"></span>
<span class="swatch" title="4: #ffb762" style="background:#ffb762"></span>
<span class="swatch" title="5: #c76e46" style="background:#c76e46"></span>
<span class="swatch" title="6: #73392e" style="background:#73392e"></span>
<span class="swatch" title="7: #34111f" style="background:#34111f"></span>
<span class="swatch" title="8: #030710" style="background:#030710"></span>
<span class="swatch" title="9: #273b2d" style="background:#273b2d"></span>
<span class="swatch" title="10: #458239" style="background:#458239"></span>
<span class="swatch" title="11: #9cb93b" style="background:#9cb93b"></span>
<span class="swatch" title="12: #ffd832" style="background:#ffd832"></span>
<span class="swatch" title="13: #ff823b" style="background:#ff823b"></span>
<span class="swatch" title="14: #d1401f" style="background:#d1401f"></span>
<span class="swatch" title="15: #7c191a" style="background:#7c191a"></span>
<span class="swatch" title="16: #310c1b" style="background:#310c1b"></span>
<span class="swatch" title="17: #833f34" style="background:#833f34"></span>
<span class="swatch" title="18: #eb9c6e" style="background:#eb9c6e"></span>
<span class="swatch" title="19: #ffdaac" style="background:#ffdaac"></span>
<span class="swatch" title="20: #ffffe4" style="background:#ffffe4"></span>
<span class="swatch" title="21: #bfc3c6" style="background:#bfc3c6"></span>
<span class="swatch" title="22: #6d8a8d" style="background:#6d8a8d"></span>
<span class="swatch" title="23: #293b49" style="background:#293b49"></span>
<span class="swatch" title="24: #041528" style="background:#041528"></span>
<span class="swatch" title="25: #033e5e" style="background:#033e5e"></span>
<span class="swatch" title="26: #1c92a7" style="background:#1c92a7"></span>
<span class="swatch" title="27: #77d6c1" style="background:#77d6c1"></span>
<span class="swatch" title="28: #ffe0dc" style="background:#ffe0dc"></span>
<span class="swatch" title="29: #ff88a9" style="background:#ff88a9"></span>
<span class="swatch" title="30: #c03b94" style="background:#c03b94"></span>
<span class="swatch" title="31: #601761" style="background:#601761"></span>
</div>

## Pollen8

`use_palette("pollen8")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #73464c" style="background:#73464c"></span>
<span class="swatch" title="1: #ab5675" style="background:#ab5675"></span>
<span class="swatch" title="2: #ee6a7c" style="background:#ee6a7c"></span>
<span class="swatch" title="3: #ffa7a5" style="background:#ffa7a5"></span>
<span class="swatch" title="4: #ffe07e" style="background:#ffe07e"></span>
<span class="swatch" title="5: #ffe7d6" style="background:#ffe7d6"></span>
<span class="swatch" title="6: #72dcbb" style="background:#72dcbb"></span>
<span class="swatch" title="7: #34acba" style="background:#34acba"></span>
</div>

## Punolite Plus

`use_palette("punolite_plus")` — 25 colors

<div class="palette">
<span class="swatch" title="0: #431c3f" style="background:#431c3f"></span>
<span class="swatch" title="1: #6d324e" style="background:#6d324e"></span>
<span class="swatch" title="2: #a65658" style="background:#a65658"></span>
<span class="swatch" title="3: #c57763" style="background:#c57763"></span>
<span class="swatch" title="4: #de9d75" style="background:#de9d75"></span>
<span class="swatch" title="5: #f0d898" style="background:#f0d898"></span>
<span class="swatch" title="6: #eef3aa" style="background:#eef3aa"></span>
<span class="swatch" title="7: #bef3aa" style="background:#bef3aa"></span>
<span class="swatch" title="8: #69c886" style="background:#69c886"></span>
<span class="swatch" title="9: #50aa82" style="background:#50aa82"></span>
<span class="swatch" title="10: #3d766d" style="background:#3d766d"></span>
<span class="swatch" title="11: #294e58" style="background:#294e58"></span>
<span class="swatch" title="12: #06041b" style="background:#06041b"></span>
<span class="swatch" title="13: #101b4c" style="background:#101b4c"></span>
<span class="swatch" title="14: #1e4676" style="background:#1e4676"></span>
<span class="swatch" title="15: #377d99" style="background:#377d99"></span>
<span class="swatch" title="16: #61b6b1" style="background:#61b6b1"></span>
<span class="swatch" title="17: #90d5bf" style="background:#90d5bf"></span>
<span class="swatch" title="18: #c7eada" style="background:#c7eada"></span>
<span class="swatch" title="19: #aacec8" style="background:#aacec8"></span>
<span class="swatch" title="20: #96b9b9" style="background:#96b9b9"></span>
<span class="swatch" title="21: #809da4" style="background:#809da4"></span>
<span class="swatch" title="22: #647789" style="background:#647789"></span>
<span class="swatch" title="23: #535d76" style="background:#535d76"></span>
<span class="swatch" title="24: #3b3c58" style="background:#3b3c58"></span>
</div>

## Punolite Plus Plus

`use_palette("punolite_plus_plus")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #2e2e43" style="background:#2e2e43"></span>
<span class="swatch" title="1: #4a4b5b" style="background:#4a4b5b"></span>
<span class="swatch" title="2: #707b89" style="background:#707b89"></span>
<span class="swatch" title="3: #a9bcbf" style="background:#a9bcbf"></span>
<span class="swatch" title="4: #e6eeed" style="background:#e6eeed"></span>
<span class="swatch" title="5: #fcfbf3" style="background:#fcfbf3"></span>
<span class="swatch" title="6: #fceba8" style="background:#fceba8"></span>
<span class="swatch" title="7: #f5c47c" style="background:#f5c47c"></span>
<span class="swatch" title="8: #e39764" style="background:#e39764"></span>
<span class="swatch" title="9: #c06852" style="background:#c06852"></span>
<span class="swatch" title="10: #9d4343" style="background:#9d4343"></span>
<span class="swatch" title="11: #813645" style="background:#813645"></span>
<span class="swatch" title="12: #542240" style="background:#542240"></span>
<span class="swatch" title="13: #2a152d" style="background:#2a152d"></span>
<span class="swatch" title="14: #4f2d4d" style="background:#4f2d4d"></span>
<span class="swatch" title="15: #5b3a56" style="background:#5b3a56"></span>
<span class="swatch" title="16: #794e6d" style="background:#794e6d"></span>
<span class="swatch" title="17: #3e4c7e" style="background:#3e4c7e"></span>
<span class="swatch" title="18: #495f94" style="background:#495f94"></span>
<span class="swatch" title="19: #5a78b2" style="background:#5a78b2"></span>
<span class="swatch" title="20: #7396d5" style="background:#7396d5"></span>
<span class="swatch" title="21: #7fbbdc" style="background:#7fbbdc"></span>
<span class="swatch" title="22: #aaeeea" style="background:#aaeeea"></span>
<span class="swatch" title="23: #d5f893" style="background:#d5f893"></span>
<span class="swatch" title="24: #96dc7f" style="background:#96dc7f"></span>
<span class="swatch" title="25: #6ec077" style="background:#6ec077"></span>
<span class="swatch" title="26: #4e9363" style="background:#4e9363"></span>
<span class="swatch" title="27: #3c6c54" style="background:#3c6c54"></span>
<span class="swatch" title="28: #2c5049" style="background:#2c5049"></span>
<span class="swatch" title="29: #34404f" style="background:#34404f"></span>
<span class="swatch" title="30: #405967" style="background:#405967"></span>
<span class="swatch" title="31: #5c8995" style="background:#5c8995"></span>
</div>

## Purplemorning8

`use_palette("purplemorning8")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #211d38" style="background:#211d38"></span>
<span class="swatch" title="1: #2e2a4f" style="background:#2e2a4f"></span>
<span class="swatch" title="2: #3b405e" style="background:#3b405e"></span>
<span class="swatch" title="3: #60556e" style="background:#60556e"></span>
<span class="swatch" title="4: #9a6278" style="background:#9a6278"></span>
<span class="swatch" title="5: #c7786f" style="background:#c7786f"></span>
<span class="swatch" title="6: #cfa98a" style="background:#cfa98a"></span>
<span class="swatch" title="7: #cdd4a5" style="background:#cdd4a5"></span>
</div>

## Resurrect 64

`use_palette("resurrect_64")` — 64 colors

<div class="palette">
<span class="swatch" title="0: #2e222f" style="background:#2e222f"></span>
<span class="swatch" title="1: #3e3546" style="background:#3e3546"></span>
<span class="swatch" title="2: #625565" style="background:#625565"></span>
<span class="swatch" title="3: #966c6c" style="background:#966c6c"></span>
<span class="swatch" title="4: #ab947a" style="background:#ab947a"></span>
<span class="swatch" title="5: #694f62" style="background:#694f62"></span>
<span class="swatch" title="6: #7f708a" style="background:#7f708a"></span>
<span class="swatch" title="7: #9babb2" style="background:#9babb2"></span>
<span class="swatch" title="8: #c7dcd0" style="background:#c7dcd0"></span>
<span class="swatch" title="9: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="10: #6e2727" style="background:#6e2727"></span>
<span class="swatch" title="11: #b33831" style="background:#b33831"></span>
<span class="swatch" title="12: #ea4f36" style="background:#ea4f36"></span>
<span class="swatch" title="13: #f57d4a" style="background:#f57d4a"></span>
<span class="swatch" title="14: #ae2334" style="background:#ae2334"></span>
<span class="swatch" title="15: #e83b3b" style="background:#e83b3b"></span>
<span class="swatch" title="16: #fb6b1d" style="background:#fb6b1d"></span>
<span class="swatch" title="17: #f79617" style="background:#f79617"></span>
<span class="swatch" title="18: #f9c22b" style="background:#f9c22b"></span>
<span class="swatch" title="19: #7a3045" style="background:#7a3045"></span>
<span class="swatch" title="20: #9e4539" style="background:#9e4539"></span>
<span class="swatch" title="21: #cd683d" style="background:#cd683d"></span>
<span class="swatch" title="22: #e6904e" style="background:#e6904e"></span>
<span class="swatch" title="23: #fbb954" style="background:#fbb954"></span>
<span class="swatch" title="24: #4c3e24" style="background:#4c3e24"></span>
<span class="swatch" title="25: #676633" style="background:#676633"></span>
<span class="swatch" title="26: #a2a947" style="background:#a2a947"></span>
<span class="swatch" title="27: #d5e04b" style="background:#d5e04b"></span>
<span class="swatch" title="28: #fbff86" style="background:#fbff86"></span>
<span class="swatch" title="29: #165a4c" style="background:#165a4c"></span>
<span class="swatch" title="30: #239063" style="background:#239063"></span>
<span class="swatch" title="31: #1ebc73" style="background:#1ebc73"></span>
<span class="swatch" title="32: #91db69" style="background:#91db69"></span>
<span class="swatch" title="33: #cddf6c" style="background:#cddf6c"></span>
<span class="swatch" title="34: #313638" style="background:#313638"></span>
<span class="swatch" title="35: #374e4a" style="background:#374e4a"></span>
<span class="swatch" title="36: #547e64" style="background:#547e64"></span>
<span class="swatch" title="37: #92a984" style="background:#92a984"></span>
<span class="swatch" title="38: #b2ba90" style="background:#b2ba90"></span>
<span class="swatch" title="39: #0b5e65" style="background:#0b5e65"></span>
<span class="swatch" title="40: #0b8a8f" style="background:#0b8a8f"></span>
<span class="swatch" title="41: #0eaf9b" style="background:#0eaf9b"></span>
<span class="swatch" title="42: #30e1b9" style="background:#30e1b9"></span>
<span class="swatch" title="43: #8ff8e2" style="background:#8ff8e2"></span>
<span class="swatch" title="44: #323353" style="background:#323353"></span>
<span class="swatch" title="45: #484a77" style="background:#484a77"></span>
<span class="swatch" title="46: #4d65b4" style="background:#4d65b4"></span>
<span class="swatch" title="47: #4d9be6" style="background:#4d9be6"></span>
<span class="swatch" title="48: #8fd3ff" style="background:#8fd3ff"></span>
<span class="swatch" title="49: #45293f" style="background:#45293f"></span>
<span class="swatch" title="50: #6b3e75" style="background:#6b3e75"></span>
<span class="swatch" title="51: #905ea9" style="background:#905ea9"></span>
<span class="swatch" title="52: #a884f3" style="background:#a884f3"></span>
<span class="swatch" title="53: #eaaded" style="background:#eaaded"></span>
<span class="swatch" title="54: #753c54" style="background:#753c54"></span>
<span class="swatch" title="55: #a24b6f" style="background:#a24b6f"></span>
<span class="swatch" title="56: #cf657f" style="background:#cf657f"></span>
<span class="swatch" title="57: #ed8099" style="background:#ed8099"></span>
<span class="swatch" title="58: #831c5d" style="background:#831c5d"></span>
<span class="swatch" title="59: #c32454" style="background:#c32454"></span>
<span class="swatch" title="60: #f04f78" style="background:#f04f78"></span>
<span class="swatch" title="61: #f68181" style="background:#f68181"></span>
<span class="swatch" title="62: #fca790" style="background:#fca790"></span>
<span class="swatch" title="63: #fdcbb0" style="background:#fdcbb0"></span>
</div>

## Retrobubble

`use_palette("retrobubble")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #9dc1c0" style="background:#9dc1c0"></span>
<span class="swatch" title="1: #525b80" style="background:#525b80"></span>
<span class="swatch" title="2: #312139" style="background:#312139"></span>
<span class="swatch" title="3: #120e1f" style="background:#120e1f"></span>
<span class="swatch" title="4: #284646" style="background:#284646"></span>
<span class="swatch" title="5: #62ab46" style="background:#62ab46"></span>
<span class="swatch" title="6: #95533d" style="background:#95533d"></span>
<span class="swatch" title="7: #6a2435" style="background:#6a2435"></span>
<span class="swatch" title="8: #654147" style="background:#654147"></span>
<span class="swatch" title="9: #fff169" style="background:#fff169"></span>
<span class="swatch" title="10: #d7793f" style="background:#d7793f"></span>
<span class="swatch" title="11: #ab3229" style="background:#ab3229"></span>
<span class="swatch" title="12: #9e8f84" style="background:#9e8f84"></span>
<span class="swatch" title="13: #ffface" style="background:#ffface"></span>
<span class="swatch" title="14: #e0b56d" style="background:#e0b56d"></span>
<span class="swatch" title="15: #f68b69" style="background:#f68b69"></span>
</div>

## Retrocal 8

`use_palette("retrocal_8")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #6eb8a8" style="background:#6eb8a8"></span>
<span class="swatch" title="1: #2a584f" style="background:#2a584f"></span>
<span class="swatch" title="2: #74a33f" style="background:#74a33f"></span>
<span class="swatch" title="3: #fcffc0" style="background:#fcffc0"></span>
<span class="swatch" title="4: #c6505a" style="background:#c6505a"></span>
<span class="swatch" title="5: #2f142f" style="background:#2f142f"></span>
<span class="swatch" title="6: #774448" style="background:#774448"></span>
<span class="swatch" title="7: #ee9c5d" style="background:#ee9c5d"></span>
</div>

## Rustic Gb

`use_palette("rustic_gb")` — 4 colors

<div class="palette">
<span class="swatch" title="0: #2c2137" style="background:#2c2137"></span>
<span class="swatch" title="1: #764462" style="background:#764462"></span>
<span class="swatch" title="2: #edb4a1" style="background:#edb4a1"></span>
<span class="swatch" title="3: #a96868" style="background:#a96868"></span>
</div>

## Ry 64

`use_palette("ry_64")` — 64 colors

<div class="palette">
<span class="swatch" title="0: #2f1e45" style="background:#2f1e45"></span>
<span class="swatch" title="1: #6a1948" style="background:#6a1948"></span>
<span class="swatch" title="2: #901a4d" style="background:#901a4d"></span>
<span class="swatch" title="3: #c1264b" style="background:#c1264b"></span>
<span class="swatch" title="4: #df3551" style="background:#df3551"></span>
<span class="swatch" title="5: #ee5959" style="background:#ee5959"></span>
<span class="swatch" title="6: #e48b47" style="background:#e48b47"></span>
<span class="swatch" title="7: #d86545" style="background:#d86545"></span>
<span class="swatch" title="8: #bb4343" style="background:#bb4343"></span>
<span class="swatch" title="9: #a52c49" style="background:#a52c49"></span>
<span class="swatch" title="10: #8a1f40" style="background:#8a1f40"></span>
<span class="swatch" title="11: #4e1829" style="background:#4e1829"></span>
<span class="swatch" title="12: #632337" style="background:#632337"></span>
<span class="swatch" title="13: #7a3243" style="background:#7a3243"></span>
<span class="swatch" title="14: #8f4747" style="background:#8f4747"></span>
<span class="swatch" title="15: #ac6754" style="background:#ac6754"></span>
<span class="swatch" title="16: #be8960" style="background:#be8960"></span>
<span class="swatch" title="17: #cfa35f" style="background:#cfa35f"></span>
<span class="swatch" title="18: #f5cf8a" style="background:#f5cf8a"></span>
<span class="swatch" title="19: #db9d28" style="background:#db9d28"></span>
<span class="swatch" title="20: #a76609" style="background:#a76609"></span>
<span class="swatch" title="21: #803d11" style="background:#803d11"></span>
<span class="swatch" title="22: #444800" style="background:#444800"></span>
<span class="swatch" title="23: #5e5d0a" style="background:#5e5d0a"></span>
<span class="swatch" title="24: #817c14" style="background:#817c14"></span>
<span class="swatch" title="25: #a7983a" style="background:#a7983a"></span>
<span class="swatch" title="26: #bfaf60" style="background:#bfaf60"></span>
<span class="swatch" title="27: #c9e276" style="background:#c9e276"></span>
<span class="swatch" title="28: #90b53a" style="background:#90b53a"></span>
<span class="swatch" title="29: #5d9226" style="background:#5d9226"></span>
<span class="swatch" title="30: #0f6a2e" style="background:#0f6a2e"></span>
<span class="swatch" title="31: #0c403b" style="background:#0c403b"></span>
<span class="swatch" title="32: #16315e" style="background:#16315e"></span>
<span class="swatch" title="33: #0f4d69" style="background:#0f4d69"></span>
<span class="swatch" title="34: #1c707f" style="background:#1c707f"></span>
<span class="swatch" title="35: #269992" style="background:#269992"></span>
<span class="swatch" title="36: #6dc0b4" style="background:#6dc0b4"></span>
<span class="swatch" title="37: #75d9f2" style="background:#75d9f2"></span>
<span class="swatch" title="38: #55a7d4" style="background:#55a7d4"></span>
<span class="swatch" title="39: #3a8bc2" style="background:#3a8bc2"></span>
<span class="swatch" title="40: #2c5791" style="background:#2c5791"></span>
<span class="swatch" title="41: #183360" style="background:#183360"></span>
<span class="swatch" title="42: #7d2f7e" style="background:#7d2f7e"></span>
<span class="swatch" title="43: #a83690" style="background:#a83690"></span>
<span class="swatch" title="44: #ce4999" style="background:#ce4999"></span>
<span class="swatch" title="45: #f27dcd" style="background:#f27dcd"></span>
<span class="swatch" title="46: #fbb8ff" style="background:#fbb8ff"></span>
<span class="swatch" title="47: #c783e9" style="background:#c783e9"></span>
<span class="swatch" title="48: #a750c4" style="background:#a750c4"></span>
<span class="swatch" title="49: #743c9f" style="background:#743c9f"></span>
<span class="swatch" title="50: #493277" style="background:#493277"></span>
<span class="swatch" title="51: #372466" style="background:#372466"></span>
<span class="swatch" title="52: #1a3349" style="background:#1a3349"></span>
<span class="swatch" title="53: #34495c" style="background:#34495c"></span>
<span class="swatch" title="54: #45596b" style="background:#45596b"></span>
<span class="swatch" title="55: #607884" style="background:#607884"></span>
<span class="swatch" title="56: #79999b" style="background:#79999b"></span>
<span class="swatch" title="57: #e6eaea" style="background:#e6eaea"></span>
<span class="swatch" title="58: #b9cbc7" style="background:#b9cbc7"></span>
<span class="swatch" title="59: #91a8a8" style="background:#91a8a8"></span>
<span class="swatch" title="60: #6d7f85" style="background:#6d7f85"></span>
<span class="swatch" title="61: #53606b" style="background:#53606b"></span>
<span class="swatch" title="62: #3c4550" style="background:#3c4550"></span>
<span class="swatch" title="63: #222734" style="background:#222734"></span>
</div>

## Shanty

`use_palette("shanty")` — 48 colors

<div class="palette">
<span class="swatch" title="0: #1e1526" style="background:#1e1526"></span>
<span class="swatch" title="1: #343147" style="background:#343147"></span>
<span class="swatch" title="2: #404861" style="background:#404861"></span>
<span class="swatch" title="3: #5a758f" style="background:#5a758f"></span>
<span class="swatch" title="4: #8eb2bd" style="background:#8eb2bd"></span>
<span class="swatch" title="5: #152b24" style="background:#152b24"></span>
<span class="swatch" title="6: #1d4732" style="background:#1d4732"></span>
<span class="swatch" title="7: #488535" style="background:#488535"></span>
<span class="swatch" title="8: #77c242" style="background:#77c242"></span>
<span class="swatch" title="9: #c6e563" style="background:#c6e563"></span>
<span class="swatch" title="10: #ddf19c" style="background:#ddf19c"></span>
<span class="swatch" title="11: #a9da86" style="background:#a9da86"></span>
<span class="swatch" title="12: #8ab27d" style="background:#8ab27d"></span>
<span class="swatch" title="13: #f28ddb" style="background:#f28ddb"></span>
<span class="swatch" title="14: #de4ee6" style="background:#de4ee6"></span>
<span class="swatch" title="15: #9143cc" style="background:#9143cc"></span>
<span class="swatch" title="16: #3a2d73" style="background:#3a2d73"></span>
<span class="swatch" title="17: #214780" style="background:#214780"></span>
<span class="swatch" title="18: #1875cc" style="background:#1875cc"></span>
<span class="swatch" title="19: #18b3f5" style="background:#18b3f5"></span>
<span class="swatch" title="20: #3de5f5" style="background:#3de5f5"></span>
<span class="swatch" title="21: #f5f5f7" style="background:#f5f5f7"></span>
<span class="swatch" title="22: #bfeaf5" style="background:#bfeaf5"></span>
<span class="swatch" title="23: #93cfed" style="background:#93cfed"></span>
<span class="swatch" title="24: #f5915b" style="background:#f5915b"></span>
<span class="swatch" title="25: #bd5044" style="background:#bd5044"></span>
<span class="swatch" title="26: #6e2b23" style="background:#6e2b23"></span>
<span class="swatch" title="27: #301b2a" style="background:#301b2a"></span>
<span class="swatch" title="28: #4f293b" style="background:#4f293b"></span>
<span class="swatch" title="29: #854657" style="background:#854657"></span>
<span class="swatch" title="30: #b06a72" style="background:#b06a72"></span>
<span class="swatch" title="31: #e69e97" style="background:#e69e97"></span>
<span class="swatch" title="32: #facc34" style="background:#facc34"></span>
<span class="swatch" title="33: #fa9a41" style="background:#fa9a41"></span>
<span class="swatch" title="34: #e86d25" style="background:#e86d25"></span>
<span class="swatch" title="35: #96181e" style="background:#96181e"></span>
<span class="swatch" title="36: #d10f2f" style="background:#d10f2f"></span>
<span class="swatch" title="37: #f02645" style="background:#f02645"></span>
<span class="swatch" title="38: #362427" style="background:#362427"></span>
<span class="swatch" title="39: #693c3c" style="background:#693c3c"></span>
<span class="swatch" title="40: #875340" style="background:#875340"></span>
<span class="swatch" title="41: #b38247" style="background:#b38247"></span>
<span class="swatch" title="42: #deb87a" style="background:#deb87a"></span>
<span class="swatch" title="43: #e7dbad" style="background:#e7dbad"></span>
<span class="swatch" title="44: #ad9e7b" style="background:#ad9e7b"></span>
<span class="swatch" title="45: #94866b" style="background:#94866b"></span>
<span class="swatch" title="46: #73695a" style="background:#73695a"></span>
<span class="swatch" title="47: #5a514a" style="background:#5a514a"></span>
</div>

## Sheltzy32

`use_palette("sheltzy32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #8cffde" style="background:#8cffde"></span>
<span class="swatch" title="1: #45b8b3" style="background:#45b8b3"></span>
<span class="swatch" title="2: #839740" style="background:#839740"></span>
<span class="swatch" title="3: #c9ec85" style="background:#c9ec85"></span>
<span class="swatch" title="4: #46c657" style="background:#46c657"></span>
<span class="swatch" title="5: #158968" style="background:#158968"></span>
<span class="swatch" title="6: #2c5b6d" style="background:#2c5b6d"></span>
<span class="swatch" title="7: #222a5c" style="background:#222a5c"></span>
<span class="swatch" title="8: #566a89" style="background:#566a89"></span>
<span class="swatch" title="9: #8babbf" style="background:#8babbf"></span>
<span class="swatch" title="10: #cce2e1" style="background:#cce2e1"></span>
<span class="swatch" title="11: #ffdba5" style="background:#ffdba5"></span>
<span class="swatch" title="12: #ccac68" style="background:#ccac68"></span>
<span class="swatch" title="13: #a36d3e" style="background:#a36d3e"></span>
<span class="swatch" title="14: #683c34" style="background:#683c34"></span>
<span class="swatch" title="15: #000000" style="background:#000000"></span>
<span class="swatch" title="16: #38002c" style="background:#38002c"></span>
<span class="swatch" title="17: #663b93" style="background:#663b93"></span>
<span class="swatch" title="18: #8b72de" style="background:#8b72de"></span>
<span class="swatch" title="19: #9cd8fc" style="background:#9cd8fc"></span>
<span class="swatch" title="20: #5e96dd" style="background:#5e96dd"></span>
<span class="swatch" title="21: #3953c0" style="background:#3953c0"></span>
<span class="swatch" title="22: #800c53" style="background:#800c53"></span>
<span class="swatch" title="23: #c34b91" style="background:#c34b91"></span>
<span class="swatch" title="24: #ff94b3" style="background:#ff94b3"></span>
<span class="swatch" title="25: #bd1f3f" style="background:#bd1f3f"></span>
<span class="swatch" title="26: #ec614a" style="background:#ec614a"></span>
<span class="swatch" title="27: #ffa468" style="background:#ffa468"></span>
<span class="swatch" title="28: #fff6ae" style="background:#fff6ae"></span>
<span class="swatch" title="29: #ffda70" style="background:#ffda70"></span>
<span class="swatch" title="30: #f4b03c" style="background:#f4b03c"></span>
<span class="swatch" title="31: #ffffff" style="background:#ffffff"></span>
</div>

## Slso8

`use_palette("slso8")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #0d2b45" style="background:#0d2b45"></span>
<span class="swatch" title="1: #203c56" style="background:#203c56"></span>
<span class="swatch" title="2: #544e68" style="background:#544e68"></span>
<span class="swatch" title="3: #8d697a" style="background:#8d697a"></span>
<span class="swatch" title="4: #d08159" style="background:#d08159"></span>
<span class="swatch" title="5: #ffaa5e" style="background:#ffaa5e"></span>
<span class="swatch" title="6: #ffd4a3" style="background:#ffd4a3"></span>
<span class="swatch" title="7: #ffecd6" style="background:#ffecd6"></span>
</div>

## Softmilk 32

`use_palette("softmilk_32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #23213d" style="background:#23213d"></span>
<span class="swatch" title="1: #d95b9a" style="background:#d95b9a"></span>
<span class="swatch" title="2: #9e4491" style="background:#9e4491"></span>
<span class="swatch" title="3: #633662" style="background:#633662"></span>
<span class="swatch" title="4: #903d62" style="background:#903d62"></span>
<span class="swatch" title="5: #bd515a" style="background:#bd515a"></span>
<span class="swatch" title="6: #d69a4e" style="background:#d69a4e"></span>
<span class="swatch" title="7: #f3d040" style="background:#f3d040"></span>
<span class="swatch" title="8: #ffe88c" style="background:#ffe88c"></span>
<span class="swatch" title="9: #f2f2f0" style="background:#f2f2f0"></span>
<span class="swatch" title="10: #94e092" style="background:#94e092"></span>
<span class="swatch" title="11: #1f9983" style="background:#1f9983"></span>
<span class="swatch" title="12: #22636b" style="background:#22636b"></span>
<span class="swatch" title="13: #57546f" style="background:#57546f"></span>
<span class="swatch" title="14: #c56876" style="background:#c56876"></span>
<span class="swatch" title="15: #76747d" style="background:#76747d"></span>
<span class="swatch" title="16: #5c3841" style="background:#5c3841"></span>
<span class="swatch" title="17: #945848" style="background:#945848"></span>
<span class="swatch" title="18: #d17f6b" style="background:#d17f6b"></span>
<span class="swatch" title="19: #eb9f7f" style="background:#eb9f7f"></span>
<span class="swatch" title="20: #f1c28f" style="background:#f1c28f"></span>
<span class="swatch" title="21: #b9b5c3" style="background:#b9b5c3"></span>
<span class="swatch" title="22: #454194" style="background:#454194"></span>
<span class="swatch" title="23: #425bbd" style="background:#425bbd"></span>
<span class="swatch" title="24: #4884d4" style="background:#4884d4"></span>
<span class="swatch" title="25: #45a1de" style="background:#45a1de"></span>
<span class="swatch" title="26: #7cd8eb" style="background:#7cd8eb"></span>
<span class="swatch" title="27: #e2f266" style="background:#e2f266"></span>
<span class="swatch" title="28: #c3d442" style="background:#c3d442"></span>
<span class="swatch" title="29: #82aa28" style="background:#82aa28"></span>
<span class="swatch" title="30: #597f1e" style="background:#597f1e"></span>
<span class="swatch" title="31: #376129" style="background:#376129"></span>
</div>

## Suez 30

`use_palette("suez_30")` — 30 colors

<div class="palette">
<span class="swatch" title="0: #c4a78b" style="background:#c4a78b"></span>
<span class="swatch" title="1: #7d665f" style="background:#7d665f"></span>
<span class="swatch" title="2: #493936" style="background:#493936"></span>
<span class="swatch" title="3: #200d0a" style="background:#200d0a"></span>
<span class="swatch" title="4: #5f2323" style="background:#5f2323"></span>
<span class="swatch" title="5: #78311d" style="background:#78311d"></span>
<span class="swatch" title="6: #944c2e" style="background:#944c2e"></span>
<span class="swatch" title="7: #83453e" style="background:#83453e"></span>
<span class="swatch" title="8: #c36846" style="background:#c36846"></span>
<span class="swatch" title="9: #e29365" style="background:#e29365"></span>
<span class="swatch" title="10: #fbbb81" style="background:#fbbb81"></span>
<span class="swatch" title="11: #ffdba5" style="background:#ffdba5"></span>
<span class="swatch" title="12: #fff3cd" style="background:#fff3cd"></span>
<span class="swatch" title="13: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="14: #ffe892" style="background:#ffe892"></span>
<span class="swatch" title="15: #fbc669" style="background:#fbc669"></span>
<span class="swatch" title="16: #db6447" style="background:#db6447"></span>
<span class="swatch" title="17: #b3382a" style="background:#b3382a"></span>
<span class="swatch" title="18: #e5e4b8" style="background:#e5e4b8"></span>
<span class="swatch" title="19: #b3b887" style="background:#b3b887"></span>
<span class="swatch" title="20: #6c8760" style="background:#6c8760"></span>
<span class="swatch" title="21: #305b46" style="background:#305b46"></span>
<span class="swatch" title="22: #303c52" style="background:#303c52"></span>
<span class="swatch" title="23: #e4fbe2" style="background:#e4fbe2"></span>
<span class="swatch" title="24: #c3dbce" style="background:#c3dbce"></span>
<span class="swatch" title="25: #89b5b0" style="background:#89b5b0"></span>
<span class="swatch" title="26: #5c8197" style="background:#5c8197"></span>
<span class="swatch" title="27: #425985" style="background:#425985"></span>
<span class="swatch" title="28: #403675" style="background:#403675"></span>
<span class="swatch" title="29: #230d51" style="background:#230d51"></span>
</div>

## Sunshine Valley

`use_palette("sunshine_valley")` — 49 colors

<div class="palette">
<span class="swatch" title="0: #0e0e1a" style="background:#0e0e1a"></span>
<span class="swatch" title="1: #2b1f4d" style="background:#2b1f4d"></span>
<span class="swatch" title="2: #513185" style="background:#513185"></span>
<span class="swatch" title="3: #8235bd" style="background:#8235bd"></span>
<span class="swatch" title="4: #c36ac4" style="background:#c36ac4"></span>
<span class="swatch" title="5: #eb83dd" style="background:#eb83dd"></span>
<span class="swatch" title="6: #f0c5df" style="background:#f0c5df"></span>
<span class="swatch" title="7: #93f0fa" style="background:#93f0fa"></span>
<span class="swatch" title="8: #76ccf5" style="background:#76ccf5"></span>
<span class="swatch" title="9: #51a6f0" style="background:#51a6f0"></span>
<span class="swatch" title="10: #3760c8" style="background:#3760c8"></span>
<span class="swatch" title="11: #3c4891" style="background:#3c4891"></span>
<span class="swatch" title="12: #2c3661" style="background:#2c3661"></span>
<span class="swatch" title="13: #f0baa3" style="background:#f0baa3"></span>
<span class="swatch" title="14: #d6968b" style="background:#d6968b"></span>
<span class="swatch" title="15: #d17e79" style="background:#d17e79"></span>
<span class="swatch" title="16: #b56d77" style="background:#b56d77"></span>
<span class="swatch" title="17: #965367" style="background:#965367"></span>
<span class="swatch" title="18: #853e61" style="background:#853e61"></span>
<span class="swatch" title="19: #57352c" style="background:#57352c"></span>
<span class="swatch" title="20: #784735" style="background:#784735"></span>
<span class="swatch" title="21: #9e643f" style="background:#9e643f"></span>
<span class="swatch" title="22: #c78350" style="background:#c78350"></span>
<span class="swatch" title="23: #d99f66" style="background:#d99f66"></span>
<span class="swatch" title="24: #e6c07e" style="background:#e6c07e"></span>
<span class="swatch" title="25: #edf067" style="background:#edf067"></span>
<span class="swatch" title="26: #d6b751" style="background:#d6b751"></span>
<span class="swatch" title="27: #bf872c" style="background:#bf872c"></span>
<span class="swatch" title="28: #b5671f" style="background:#b5671f"></span>
<span class="swatch" title="29: #963e1e" style="background:#963e1e"></span>
<span class="swatch" title="30: #802114" style="background:#802114"></span>
<span class="swatch" title="31: #611b2a" style="background:#611b2a"></span>
<span class="swatch" title="32: #b02e3b" style="background:#b02e3b"></span>
<span class="swatch" title="33: #de3c31" style="background:#de3c31"></span>
<span class="swatch" title="34: #f55e38" style="background:#f55e38"></span>
<span class="swatch" title="35: #f78952" style="background:#f78952"></span>
<span class="swatch" title="36: #fcb177" style="background:#fcb177"></span>
<span class="swatch" title="37: #c8ed8c" style="background:#c8ed8c"></span>
<span class="swatch" title="38: #86d468" style="background:#86d468"></span>
<span class="swatch" title="39: #4cbd48" style="background:#4cbd48"></span>
<span class="swatch" title="40: #3f8f4f" style="background:#3f8f4f"></span>
<span class="swatch" title="41: #366e4d" style="background:#366e4d"></span>
<span class="swatch" title="42: #274d41" style="background:#274d41"></span>
<span class="swatch" title="43: #22202e" style="background:#22202e"></span>
<span class="swatch" title="44: #3b3d4d" style="background:#3b3d4d"></span>
<span class="swatch" title="45: #69728a" style="background:#69728a"></span>
<span class="swatch" title="46: #8294ab" style="background:#8294ab"></span>
<span class="swatch" title="47: #abc7d9" style="background:#abc7d9"></span>
<span class="swatch" title="48: #f5f8fa" style="background:#f5f8fa"></span>
</div>

## Sweet Canyon Extended 64

`use_palette("sweet_canyon_extended_64")` — 64 colors

<div class="palette">
<span class="swatch" title="0: #0f0e11" style="background:#0f0e11"></span>
<span class="swatch" title="1: #2d2c33" style="background:#2d2c33"></span>
<span class="swatch" title="2: #40404a" style="background:#40404a"></span>
<span class="swatch" title="3: #51545c" style="background:#51545c"></span>
<span class="swatch" title="4: #6b7179" style="background:#6b7179"></span>
<span class="swatch" title="5: #7c8389" style="background:#7c8389"></span>
<span class="swatch" title="6: #a8b2b6" style="background:#a8b2b6"></span>
<span class="swatch" title="7: #d5d5d5" style="background:#d5d5d5"></span>
<span class="swatch" title="8: #eeebe0" style="background:#eeebe0"></span>
<span class="swatch" title="9: #f1dbb1" style="background:#f1dbb1"></span>
<span class="swatch" title="10: #eec99f" style="background:#eec99f"></span>
<span class="swatch" title="11: #e1a17e" style="background:#e1a17e"></span>
<span class="swatch" title="12: #cc9562" style="background:#cc9562"></span>
<span class="swatch" title="13: #ab7b49" style="background:#ab7b49"></span>
<span class="swatch" title="14: #9a643a" style="background:#9a643a"></span>
<span class="swatch" title="15: #86482f" style="background:#86482f"></span>
<span class="swatch" title="16: #783a29" style="background:#783a29"></span>
<span class="swatch" title="17: #6a3328" style="background:#6a3328"></span>
<span class="swatch" title="18: #541d29" style="background:#541d29"></span>
<span class="swatch" title="19: #42192c" style="background:#42192c"></span>
<span class="swatch" title="20: #512240" style="background:#512240"></span>
<span class="swatch" title="21: #782349" style="background:#782349"></span>
<span class="swatch" title="22: #8b2e5d" style="background:#8b2e5d"></span>
<span class="swatch" title="23: #a93e89" style="background:#a93e89"></span>
<span class="swatch" title="24: #d062c8" style="background:#d062c8"></span>
<span class="swatch" title="25: #ec94ea" style="background:#ec94ea"></span>
<span class="swatch" title="26: #f2bdfc" style="background:#f2bdfc"></span>
<span class="swatch" title="27: #eaebff" style="background:#eaebff"></span>
<span class="swatch" title="28: #a2fafa" style="background:#a2fafa"></span>
<span class="swatch" title="29: #64e7e7" style="background:#64e7e7"></span>
<span class="swatch" title="30: #54cfd8" style="background:#54cfd8"></span>
<span class="swatch" title="31: #2fb6c3" style="background:#2fb6c3"></span>
<span class="swatch" title="32: #2c89af" style="background:#2c89af"></span>
<span class="swatch" title="33: #25739d" style="background:#25739d"></span>
<span class="swatch" title="34: #2a5684" style="background:#2a5684"></span>
<span class="swatch" title="35: #214574" style="background:#214574"></span>
<span class="swatch" title="36: #1f2966" style="background:#1f2966"></span>
<span class="swatch" title="37: #101445" style="background:#101445"></span>
<span class="swatch" title="38: #3c0d3b" style="background:#3c0d3b"></span>
<span class="swatch" title="39: #66164c" style="background:#66164c"></span>
<span class="swatch" title="40: #901f3d" style="background:#901f3d"></span>
<span class="swatch" title="41: #bb3030" style="background:#bb3030"></span>
<span class="swatch" title="42: #dc473c" style="background:#dc473c"></span>
<span class="swatch" title="43: #ec6a45" style="background:#ec6a45"></span>
<span class="swatch" title="44: #fb9b41" style="background:#fb9b41"></span>
<span class="swatch" title="45: #f0c04c" style="background:#f0c04c"></span>
<span class="swatch" title="46: #f4d66e" style="background:#f4d66e"></span>
<span class="swatch" title="47: #fffb76" style="background:#fffb76"></span>
<span class="swatch" title="48: #ccf17a" style="background:#ccf17a"></span>
<span class="swatch" title="49: #97d948" style="background:#97d948"></span>
<span class="swatch" title="50: #6fba3b" style="background:#6fba3b"></span>
<span class="swatch" title="51: #229443" style="background:#229443"></span>
<span class="swatch" title="52: #1d7e45" style="background:#1d7e45"></span>
<span class="swatch" title="53: #116548" style="background:#116548"></span>
<span class="swatch" title="54: #0c4f3f" style="background:#0c4f3f"></span>
<span class="swatch" title="55: #0a3639" style="background:#0a3639"></span>
<span class="swatch" title="56: #251746" style="background:#251746"></span>
<span class="swatch" title="57: #48246d" style="background:#48246d"></span>
<span class="swatch" title="58: #69189c" style="background:#69189c"></span>
<span class="swatch" title="59: #9f20c0" style="background:#9f20c0"></span>
<span class="swatch" title="60: #e527d2" style="background:#e527d2"></span>
<span class="swatch" title="61: #ff51cf" style="background:#ff51cf"></span>
<span class="swatch" title="62: #ff7ada" style="background:#ff7ada"></span>
<span class="swatch" title="63: #ff9edb" style="background:#ff9edb"></span>
</div>

## Sweet24

`use_palette("sweet24")` — 24 colors

<div class="palette">
<span class="swatch" title="0: #2c4941" style="background:#2c4941"></span>
<span class="swatch" title="1: #66a650" style="background:#66a650"></span>
<span class="swatch" title="2: #b9d850" style="background:#b9d850"></span>
<span class="swatch" title="3: #82dcd7" style="background:#82dcd7"></span>
<span class="swatch" title="4: #208cb2" style="background:#208cb2"></span>
<span class="swatch" title="5: #253348" style="background:#253348"></span>
<span class="swatch" title="6: #1d1b24" style="background:#1d1b24"></span>
<span class="swatch" title="7: #3a3a41" style="background:#3a3a41"></span>
<span class="swatch" title="8: #7a7576" style="background:#7a7576"></span>
<span class="swatch" title="9: #b59a66" style="background:#b59a66"></span>
<span class="swatch" title="10: #cec7b1" style="background:#cec7b1"></span>
<span class="swatch" title="11: #edefe2" style="background:#edefe2"></span>
<span class="swatch" title="12: #d78b98" style="background:#d78b98"></span>
<span class="swatch" title="13: #a13d77" style="background:#a13d77"></span>
<span class="swatch" title="14: #6d2047" style="background:#6d2047"></span>
<span class="swatch" title="15: #3c1c43" style="background:#3c1c43"></span>
<span class="swatch" title="16: #2c2228" style="background:#2c2228"></span>
<span class="swatch" title="17: #5e3735" style="background:#5e3735"></span>
<span class="swatch" title="18: #885a44" style="background:#885a44"></span>
<span class="swatch" title="19: #b8560f" style="background:#b8560f"></span>
<span class="swatch" title="20: #dc9824" style="background:#dc9824"></span>
<span class="swatch" title="21: #efcb84" style="background:#efcb84"></span>
<span class="swatch" title="22: #e68556" style="background:#e68556"></span>
<span class="swatch" title="23: #c02931" style="background:#c02931"></span>
</div>

## Sweetie 16

`use_palette("sweetie_16")` — 16 colors

<div class="palette">
<span class="swatch" title="0: #1a1c2c" style="background:#1a1c2c"></span>
<span class="swatch" title="1: #5d275d" style="background:#5d275d"></span>
<span class="swatch" title="2: #b13e53" style="background:#b13e53"></span>
<span class="swatch" title="3: #ef7d57" style="background:#ef7d57"></span>
<span class="swatch" title="4: #ffcd75" style="background:#ffcd75"></span>
<span class="swatch" title="5: #a7f070" style="background:#a7f070"></span>
<span class="swatch" title="6: #38b764" style="background:#38b764"></span>
<span class="swatch" title="7: #257179" style="background:#257179"></span>
<span class="swatch" title="8: #29366f" style="background:#29366f"></span>
<span class="swatch" title="9: #3b5dc9" style="background:#3b5dc9"></span>
<span class="swatch" title="10: #41a6f6" style="background:#41a6f6"></span>
<span class="swatch" title="11: #73eff7" style="background:#73eff7"></span>
<span class="swatch" title="12: #f4f4f4" style="background:#f4f4f4"></span>
<span class="swatch" title="13: #94b0c2" style="background:#94b0c2"></span>
<span class="swatch" title="14: #566c86" style="background:#566c86"></span>
<span class="swatch" title="15: #333c57" style="background:#333c57"></span>
</div>

## Tofu 20K

`use_palette("tofu_20k")` — 36 colors

<div class="palette">
<span class="swatch" title="0: #120a1a" style="background:#120a1a"></span>
<span class="swatch" title="1: #2a2a41" style="background:#2a2a41"></span>
<span class="swatch" title="2: #404863" style="background:#404863"></span>
<span class="swatch" title="3: #59607a" style="background:#59607a"></span>
<span class="swatch" title="4: #787d8b" style="background:#787d8b"></span>
<span class="swatch" title="5: #9da5ae" style="background:#9da5ae"></span>
<span class="swatch" title="6: #c8d6ac" style="background:#c8d6ac"></span>
<span class="swatch" title="7: #feffe5" style="background:#feffe5"></span>
<span class="swatch" title="8: #e4cd5a" style="background:#e4cd5a"></span>
<span class="swatch" title="9: #d49733" style="background:#d49733"></span>
<span class="swatch" title="10: #d68552" style="background:#d68552"></span>
<span class="swatch" title="11: #be5a1e" style="background:#be5a1e"></span>
<span class="swatch" title="12: #894835" style="background:#894835"></span>
<span class="swatch" title="13: #602631" style="background:#602631"></span>
<span class="swatch" title="14: #4b0c30" style="background:#4b0c30"></span>
<span class="swatch" title="15: #81173f" style="background:#81173f"></span>
<span class="swatch" title="16: #cc1825" style="background:#cc1825"></span>
<span class="swatch" title="17: #dc4926" style="background:#dc4926"></span>
<span class="swatch" title="18: #f1934c" style="background:#f1934c"></span>
<span class="swatch" title="19: #fad5af" style="background:#fad5af"></span>
<span class="swatch" title="20: #ed9d7c" style="background:#ed9d7c"></span>
<span class="swatch" title="21: #d16363" style="background:#d16363"></span>
<span class="swatch" title="22: #b7ab76" style="background:#b7ab76"></span>
<span class="swatch" title="23: #b59857" style="background:#b59857"></span>
<span class="swatch" title="24: #926d3c" style="background:#926d3c"></span>
<span class="swatch" title="25: #8b5b37" style="background:#8b5b37"></span>
<span class="swatch" title="26: #ff82a0" style="background:#ff82a0"></span>
<span class="swatch" title="27: #ff26a8" style="background:#ff26a8"></span>
<span class="swatch" title="28: #422490" style="background:#422490"></span>
<span class="swatch" title="29: #2749d0" style="background:#2749d0"></span>
<span class="swatch" title="30: #4477ff" style="background:#4477ff"></span>
<span class="swatch" title="31: #4cc5e4" style="background:#4cc5e4"></span>
<span class="swatch" title="32: #8bf5c6" style="background:#8bf5c6"></span>
<span class="swatch" title="33: #85c448" style="background:#85c448"></span>
<span class="swatch" title="34: #439d40" style="background:#439d40"></span>
<span class="swatch" title="35: #29694e" style="background:#29694e"></span>
</div>

## Vga

`use_palette("vga")` — 256 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #0000aa" style="background:#0000aa"></span>
<span class="swatch" title="2: #00aa00" style="background:#00aa00"></span>
<span class="swatch" title="3: #00aaaa" style="background:#00aaaa"></span>
<span class="swatch" title="4: #aa0000" style="background:#aa0000"></span>
<span class="swatch" title="5: #aa00aa" style="background:#aa00aa"></span>
<span class="swatch" title="6: #aa5500" style="background:#aa5500"></span>
<span class="swatch" title="7: #aaaaaa" style="background:#aaaaaa"></span>
<span class="swatch" title="8: #555555" style="background:#555555"></span>
<span class="swatch" title="9: #5555ff" style="background:#5555ff"></span>
<span class="swatch" title="10: #55ff55" style="background:#55ff55"></span>
<span class="swatch" title="11: #55ffff" style="background:#55ffff"></span>
<span class="swatch" title="12: #ff5555" style="background:#ff5555"></span>
<span class="swatch" title="13: #ff55ff" style="background:#ff55ff"></span>
<span class="swatch" title="14: #ffff55" style="background:#ffff55"></span>
<span class="swatch" title="15: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="16: #000000" style="background:#000000"></span>
<span class="swatch" title="17: #141414" style="background:#141414"></span>
<span class="swatch" title="18: #202020" style="background:#202020"></span>
<span class="swatch" title="19: #2c2c2c" style="background:#2c2c2c"></span>
<span class="swatch" title="20: #383838" style="background:#383838"></span>
<span class="swatch" title="21: #454545" style="background:#454545"></span>
<span class="swatch" title="22: #515151" style="background:#515151"></span>
<span class="swatch" title="23: #616161" style="background:#616161"></span>
<span class="swatch" title="24: #717171" style="background:#717171"></span>
<span class="swatch" title="25: #828282" style="background:#828282"></span>
<span class="swatch" title="26: #929292" style="background:#929292"></span>
<span class="swatch" title="27: #a2a2a2" style="background:#a2a2a2"></span>
<span class="swatch" title="28: #b6b6b6" style="background:#b6b6b6"></span>
<span class="swatch" title="29: #cbcbcb" style="background:#cbcbcb"></span>
<span class="swatch" title="30: #e3e3e3" style="background:#e3e3e3"></span>
<span class="swatch" title="31: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="32: #0000ff" style="background:#0000ff"></span>
<span class="swatch" title="33: #4100ff" style="background:#4100ff"></span>
<span class="swatch" title="34: #7d00ff" style="background:#7d00ff"></span>
<span class="swatch" title="35: #be00ff" style="background:#be00ff"></span>
<span class="swatch" title="36: #ff00ff" style="background:#ff00ff"></span>
<span class="swatch" title="37: #ff00be" style="background:#ff00be"></span>
<span class="swatch" title="38: #ff007d" style="background:#ff007d"></span>
<span class="swatch" title="39: #ff0041" style="background:#ff0041"></span>
<span class="swatch" title="40: #ff0000" style="background:#ff0000"></span>
<span class="swatch" title="41: #ff4100" style="background:#ff4100"></span>
<span class="swatch" title="42: #ff7d00" style="background:#ff7d00"></span>
<span class="swatch" title="43: #ffbe00" style="background:#ffbe00"></span>
<span class="swatch" title="44: #ffff00" style="background:#ffff00"></span>
<span class="swatch" title="45: #beff00" style="background:#beff00"></span>
<span class="swatch" title="46: #7dff00" style="background:#7dff00"></span>
<span class="swatch" title="47: #41ff00" style="background:#41ff00"></span>
<span class="swatch" title="48: #00ff00" style="background:#00ff00"></span>
<span class="swatch" title="49: #00ff41" style="background:#00ff41"></span>
<span class="swatch" title="50: #00ff7d" style="background:#00ff7d"></span>
<span class="swatch" title="51: #00ffbe" style="background:#00ffbe"></span>
<span class="swatch" title="52: #00ffff" style="background:#00ffff"></span>
<span class="swatch" title="53: #00beff" style="background:#00beff"></span>
<span class="swatch" title="54: #007dff" style="background:#007dff"></span>
<span class="swatch" title="55: #0041ff" style="background:#0041ff"></span>
<span class="swatch" title="56: #7d7dff" style="background:#7d7dff"></span>
<span class="swatch" title="57: #9e7dff" style="background:#9e7dff"></span>
<span class="swatch" title="58: #be7dff" style="background:#be7dff"></span>
<span class="swatch" title="59: #df7dff" style="background:#df7dff"></span>
<span class="swatch" title="60: #ff7dff" style="background:#ff7dff"></span>
<span class="swatch" title="61: #ff7ddf" style="background:#ff7ddf"></span>
<span class="swatch" title="62: #ff7dbe" style="background:#ff7dbe"></span>
<span class="swatch" title="63: #ff7d9e" style="background:#ff7d9e"></span>
<span class="swatch" title="64: #ff7d7d" style="background:#ff7d7d"></span>
<span class="swatch" title="65: #ff9e7d" style="background:#ff9e7d"></span>
<span class="swatch" title="66: #ffbe7d" style="background:#ffbe7d"></span>
<span class="swatch" title="67: #ffdf7d" style="background:#ffdf7d"></span>
<span class="swatch" title="68: #ffff7d" style="background:#ffff7d"></span>
<span class="swatch" title="69: #dfff7d" style="background:#dfff7d"></span>
<span class="swatch" title="70: #beff7d" style="background:#beff7d"></span>
<span class="swatch" title="71: #9eff7d" style="background:#9eff7d"></span>
<span class="swatch" title="72: #7dff7d" style="background:#7dff7d"></span>
<span class="swatch" title="73: #7dff9e" style="background:#7dff9e"></span>
<span class="swatch" title="74: #7dffbe" style="background:#7dffbe"></span>
<span class="swatch" title="75: #7dffdf" style="background:#7dffdf"></span>
<span class="swatch" title="76: #7dffff" style="background:#7dffff"></span>
<span class="swatch" title="77: #7ddfff" style="background:#7ddfff"></span>
<span class="swatch" title="78: #7dbeff" style="background:#7dbeff"></span>
<span class="swatch" title="79: #7d9eff" style="background:#7d9eff"></span>
<span class="swatch" title="80: #b6b6ff" style="background:#b6b6ff"></span>
<span class="swatch" title="81: #c7b6ff" style="background:#c7b6ff"></span>
<span class="swatch" title="82: #dbb6ff" style="background:#dbb6ff"></span>
<span class="swatch" title="83: #ebb6ff" style="background:#ebb6ff"></span>
<span class="swatch" title="84: #ffb6ff" style="background:#ffb6ff"></span>
<span class="swatch" title="85: #ffb6eb" style="background:#ffb6eb"></span>
<span class="swatch" title="86: #ffb6db" style="background:#ffb6db"></span>
<span class="swatch" title="87: #ffb6c7" style="background:#ffb6c7"></span>
<span class="swatch" title="88: #ffb6b6" style="background:#ffb6b6"></span>
<span class="swatch" title="89: #ffc7b6" style="background:#ffc7b6"></span>
<span class="swatch" title="90: #ffdbb6" style="background:#ffdbb6"></span>
<span class="swatch" title="91: #ffebb6" style="background:#ffebb6"></span>
<span class="swatch" title="92: #ffffb6" style="background:#ffffb6"></span>
<span class="swatch" title="93: #ebffb6" style="background:#ebffb6"></span>
<span class="swatch" title="94: #dbffb6" style="background:#dbffb6"></span>
<span class="swatch" title="95: #c7ffb6" style="background:#c7ffb6"></span>
<span class="swatch" title="96: #b6ffb6" style="background:#b6ffb6"></span>
<span class="swatch" title="97: #b6ffc7" style="background:#b6ffc7"></span>
<span class="swatch" title="98: #b6ffdb" style="background:#b6ffdb"></span>
<span class="swatch" title="99: #b6ffeb" style="background:#b6ffeb"></span>
<span class="swatch" title="100: #b6ffff" style="background:#b6ffff"></span>
<span class="swatch" title="101: #b6ebff" style="background:#b6ebff"></span>
<span class="swatch" title="102: #b6dbff" style="background:#b6dbff"></span>
<span class="swatch" title="103: #b6c7ff" style="background:#b6c7ff"></span>
<span class="swatch" title="104: #000071" style="background:#000071"></span>
<span class="swatch" title="105: #1c0071" style="background:#1c0071"></span>
<span class="swatch" title="106: #380071" style="background:#380071"></span>
<span class="swatch" title="107: #550071" style="background:#550071"></span>
<span class="swatch" title="108: #710071" style="background:#710071"></span>
<span class="swatch" title="109: #710055" style="background:#710055"></span>
<span class="swatch" title="110: #710038" style="background:#710038"></span>
<span class="swatch" title="111: #71001c" style="background:#71001c"></span>
<span class="swatch" title="112: #710000" style="background:#710000"></span>
<span class="swatch" title="113: #711c00" style="background:#711c00"></span>
<span class="swatch" title="114: #713800" style="background:#713800"></span>
<span class="swatch" title="115: #715500" style="background:#715500"></span>
<span class="swatch" title="116: #717100" style="background:#717100"></span>
<span class="swatch" title="117: #557100" style="background:#557100"></span>
<span class="swatch" title="118: #387100" style="background:#387100"></span>
<span class="swatch" title="119: #1c7100" style="background:#1c7100"></span>
<span class="swatch" title="120: #007100" style="background:#007100"></span>
<span class="swatch" title="121: #00711c" style="background:#00711c"></span>
<span class="swatch" title="122: #007138" style="background:#007138"></span>
<span class="swatch" title="123: #007155" style="background:#007155"></span>
<span class="swatch" title="124: #007171" style="background:#007171"></span>
<span class="swatch" title="125: #005571" style="background:#005571"></span>
<span class="swatch" title="126: #003871" style="background:#003871"></span>
<span class="swatch" title="127: #001c71" style="background:#001c71"></span>
<span class="swatch" title="128: #383871" style="background:#383871"></span>
<span class="swatch" title="129: #453871" style="background:#453871"></span>
<span class="swatch" title="130: #553871" style="background:#553871"></span>
<span class="swatch" title="131: #613871" style="background:#613871"></span>
<span class="swatch" title="132: #713871" style="background:#713871"></span>
<span class="swatch" title="133: #713861" style="background:#713861"></span>
<span class="swatch" title="134: #713855" style="background:#713855"></span>
<span class="swatch" title="135: #713845" style="background:#713845"></span>
<span class="swatch" title="136: #713838" style="background:#713838"></span>
<span class="swatch" title="137: #714538" style="background:#714538"></span>
<span class="swatch" title="138: #715538" style="background:#715538"></span>
<span class="swatch" title="139: #716138" style="background:#716138"></span>
<span class="swatch" title="140: #717138" style="background:#717138"></span>
<span class="swatch" title="141: #617138" style="background:#617138"></span>
<span class="swatch" title="142: #557138" style="background:#557138"></span>
<span class="swatch" title="143: #457138" style="background:#457138"></span>
<span class="swatch" title="144: #387138" style="background:#387138"></span>
<span class="swatch" title="145: #387145" style="background:#387145"></span>
<span class="swatch" title="146: #387155" style="background:#387155"></span>
<span class="swatch" title="147: #387161" style="background:#387161"></span>
<span class="swatch" title="148: #387171" style="background:#387171"></span>
<span class="swatch" title="149: #386171" style="background:#386171"></span>
<span class="swatch" title="150: #385571" style="background:#385571"></span>
<span class="swatch" title="151: #384571" style="background:#384571"></span>
<span class="swatch" title="152: #515171" style="background:#515171"></span>
<span class="swatch" title="153: #595171" style="background:#595171"></span>
<span class="swatch" title="154: #615171" style="background:#615171"></span>
<span class="swatch" title="155: #695171" style="background:#695171"></span>
<span class="swatch" title="156: #715171" style="background:#715171"></span>
<span class="swatch" title="157: #715169" style="background:#715169"></span>
<span class="swatch" title="158: #715161" style="background:#715161"></span>
<span class="swatch" title="159: #715159" style="background:#715159"></span>
<span class="swatch" title="160: #715151" style="background:#715151"></span>
<span class="swatch" title="161: #715951" style="background:#715951"></span>
<span class="swatch" title="162: #716151" style="background:#716151"></span>
<span class="swatch" title="163: #716951" style="background:#716951"></span>
<span class="swatch" title="164: #717151" style="background:#717151"></span>
<span class="swatch" title="165: #697151" style="background:#697151"></span>
<span class="swatch" title="166: #617151" style="background:#617151"></span>
<span class="swatch" title="167: #597151" style="background:#597151"></span>
<span class="swatch" title="168: #517151" style="background:#517151"></span>
<span class="swatch" title="169: #517159" style="background:#517159"></span>
<span class="swatch" title="170: #517161" style="background:#517161"></span>
<span class="swatch" title="171: #517169" style="background:#517169"></span>
<span class="swatch" title="172: #517171" style="background:#517171"></span>
<span class="swatch" title="173: #516971" style="background:#516971"></span>
<span class="swatch" title="174: #516171" style="background:#516171"></span>
<span class="swatch" title="175: #515971" style="background:#515971"></span>
<span class="swatch" title="176: #000041" style="background:#000041"></span>
<span class="swatch" title="177: #100041" style="background:#100041"></span>
<span class="swatch" title="178: #200041" style="background:#200041"></span>
<span class="swatch" title="179: #300041" style="background:#300041"></span>
<span class="swatch" title="180: #410041" style="background:#410041"></span>
<span class="swatch" title="181: #410030" style="background:#410030"></span>
<span class="swatch" title="182: #410020" style="background:#410020"></span>
<span class="swatch" title="183: #410010" style="background:#410010"></span>
<span class="swatch" title="184: #410000" style="background:#410000"></span>
<span class="swatch" title="185: #411000" style="background:#411000"></span>
<span class="swatch" title="186: #412000" style="background:#412000"></span>
<span class="swatch" title="187: #413000" style="background:#413000"></span>
<span class="swatch" title="188: #414100" style="background:#414100"></span>
<span class="swatch" title="189: #304100" style="background:#304100"></span>
<span class="swatch" title="190: #204100" style="background:#204100"></span>
<span class="swatch" title="191: #104100" style="background:#104100"></span>
<span class="swatch" title="192: #004100" style="background:#004100"></span>
<span class="swatch" title="193: #004110" style="background:#004110"></span>
<span class="swatch" title="194: #004120" style="background:#004120"></span>
<span class="swatch" title="195: #004130" style="background:#004130"></span>
<span class="swatch" title="196: #004141" style="background:#004141"></span>
<span class="swatch" title="197: #003041" style="background:#003041"></span>
<span class="swatch" title="198: #002041" style="background:#002041"></span>
<span class="swatch" title="199: #001041" style="background:#001041"></span>
<span class="swatch" title="200: #202041" style="background:#202041"></span>
<span class="swatch" title="201: #282041" style="background:#282041"></span>
<span class="swatch" title="202: #302041" style="background:#302041"></span>
<span class="swatch" title="203: #382041" style="background:#382041"></span>
<span class="swatch" title="204: #412041" style="background:#412041"></span>
<span class="swatch" title="205: #412038" style="background:#412038"></span>
<span class="swatch" title="206: #412030" style="background:#412030"></span>
<span class="swatch" title="207: #412028" style="background:#412028"></span>
<span class="swatch" title="208: #412020" style="background:#412020"></span>
<span class="swatch" title="209: #412820" style="background:#412820"></span>
<span class="swatch" title="210: #413020" style="background:#413020"></span>
<span class="swatch" title="211: #413820" style="background:#413820"></span>
<span class="swatch" title="212: #414120" style="background:#414120"></span>
<span class="swatch" title="213: #384120" style="background:#384120"></span>
<span class="swatch" title="214: #304120" style="background:#304120"></span>
<span class="swatch" title="215: #284120" style="background:#284120"></span>
<span class="swatch" title="216: #204120" style="background:#204120"></span>
<span class="swatch" title="217: #204128" style="background:#204128"></span>
<span class="swatch" title="218: #204130" style="background:#204130"></span>
<span class="swatch" title="219: #204138" style="background:#204138"></span>
<span class="swatch" title="220: #204141" style="background:#204141"></span>
<span class="swatch" title="221: #203841" style="background:#203841"></span>
<span class="swatch" title="222: #203041" style="background:#203041"></span>
<span class="swatch" title="223: #202841" style="background:#202841"></span>
<span class="swatch" title="224: #2c2c41" style="background:#2c2c41"></span>
<span class="swatch" title="225: #302c41" style="background:#302c41"></span>
<span class="swatch" title="226: #342c41" style="background:#342c41"></span>
<span class="swatch" title="227: #3c2c41" style="background:#3c2c41"></span>
<span class="swatch" title="228: #412c41" style="background:#412c41"></span>
<span class="swatch" title="229: #412c3c" style="background:#412c3c"></span>
<span class="swatch" title="230: #412c34" style="background:#412c34"></span>
<span class="swatch" title="231: #412c30" style="background:#412c30"></span>
<span class="swatch" title="232: #412c2c" style="background:#412c2c"></span>
<span class="swatch" title="233: #41302c" style="background:#41302c"></span>
<span class="swatch" title="234: #41342c" style="background:#41342c"></span>
<span class="swatch" title="235: #413c2c" style="background:#413c2c"></span>
<span class="swatch" title="236: #41412c" style="background:#41412c"></span>
<span class="swatch" title="237: #3c412c" style="background:#3c412c"></span>
<span class="swatch" title="238: #34412c" style="background:#34412c"></span>
<span class="swatch" title="239: #30412c" style="background:#30412c"></span>
<span class="swatch" title="240: #2c412c" style="background:#2c412c"></span>
<span class="swatch" title="241: #2c4130" style="background:#2c4130"></span>
<span class="swatch" title="242: #2c4134" style="background:#2c4134"></span>
<span class="swatch" title="243: #2c413c" style="background:#2c413c"></span>
<span class="swatch" title="244: #2c4141" style="background:#2c4141"></span>
<span class="swatch" title="245: #2c3c41" style="background:#2c3c41"></span>
<span class="swatch" title="246: #2c3441" style="background:#2c3441"></span>
<span class="swatch" title="247: #2c3041" style="background:#2c3041"></span>
<span class="swatch" title="248: #000000" style="background:#000000"></span>
<span class="swatch" title="249: #000000" style="background:#000000"></span>
<span class="swatch" title="250: #000000" style="background:#000000"></span>
<span class="swatch" title="251: #000000" style="background:#000000"></span>
<span class="swatch" title="252: #000000" style="background:#000000"></span>
<span class="swatch" title="253: #000000" style="background:#000000"></span>
<span class="swatch" title="254: #000000" style="background:#000000"></span>
<span class="swatch" title="255: #000000" style="background:#000000"></span>
</div>

## Vines Flexible Linear Ramps

`use_palette("vines_flexible_linear_ramps")` — 38 colors

<div class="palette">
<span class="swatch" title="0: #150a1f" style="background:#150a1f"></span>
<span class="swatch" title="1: #280b26" style="background:#280b26"></span>
<span class="swatch" title="2: #361027" style="background:#361027"></span>
<span class="swatch" title="3: #681824" style="background:#681824"></span>
<span class="swatch" title="4: #b42313" style="background:#b42313"></span>
<span class="swatch" title="5: #f4680b" style="background:#f4680b"></span>
<span class="swatch" title="6: #f4c047" style="background:#f4c047"></span>
<span class="swatch" title="7: #fffdf0" style="background:#fffdf0"></span>
<span class="swatch" title="8: #0c1327" style="background:#0c1327"></span>
<span class="swatch" title="9: #03282b" style="background:#03282b"></span>
<span class="swatch" title="10: #09493f" style="background:#09493f"></span>
<span class="swatch" title="11: #118337" style="background:#118337"></span>
<span class="swatch" title="12: #57c52b" style="background:#57c52b"></span>
<span class="swatch" title="13: #b9ed5e" style="background:#b9ed5e"></span>
<span class="swatch" title="14: #1a112e" style="background:#1a112e"></span>
<span class="swatch" title="15: #291945" style="background:#291945"></span>
<span class="swatch" title="16: #5e1c5a" style="background:#5e1c5a"></span>
<span class="swatch" title="17: #8f1767" style="background:#8f1767"></span>
<span class="swatch" title="18: #f45d92" style="background:#f45d92"></span>
<span class="swatch" title="19: #feb58b" style="background:#feb58b"></span>
<span class="swatch" title="20: #0e092f" style="background:#0e092f"></span>
<span class="swatch" title="21: #1b1853" style="background:#1b1853"></span>
<span class="swatch" title="22: #222d81" style="background:#222d81"></span>
<span class="swatch" title="23: #465be7" style="background:#465be7"></span>
<span class="swatch" title="24: #2ac0f2" style="background:#2ac0f2"></span>
<span class="swatch" title="25: #7df2cf" style="background:#7df2cf"></span>
<span class="swatch" title="26: #220c27" style="background:#220c27"></span>
<span class="swatch" title="27: #2f1316" style="background:#2f1316"></span>
<span class="swatch" title="28: #431e1e" style="background:#431e1e"></span>
<span class="swatch" title="29: #74341a" style="background:#74341a"></span>
<span class="swatch" title="30: #af5d23" style="background:#af5d23"></span>
<span class="swatch" title="31: #f8993a" style="background:#f8993a"></span>
<span class="swatch" title="32: #19102e" style="background:#19102e"></span>
<span class="swatch" title="33: #241e44" style="background:#241e44"></span>
<span class="swatch" title="34: #25315e" style="background:#25315e"></span>
<span class="swatch" title="35: #3a5c85" style="background:#3a5c85"></span>
<span class="swatch" title="36: #56a1bf" style="background:#56a1bf"></span>
<span class="swatch" title="37: #97dbd2" style="background:#97dbd2"></span>
</div>

## Vinik24

`use_palette("vinik24")` — 24 colors

<div class="palette">
<span class="swatch" title="0: #000000" style="background:#000000"></span>
<span class="swatch" title="1: #6f6776" style="background:#6f6776"></span>
<span class="swatch" title="2: #9a9a97" style="background:#9a9a97"></span>
<span class="swatch" title="3: #c5ccb8" style="background:#c5ccb8"></span>
<span class="swatch" title="4: #8b5580" style="background:#8b5580"></span>
<span class="swatch" title="5: #c38890" style="background:#c38890"></span>
<span class="swatch" title="6: #a593a5" style="background:#a593a5"></span>
<span class="swatch" title="7: #666092" style="background:#666092"></span>
<span class="swatch" title="8: #9a4f50" style="background:#9a4f50"></span>
<span class="swatch" title="9: #c28d75" style="background:#c28d75"></span>
<span class="swatch" title="10: #7ca1c0" style="background:#7ca1c0"></span>
<span class="swatch" title="11: #416aa3" style="background:#416aa3"></span>
<span class="swatch" title="12: #8d6268" style="background:#8d6268"></span>
<span class="swatch" title="13: #be955c" style="background:#be955c"></span>
<span class="swatch" title="14: #68aca9" style="background:#68aca9"></span>
<span class="swatch" title="15: #387080" style="background:#387080"></span>
<span class="swatch" title="16: #6e6962" style="background:#6e6962"></span>
<span class="swatch" title="17: #93a167" style="background:#93a167"></span>
<span class="swatch" title="18: #6eaa78" style="background:#6eaa78"></span>
<span class="swatch" title="19: #557064" style="background:#557064"></span>
<span class="swatch" title="20: #9d9f7f" style="background:#9d9f7f"></span>
<span class="swatch" title="21: #7e9e99" style="background:#7e9e99"></span>
<span class="swatch" title="22: #5d6872" style="background:#5d6872"></span>
<span class="swatch" title="23: #433455" style="background:#433455"></span>
</div>

## Winter Wonderland

`use_palette("winter_wonderland")` — 8 colors

<div class="palette">
<span class="swatch" title="0: #20284e" style="background:#20284e"></span>
<span class="swatch" title="1: #2c4a78" style="background:#2c4a78"></span>
<span class="swatch" title="2: #3875a1" style="background:#3875a1"></span>
<span class="swatch" title="3: #8bcadd" style="background:#8bcadd"></span>
<span class="swatch" title="4: #ffffff" style="background:#ffffff"></span>
<span class="swatch" title="5: #d6e1e9" style="background:#d6e1e9"></span>
<span class="swatch" title="6: #a7bcc9" style="background:#a7bcc9"></span>
<span class="swatch" title="7: #738d9d" style="background:#738d9d"></span>
</div>

## Zughy 32

`use_palette("zughy_32")` — 32 colors

<div class="palette">
<span class="swatch" title="0: #472d3c" style="background:#472d3c"></span>
<span class="swatch" title="1: #5e3643" style="background:#5e3643"></span>
<span class="swatch" title="2: #7a444a" style="background:#7a444a"></span>
<span class="swatch" title="3: #a05b53" style="background:#a05b53"></span>
<span class="swatch" title="4: #bf7958" style="background:#bf7958"></span>
<span class="swatch" title="5: #eea160" style="background:#eea160"></span>
<span class="swatch" title="6: #f4cca1" style="background:#f4cca1"></span>
<span class="swatch" title="7: #b6d53c" style="background:#b6d53c"></span>
<span class="swatch" title="8: #71aa34" style="background:#71aa34"></span>
<span class="swatch" title="9: #397b44" style="background:#397b44"></span>
<span class="swatch" title="10: #3c5956" style="background:#3c5956"></span>
<span class="swatch" title="11: #302c2e" style="background:#302c2e"></span>
<span class="swatch" title="12: #5a5353" style="background:#5a5353"></span>
<span class="swatch" title="13: #7d7071" style="background:#7d7071"></span>
<span class="swatch" title="14: #a0938e" style="background:#a0938e"></span>
<span class="swatch" title="15: #cfc6b8" style="background:#cfc6b8"></span>
<span class="swatch" title="16: #dff6f5" style="background:#dff6f5"></span>
<span class="swatch" title="17: #8aebf1" style="background:#8aebf1"></span>
<span class="swatch" title="18: #28ccdf" style="background:#28ccdf"></span>
<span class="swatch" title="19: #3978a8" style="background:#3978a8"></span>
<span class="swatch" title="20: #394778" style="background:#394778"></span>
<span class="swatch" title="21: #39314b" style="background:#39314b"></span>
<span class="swatch" title="22: #564064" style="background:#564064"></span>
<span class="swatch" title="23: #8e478c" style="background:#8e478c"></span>
<span class="swatch" title="24: #cd6093" style="background:#cd6093"></span>
<span class="swatch" title="25: #ffaeb6" style="background:#ffaeb6"></span>
<span class="swatch" title="26: #f4b41b" style="background:#f4b41b"></span>
<span class="swatch" title="27: #f47e1b" style="background:#f47e1b"></span>
<span class="swatch" title="28: #e6482e" style="background:#e6482e"></span>
<span class="swatch" title="29: #a93b3b" style="background:#a93b3b"></span>
<span class="swatch" title="30: #827094" style="background:#827094"></span>
<span class="swatch" title="31: #4f546b" style="background:#4f546b"></span>
</div>

<style>
.palette { display:flex; flex-wrap:wrap; gap:3px; margin:.5rem 0 1.5rem; }
.swatch { width:22px; height:22px; border-radius:4px; border:1px solid rgba(127,127,127,.25); }
</style>
