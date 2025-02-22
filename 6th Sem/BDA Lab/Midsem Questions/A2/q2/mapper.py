#!usr/bin/python3
'''
Q)Write a map reducer code to get the total revenue generates by each category(3m,5m)
The input file was csv file
'''
import sys

for line in sys.stdin:
    line = line.strip()
    product_id,product_name,category,units_sold,price_per_unit = line.split(",")
    print(f"{category},{units_sold}\t{price_per_unit}")