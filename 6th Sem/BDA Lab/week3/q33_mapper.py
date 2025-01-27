import sys

# Read each line from standard input
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Split the line into name and score
    name, score = line.split(" | ")

    # Output the constant key and score as key-value pair
    print(f"{name}\t{score}")

