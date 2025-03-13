sales_data = LOAD '/home/bdalab/Desktop/220968100/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);
sorted_sales = ORDER sales_data BY amount DESC;
top_3_expensive_products = LIMIT sorted_sales 3;
DUMP top_3_expensive_products;
