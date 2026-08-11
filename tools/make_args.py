#!/usr/bin/env python3
import json
import sys

# usage: make_args.py OUTPUT [arg ...]
output = sys.argv[1]
args = sys.argv[2:]
with open(output, "w", encoding="utf-8") as f:
    f.write("window.PIXELRAM_ARGS = ")
    json.dump(args, f)
    f.write(";\n")
