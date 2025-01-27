#!/usr/bin/python3
import sys

def main():
	raw = sys.stdin
	d = {}

	for line in raw:
		a, value = line.strip().split(",")
		matrix, posi, posj = a.split("\t")
		value = int(value)
		if (posi, posj) not in d:
			d[(posi, posj)] = value
		else:
			d[(posi, posj)] = (d[(posi, posj)] + value, d[(posi, posj)]-value)#to store addition and subtraction
    
	for k, v in d.items():
		print(f"{k[0]}\t{k[1]}\tadd:{v[0]}\tsub:{v[1]}")

main()

