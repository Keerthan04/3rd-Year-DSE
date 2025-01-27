import sys

# Read each line from standard input
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Skip header line if present
    if line.startswith("Date"):
        continue

    # Split the line by delimiter ('|')
    date, temperature = line.split("|")

    # Extract the year from the date (format is YYYY-MM-DD)
    year = date.split("-")[0]

    # Output the year and temperature as key-value pair
    print(f"{year}\t{temperature}")
			
