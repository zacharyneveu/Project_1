#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2019 zach <zach@zach-blade>
#
# Distributed under terms of the MIT license.

"""
Runs knapsack on all input files
"""

import sys, os
import pexpect

infiles = [x for x in os.listdir('instances') if x.startswith('knapsack') and x.endswith('.input')]
infiles = sorted(infiles, key=lambda x: int(x[8:-6]))

for f in infiles:
    print(f)
    p = pexpect.spawnu('./p1a.out')
    p.expect('Enter filename')
    p.sendline('instances/'+f)
    p.expect('Enter time to run')
    try:
        p.sendline(sys.argv[1])
    except:
        p.sendline('10')

    p.expect('done')
    with open('output/'+f[:-6]+'.output', 'w+') as of:
        of.write(p.before)
