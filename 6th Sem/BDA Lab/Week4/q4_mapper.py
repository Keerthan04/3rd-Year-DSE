#!/user/bin/env python3
import sys

for line in sys.stdin:
	line = line.strip()
	docId,words_sentance = line.split('\t')
	words = words_sentance.split()
	for word in words:
		print(f"{word},{docId}")
	
