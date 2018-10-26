#!/usr/bin/env python

import sys
import re
import math
import numpy as np
import scipy.stats as sp

def inverse_mapping(f):
    return f.__class__(map(reversed, f.items()))

max_frame = int(sys.argv[2])
n_lins = int(sys.argv[3])
field = int(sys.argv[4])
# when is the drug introduced in the timelapse?
tDrug = int(sys.argv[5])

cumul = [[0 for i in range(max_frame)] for j in range(n_lins)]
edge = [0 for k in range(n_lins)]
pro_index = []
mother_dict = {'0':[0]}
idx_dict = {'-1':0}

progenitor_idx = -1
pro_ID = 0

with open(sys.argv[1]) as f:
	next(f)
	for line in f:
		line = str.split(line)
		birthframe = int(line[4])
		if(line[8]=="nan"):
			lifespan = float("inf")
		else: lifespan = int(line[8])

		if(tDrug - birthframe > lifespan):
			continue

		ID = int(line[3])
		progenitor = int(line[6])
		mother = int(line[5])
		dist = float(line[15])

		#print(line)

		#if mother is not in progenitor list
		if(mother not in pro_index):
			#then that cell is considered a new progenitor
			# the new progenitor's ID is registered, and it is added to the map of mothers for that lineage
			pro_index.append(ID)
			temp = str(ID)

			mother_dict[temp] = [ID]
			progenitor_idx += 1
			idx_dict[temp] = progenitor_idx
			edge[progenitor_idx] = dist
			cumul[progenitor_idx][birthframe] += 1
		else:
			#find the lineage where it belongs
			# and add to mother dict
			for k,v in mother_dict.items():
				if(mother not in v):
					continue
				else:
					#print(k,v)
					pro_ID = k

			#pro_ID = mother_dict.keys()[mother_dict.values().index(mother)]

			temp = str(pro_ID)
			mother_dict[temp].append(ID)
			pro_index.append(ID)
			#print(mother_dict[temp])
			cumul[idx_dict[pro_ID]][birthframe] += 0.5


		# #if progenitor is new, find index
		# if(progenitor not in index):
		# 	index.append(progenitor)
		# 	progenitor_idx += 1
		# 	cumul[progenitor_idx][birthframe] += 1
		# else:
		# 	cumul[progenitor_idx][birthframe] += 0.5

print("Field" + "\t" + "Lineage" + "\t" + "Frame" + "\t" + "Births" + "\t" + "DistToEdge")
for lin in range(n_lins):
	for frame in range(max_frame):
		print(str(field) + "\t" + str(lin) + "\t" + str(frame) + "\t" + str(cumul[lin][frame]) + "\t" + str(edge[lin]))
