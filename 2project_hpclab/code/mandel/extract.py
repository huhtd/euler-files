#!/usr/bin/python3

import re, string
import sys
from pathlib import Path

print('i,p,t,key,value')

for file in sys.argv[1:]:
    path = Path(file)
    f = open(path,"r")
    text = f.read()
    i, p, t = path.stem.split('-')

    patterns = [
        ['time', 'Total time:[\s]*([\d.e+]+)'],
        ['pixelsize', 'Image size:[\s]*[\d]* x [\d]* = ([\d.e+]+)'],
        ['iterationnumber', 'Total number of iterations:[\s]*([\d.e+]+)'],
        ['timeperpixel', 'Avg. time per pixel:[\s]*([\d.e+]+)'],
        ['timeperiteration', 'Avg. time per iteration:[\s]*([\d.e+]+)'],
        ['iterationspersecond', 'Iterations/second:[\s]*([\d.e+]+)'],
        ['MFlops/s', 'MFlop/s:[\s]*([\d.e+]+)']
    ]

    for key, pattern in patterns:
        m = re.search(
            pattern,
            text,
            re.IGNORECASE
        )
        print(i, p , t, key, m.group(1), sep=',')