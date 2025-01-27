import sys
for line in sys.stdin:
	line = line.strip()
	line = line.split()
	for word in line:
		for char in word:
			print ('%s\t%s' % (char, 1))
