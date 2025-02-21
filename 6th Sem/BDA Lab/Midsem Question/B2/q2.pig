customers = LOAD '/user/keerthan/customers.txt' USING PigStorage(',') AS (customer_id:int,name:chararray,city:chararray,plan_type:chararray);
filtered_customers = FILTER customers BY plan_type=='Premium';
DUMP filtered_customers;