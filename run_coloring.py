#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2019 zach <zach@zach-blade>
#
# Distributed under terms of the MIT license.

"""
Runs graph coloring on all input files
"""

import sys, os
import pexpect

infiles = [x for x in os.listdir('instances') if (x.startswith('color') and x.endswith('.input'))]
infiles = sorted(infiles, key=lambda x: int(x[5:-6].split('-')[0]))
#infiles = [x for x in infiles if int(x[5:-6].split('-')[0]) > 24]

for f in infiles:
    print(f)
    p = pexpect.spawnu('./p2b.out')
    p.expect('Enter filename')
    p.sendline('instances/'+f)
    p.expect('Enter time to run')
    t = 10
    try:
        t = int(sys.argv[1])
    except:
        pass
    p.sendline(str(t))

    p.expect('done', timeout=t+10)
    with open('output/'+f[:-6]+'.output', 'w+') as of:
        of.write(p.before)
