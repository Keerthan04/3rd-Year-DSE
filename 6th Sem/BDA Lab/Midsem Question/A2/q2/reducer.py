#!usr/bin/python3
import sys
from collections import defaultdict

category_revenue_dict = defaultdict(int)

for line in sys.stdin:
    line = line.strip()
    category, rev_details = line.split(",")
    units_sold, price_per_unit = rev_details.split("\t")
    revenue = int(units_sold) * float(price_per_unit)
    category_revenue_dict[category] += revenue

for category, revenue in category_revenue_dict.items():
    print(f"{category},{revenue}")