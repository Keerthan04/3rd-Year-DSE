from pyspark.sql import SparkSession
from pyspark.sql.functions import col, expr, max

# Create SparkSession
spark = SparkSession.builder.appName("Sales Data Processing").getOrCreate()

# Load CSV file into DataFrame
df = spark.read.option("header", "true").option("inferSchema", "true").csv("hdfs://localhost:9000/user/220968118/lab9/sales.csv")

# Compute total revenue per product (Price * Quantity)
df_with_revenue = df.withColumn("Revenue", col("Price") * col("Quantity"))
df_with_revenue.show()

# Find highest-selling product by revenue
max_revenue = df_with_revenue.agg(max("Revenue")).collect()[0][0]
highest_selling = df_with_revenue.filter(col("Revenue") == max_revenue)
print("Highest Selling Product:")
highest_selling.show()

# Filter transactions where total sales > 500
filtered_sales = df_with_revenue.filter(col("Revenue") > 500)
print("Sales with revenue > $500:")
filtered_sales.show()

# Group by category and compute total revenue per category
category_revenue = df_with_revenue.groupBy("Category").sum("Revenue").withColumnRenamed("sum(Revenue)", "Total_Revenue")
category_revenue.show()

# Save all transformed DataFrames to HDFS
df_with_revenue.write.mode("overwrite").option("header", "true").csv("hdfs://localhost:9000/user/220968118/lab9/with_revenue")
filtered_sales.write.mode("overwrite").option("header", "true").csv("hdfs://localhost:9000/user/220968118/lab9/sales_above_500")
category_revenue.write.mode("overwrite").option("header", "true").csv("hdfs://localhost:9000/user/220968118/lab9/category_revenue")

