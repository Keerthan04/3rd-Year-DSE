import random
from datetime import datetime, timedelta

# Start and end dates
start_date = datetime(1947, 1, 1)
end_date = datetime(2047, 12, 31)

# Open a file to save the data
with open("temperature_readings_2016_2018.txt", "w") as file:
    # Write the header
    file.write("Date        | Temperature (°C)\n")
    file.write("------------|------------------\n")

    # Loop through each day
    current_date = start_date
    while current_date <= end_date:
        # Generate a random temperature between -10 and 35 °C (reasonable range)
        temperature = round(random.uniform(-10.0, 35.0), 1)
        
        # Write the date and temperature to the file
        file.write(f"{current_date.strftime('%Y-%m-%d')} | {temperature}\n")
        
        # Move to the next day
        current_date += timedelta(days=1)

print("Temperature data has been saved to 'temperature_readings_2016_2018.txt'")
