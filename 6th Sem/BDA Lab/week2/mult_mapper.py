#!/usr/bin/python3
import sys

def main():
	raw = sys.stdin
	
	for line in raw:
		line = line.strip()
		mat,posi,posj,val = line.split(",")
		print(f"{mat}\t{posi},{posj}\t{val}")
main()
