#!/bin/bash

CSV=$1

awk -F, ' FNR>1 { print sprintf("%d,%d,%.2f,%d,%d,%.5f", $1,$4,$7,$61,$101,$102); }' $CSV > csv.txt