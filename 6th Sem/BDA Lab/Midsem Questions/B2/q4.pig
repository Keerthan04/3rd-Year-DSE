calls = LOAD '/user/keerthan/calls.txt' USING PigStorage(',') AS (caller_id:int,receiver_id:int,duration:int,timestamp:chararray,city:chararray);
customers = LOAD '/user/keerthan/customers.txt' USING PigStorage(',') AS (customer_id:int,name:chararray,city:chararray,plan_type:chararray);
joined_data = JOIN calls BY caller_id,customers BY customer_id;
DUMP joined_data;