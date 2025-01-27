#!/usr/bin/python3
import sys

def main():
	raw = sys.stdin
	
	for line in raw:
		matrix,pos,value = line.strip().split("\t")
		print(f"i:{pos[-1]}\tj:{pos[0]}\tvalue:{value}")#just interchange the i and j
#else store in matrix then tranpose that and print ele wise
#also change input text to have data of only one matrix
main()
