#!/usr/bin/env python

import sys
import re
import math
import numpy as np
import scipy.stats as sp

max_frame = int(sys.argv[2])
n_lins = int(sys.argv[3])
field = int(sys.argv[4])

cumul = [[0 for i in range(max_frame)] for j in range(n_lins)]
index = []

progenitor_idx = -1

with open(sys.argv[1]) as f:
	next(f)
	for line in f:
		line = str.split(line)
		birthframe = int(line[3])
		progenitor = int(line[5])
		#if progenitor is new, find index
		if(progenitor not in index):
			index.append(progenitor)
			progenitor_idx += 1
			cumul[progenitor_idx][birthframe] += 1
		else:
			cumul[progenitor_idx][birthframe] += 0.5

#print("Lineage" + "\t" + "Frame" + "\t" + "Births")
for lin in range(n_lins):
	for frame in range(max_frame):
		print(str(field) + "\t" + str(lin) + "\t" + str(frame) + "\t" + str(cumul[lin][frame]))
