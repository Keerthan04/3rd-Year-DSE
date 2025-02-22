calls = LOAD '/user/keerthan/calls.txt' USING PigStorage(',') AS (caller_id:int,receiver_id:int,duration:int,timestamp:chararray,city:chararray);
DUMP calls;
customers = LOAD '/user/keerthan/customers.txt' USING PigStorage(',') AS (customer_id:int,name:chararray,city:chararray,plan_type:chararray);
DUMP customers;