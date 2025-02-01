#!/usr/bin/env python3
import sys

for line in sys.stdin:
	line = line.strip()
	
	fields = line.split(',')
	
	if len(fields) == 4:
		employee_id,department,name,salary = fields
		
		print(f"{department}\t{salary}\t{employee_id},{name}")
