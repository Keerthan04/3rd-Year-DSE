#!/usr/bin/env python3
import sys
from collections import defaultdict

# Default dictionary to collect all the values for each courseId
coursedict = defaultdict(list)

for line in sys.stdin:
    line = line.strip()
    
    # Splitting the input by comma and tab
    courseId, values = line.split(',')
    coursedict[courseId].append(values.split('\t'))

# Outputting the result by iterating through all courses
for courseId, values in coursedict.items():
    course_info = values[0]  # First element will be course information (name, semester)
    course_name, semester = course_info[0], course_info[1]
    
    # Print the course details along with each student enrolled in the course
    for student_info in values[1:]:  # Skipping the course info, since it's already added
        student_id, student_name = student_info[0], student_info[1]
        print(f"{student_id},{student_name},{course_name},{semester}")

