#!/bin/bash

for f in *; do
	awk -F, ' FNR>1 { print sprintf("%d,%d,%.2f,%.2f,%d,%d,%d,%.5f,%d,%.5f", $1,$4,$5,$7,$10,$11,$61,$98,$101,$102); }' $f > ${f%.*}.txt;
done