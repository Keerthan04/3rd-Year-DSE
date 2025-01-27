#!/usr/bin/python3
import sys

def main():
	raw = sys.stdin
	for line in raw:
		roll,student_name,marks = line.strip().split(",")
		print(f"{student_name},{roll}\t{marks}")

main()	
