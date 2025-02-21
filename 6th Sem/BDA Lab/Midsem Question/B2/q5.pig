calls = LOAD '/user/keerthan/calls.txt' USING PigStorage(',') 
AS (caller_id:int,receiver_id:int,duration:int,timestamp:chararray,city:chararray);

grouped_data = GROUP calls BY city;

filtered_data = FOREACH grouped_data GENERATE group AS city, SUM(calls.duration) AS total_duration;

highest_data = ORDER filtered_data BY total_duration DESC;

top_data = LIMIT highest_data 1;

DUMP top_data;
