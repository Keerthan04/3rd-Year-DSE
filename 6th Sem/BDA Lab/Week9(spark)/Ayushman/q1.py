from pyspark import SparkContext
import re

sc = SparkContext("local", "server log")

# HDFS Paths
hdfs_input_path = "hdfs://localhost:9000/user/220968002/week9/q1.txt"
hdfs_output_path = "hdfs://localhost:9000/user/220968002/week9/out1/"

# Read log file from HDFS
rdd = sc.textFile(hdfs_input_path)

# Extract HTTP status codes and count occurrences
status_codes_and_occurrences = (
    rdd.map(lambda line: re.findall(r'"\s(\d{3})\s', line))  # Extract status code
       .filter(lambda x: len(x) > 0)  # Remove empty extractions
       .map(lambda x: (x[0], 1))  # Convert to key-value pairs
       .reduceByKey(lambda a, b: a + b)  # Count occurrences
)

# Extract most common IP addresses
ip_counts = (
    rdd.map(lambda line: re.findall(r'^(\d+\.\d+\.\d+\.\d+)', line))  # Extract IPs
       .filter(lambda x: len(x) > 0)
       .map(lambda x: (x[0], 1))
       .reduceByKey(lambda a, b: a + b)
)

# Filter out error logs (4xx and 5xx)
error_logs_count = (
    status_codes_and_occurrences
    .filter(lambda x: x[0].startswith("4") or x[0].startswith("5"))  # HTTP 4xx, 5xx
)

# Save results to HDFS
status_codes_and_occurrences.saveAsTextFile(hdfs_output_path + "status_codes")
ip_counts.saveAsTextFile(hdfs_output_path + "ip_counts")
error_logs_count.saveAsTextFile(hdfs_output_path + "error_logs")

