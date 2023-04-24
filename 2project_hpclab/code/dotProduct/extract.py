#!/usr/bin/python3

import re, string
import sys
from pathlib import Path

print('n,p,t,name,time')

for file in sys.argv[1:]:
    path = Path(file)
    f = open(path,"r")
    text = f.read()
    n, p, t = path.stem.split('-')

    patterns = [
        ['serial', 'Serial execution time = ([\d.e+]+) sec'],
        ['reduction', 'time using reduction method = ([\d.e+]+) sec'],
        ['critical', 'time using critical method ([\d.e+]+) sec'],
    ]

    for name, pattern in patterns:
        m = re.search(
            pattern,
            text,
            re.IGNORECASE
        )
        print(n, p, t, name, m.group(1), sep=',')
