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

infiles = [x for x in os.listdir('instances') if x.startswith('knapsack')]

for f in infiles:
    print(f)
    p = pexpect.spawnu('./p1a.out')
    p.expect('Enter filename')
    p.sendline('instances/'+f)
    p.interact()
    # Give the program 11 minutes to give a result (timer should kill it at minute 10)
    #p.expect("done")
    #print(p.before)
    #p.read()
    #p.close()
