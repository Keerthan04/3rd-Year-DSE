#!/usr/bin/python3
import sys

def main():
	for line in sys.stdin:
		line = line.strip()
		matrix,posi,posj,value = line.split(",")
		print(f"{matrix}\t{posi}\t{posj},{value}")

main()
