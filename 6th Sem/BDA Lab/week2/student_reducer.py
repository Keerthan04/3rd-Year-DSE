#!/usr/bin/python3
import sys

def main():
	raw = sys.stdin
	for line in raw:
		student_name,roll_marks = line.strip().split(",")
		roll,marks = roll_marks.split("\t")
		print(f"{student_name}\t{roll}\t{marks}")
main()
