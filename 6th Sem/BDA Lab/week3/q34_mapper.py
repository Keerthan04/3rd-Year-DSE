import sys

# Read each line from standard input
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Skip header line if present
    if line.startswith("Key"):
        continue

    # Split the line into key and value
    key, value = line.split("|")

    # Output the key and value as key-value pair
    print(f"{key}\t{value}")

