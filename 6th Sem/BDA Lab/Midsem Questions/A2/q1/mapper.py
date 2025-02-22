#!usr/bin/python3

'''
Q)Write a map reducer code to get the top three soled product name and id(3m,5m)
'''
import sys

for line in sys.stdin:
    line = line.strip()
    product_id,product_name,category,units_sold,price_per_unit = line.split(",")
    print(f"{units_sold},{product_name}\t{product_id}")