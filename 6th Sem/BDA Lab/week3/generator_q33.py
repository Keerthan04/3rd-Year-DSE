import random
import string

# Function to generate a random student name
def random_name(length=5):
    return ''.join(random.choices(string.ascii_uppercase, k=length))

# Function to generate random score between 0 and 100
def random_score():
    return round(random.uniform(50, 100), 1)

# Number of students in the dataset
num_students = 100  # Adjust as needed

# Open a file to save the generated dataset
with open("student_scores.txt", "w") as file:
    # Write the header
    file.write("StudentName | Score\n")
    file.write("-------------|-------\n")
    
    # Generate random student names and scores
    for _ in range(num_students):
        name = random_name()
        score = random_score()
        
        # Write the student name and score to the file
        file.write(f"{name} | {score}\n")

print(f"Dataset with {num_students} students has been saved to 'student_scores.txt'")

