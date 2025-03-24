from pyspark import SparkContext

sc = SparkContext("local", "Log Analyzer")

log_rdd = sc.textFile("hdfs://localhost:9000/user/220968118/lab9/input1.txt")

# Extract status codes safely
def extract_status_code(line):
    try:
        parts = line.split('"')
        if len(parts) > 2:
            return parts[2].strip().split(" ")[0]
    except:
        pass
    return "UNKNOWN"

status_codes = log_rdd.map(extract_status_code)
status_counts = status_codes.map(lambda code: (code, 1)).reduceByKey(lambda a, b: a + b)

# IP address counts
ip_counts = log_rdd.map(lambda line: line.split(" ")[0]) \
                   .map(lambda ip: (ip, 1)) \
                   .reduceByKey(lambda a, b: a + b) \
                   .sortBy(lambda x: -x[1])

# Error logs filtering
def is_error(line):
    try:
        parts = line.split('"')
        if len(parts) > 2:
            status = int(parts[2].strip().split(" ")[0])
            return 400 <= status < 600
    except:
        return False
    return False

error_logs = log_rdd.filter(is_error)
error_count = error_logs.count()

# Save outputs to HDFS
status_counts.saveAsTextFile("hdfs://localhost:9000/user/220968118/lab9/status_counts")
ip_counts.saveAsTextFile("hdfs://localhost:9000/user/220968118/lab9/ip_counts")
error_logs.saveAsTextFile("hdfs://localhost:9000/user/220968118/lab9/error_logs")

# Print results
print("\nStatus Code Counts:")
print(status_counts.collect())

print("\nTop IP Addresses:")
print(ip_counts.take(5))

print(f"\nTotal Error Logs (4xx/5xx): {error_count}")

