from pyspark.sql import SparkSession

# Create SparkSession
spark = SparkSession.builder \
    .appName("JSON Data Processing") \
    .getOrCreate()

# Step 1: Read JSON file from HDFS into DataFrame
df = spark.read.json("hdfs://localhost:9000/user/220968118/lab9/users3.json")

# Step 2: Select specific fields
df.select("name", "age").show()

# Step 3: Filter records where age > 30
filtered_df = df.filter(df.age > 30)
filtered_df.show()

# Step 4: Group by city and count users
grouped_df = df.groupBy("city").count()
grouped_df.show()

# Step 5: Save filtered data as new JSON file to HDFS
filtered_df.write.mode("overwrite").json("hdfs://localhost:9000/user/220968118/lab9/filtered_users3")

# Save grouped data as JSON to HDFS
grouped_df.write.mode("overwrite").json("hdfs://localhost:9000/user/220968118/lab9/grouped_by_city3")

