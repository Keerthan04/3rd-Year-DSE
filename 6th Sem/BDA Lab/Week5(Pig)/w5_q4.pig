sales_data = LOAD '/home/bdalab/Desktop/220968100/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);
DUMP sales_data;
grouped_data = group sales_data by category;
s_sales = foreach grouped_data generate group as category, SUM(sales_data.amount) as sum_sales;
dump s_sales;

