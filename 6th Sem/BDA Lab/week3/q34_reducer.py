import sys

# Initialize variables for sum and count
current_key = None
sum_values = 0
count = 0

# Read each line from standard input (mapper output)
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Skip empty lines
    if not line:
        continue

    # Parse the input from the mapper (expected format: 'key\tvalue')
    key, value = line.split('\t')

    # Convert value to an integer
    value = float(value)

    # If the current key is the same as the last one, accumulate the sum and count
    if current_key == key:
        sum_values += value
        count += 1
    else:
        # If we have a key (not the first line), output the average for the previous key
        if current_key:
            average = sum_values / count
            print(f"{current_key}\t{average}")

        # Reset for the new key
        current_key = key
        sum_values = value
        count = 1

# Output the average for the last key
if current_key:
    average = sum_values / count
    print(f"{current_key}\t{average}")

