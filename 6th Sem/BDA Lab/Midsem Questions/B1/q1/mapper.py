#!usr/bin/python3
import sys

for line in sys.stdin:
	line = line.strip()
	if line[0] =='C':
		continue
	call_id,caller_id,reciever_id,duration,call_type,date = line.split(',')
	print(f"{call_type},{1}")
