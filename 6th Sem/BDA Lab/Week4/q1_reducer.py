#!/usr/bin/env python3
import sys
from collections import defaultdict

department_data = defaultdict(list)

for line in sys.stdin:
	line = line.strip()
	try:
		department,salary,details = line.split('\t',2)
		salary = int(salary)
		department_data[department].append((salary,details))
	except ValueError:
		continue
		
for department,records in department_data.items():
	sorted_records = sorted(records, key = lambda x: x[0])
	for salary,details in sorted_records:
		print(f"{department},{details}")
