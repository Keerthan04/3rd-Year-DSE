#!/user/bin/env python3
import sys

for line in sys.stdin:
	line = line.strip()
	if line[0] == 'S':
		studentId,name,courseId = line.split(',')
		print(f"{courseId},{studentId}\t{name}")
		
	else:
		courseId,cname,sem = line.split(',')
		print(f"{courseId},{cname}\t{sem}")
