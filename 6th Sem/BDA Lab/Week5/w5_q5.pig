sales_data = LOAD '/home/bdalab/Desktop/220968100/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);
cust_data = LOAD '/home/bdalab/Desktop/220968100/customer_week5.csv' USING PigStorage(',') AS (order_id:int, customer:chararray, city:chararray);
joined_data = join sales_data by order_id,cust_data by order_id;
DUMP joined_data;
