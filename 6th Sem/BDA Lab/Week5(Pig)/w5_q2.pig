sales_data = LOAD '/home/bdalab/Desktop/220968100/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);
DUMP sales_data;
high_amount = filter sales_data by amount>50000;
dump high_amount;
