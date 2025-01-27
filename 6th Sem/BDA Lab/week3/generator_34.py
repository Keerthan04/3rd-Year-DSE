import random
import string

# Function to generate a random key (e.g., "A", "B", "C", etc.)
def random_key():
    return random.choice(string.ascii_uppercase)  # Random key from A-Z

# Function to generate a random value (numeric value)
def random_value():
    return round(random.uniform(50, 100), 1)  # Random value between 50 and 100 (inclusive)

# Number of records to generate
num_records = 10000  # Adjust as needed

# Open a file to save the generated dataset
with open("generated_data.txt", "w") as file:
    # Write the header
    file.write("Key | Value\n")
    file.write("----|-------\n")
    
    # Generate random key-value pairs
    for _ in range(num_records):
        key = random_key()
        value = random_value()
        
        # Write the key and value to the file
        file.write(f"{key} | {value}\n")

print(f"Dataset with {num_records} records has been saved to 'generated_data.txt'")

