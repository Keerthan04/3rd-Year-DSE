import sys

# Initialize variables
current_char = None
current_count = 0

# Read each line from standard input (mapper output)
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Parse the input from the mapper (it's expected to be 'char\tcount')
    char, count = line.split('\t')

    # Convert the count to an integer
    count = int(count)

    # If the current character is the same as the last one, accumulate the count
    if current_char == char:
        current_count += count
    else:
        if current_char:
            print('%s\t%s' % (current_char, current_count))

        current_char = char
        current_count = count

if current_char:
    print('%s\t%s' % (current_char, current_count))
