#!/usr/bin/python3

import sys

current_word = None
current_count = 0

# Iterate through the input lines from the mapper
for line in sys.stdin:
    # Remove leading and trailing whitespaces
    line = line.strip()

    # Parse the input we got from the mapper (word, count)
    word, count = line.split('\t')
    count = int(count)

    # If the word is the same as the previous word, accumulate the count
    if current_word == word:
        current_count += count
    else:
        # If we have a previous word, print it and its total count
        if current_word:
            print(f'{current_word}\t{current_count}')
        
        # Update the current word and reset the count
        current_word = word
        current_count = count

# Print the last word and its count (needed as the last word won't be printed in the loop)
if current_word:
    print(f'{current_word}\t{current_count}')

