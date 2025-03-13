sales_data = LOAD '/user/220968100/lab5/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);
DUMP sales_data;
high_amount = filter sales_data by amount>50000;
store high_amount into '/user/220968100/lab5/out1' using PigStorage(',');
