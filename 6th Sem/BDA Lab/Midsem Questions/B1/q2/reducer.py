#!usr/bin/python3
import sys
from collections import defaultdict
call_id_dict = defaultdict(int)

for line in sys.stdin:
	line = line.strip()
	call_id,duration = line.split(',')
	if call_id_dict[call_id]:
		call_id_dict[call_id]+=int(duration)
	else:
		call_id_dict[call_id]=int(duration)

longest = dict(sorted(call_id_dict.items(),key = lambda x: x[1],reverse =True))


count = 0;
for call_id,duration in longest.items():
	if count ==5: break
	print(f"{call_id}\t{duration}")
	count+=1
