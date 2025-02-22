#!usr/bin/python3
import sys
from collections import defaultdict
product_dict = defaultdict(list)

for line in sys.stdin:
    line = line.strip()
    units_sold,product_details = line.split(",")
    product_name,product_id = product_details.split("\t")
    product_dict[int(units_sold)].append((product_name,product_id))

new_dict = sorted(product_dict.items(),key=lambda x: x[0],reverse=True)

count = 0
for units_sold, products in new_dict:
    for product_name, product_id in products:
        if count == 3:  # Stop after 3 products
            break
        print(f"{units_sold}\t{product_name}\t{product_id}")
        count += 1
    if count == 3:  # Stop looping if 3 products are printed
        break