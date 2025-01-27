import sys

# Initialize variables
current_year = None
max_temperature = -float('inf')  # Start with a very low value to ensure any temperature is greater

# Read each line from standard input (mapper output)
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Skip empty lines or header
    if not line:
        continue

    # Parse the input from the mapper (expected format: 'year\ttemperature')
    year, temperature = line.split('\t')

    # Convert temperature to a float
    temperature = float(temperature)

    # If we are still processing the same year, update the max temperature
    if current_year == year:
        if temperature > max_temperature:
            max_temperature = temperature
    else:
        # If we have a previous year, output its maximum temperature
        if current_year:
            print(f"{current_year}\t{max_temperature}")

        # Update the current year and reset max temperature
        current_year = year
        max_temperature = temperature

# Output the last year and its maximum temperature
if current_year:
    print(f"{current_year}\t{max_temperature}")

