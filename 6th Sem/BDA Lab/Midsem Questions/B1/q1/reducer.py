#!usr/bin/python3
import sys
from collections import defaultdict
call_type_dict = defaultdict(int)

for line in sys.stdin:
	line = line.strip()
	call_type,count = line.split(',')
	if call_type_dict[call_type]:
		call_type_dict[call_type]+=int(count)
	else:
		call_type_dict[call_type]=int(count)

for call_type,count in call_type_dict.items():
	print(f"{call_type}\t{count}")
	

	
