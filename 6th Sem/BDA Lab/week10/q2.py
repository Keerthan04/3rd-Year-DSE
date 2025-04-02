import matplotlib.pyplot as plt
import pandas as pd
from pyspark.sql import SparkSession
from pyspark.ml.feature import StringIndexer, VectorAssembler, MinMaxScaler
from pyspark.ml.classification import LogisticRegression
from pyspark.ml.evaluation import BinaryClassificationEvaluator
from pyspark.sql.functions import col, avg, count

# Initialize Spark Session
spark = SparkSession.builder.appName("EmployeePromotionPrediction").getOrCreate()

# a) Load and preprocess employee data stored in HDFS
df = spark.read.csv("hdfs://localhost:9000/user/220968002/week10/employee_promotion.csv", header=True, inferSchema=True)

# Basic Data Inspection
print("Dataset Sample:")
df.show(5)
print("Dataset Schema:")
df.printSchema()

# Handle missing values (example: fill with mean/mode, adapt as needed)
for column in df.columns:
    if df.select(column).dtypes[0][1] == "int" or df.select(column).dtypes[0][1] == "double":
        mean_val = df.select(avg(col(column))).collect()[0][0]
        df = df.fillna({column: mean_val})
    else:
        mode_val = df.groupBy(column).count().orderBy(col("count").desc()).first()[0]
        df = df.fillna({column: mode_val})

# Convert categorical columns to numeric using StringIndexer
categorical_cols = [item[0] for item in df.dtypes if item[1] == 'string']
for col_name in categorical_cols:
    indexer = StringIndexer(inputCol=col_name, outputCol=col_name + "_index")
    df = indexer.fit(df).transform(df).drop(col_name).withColumnRenamed(col_name + "_index", col_name)

# b) Perform Exploratory Data Analysis (EDA) to find patterns
promotion_rate_dept = df.groupBy("department").agg(avg("PromotionStatus").alias("PromotionRate"))
promotion_rate_dept.show()

# Example EDA: Average training score by promotion status
avg_score_promotion = df.groupBy("PromotionStatus").agg(avg("TrainingHours").alias("AvgTrainingHours"))
avg_score_promotion.show()

# Assemble features
feature_cols = [col_name for col_name in df.columns if col_name not in ["EmployeeID", "PromotionStatus"]] #Adjust as needed
assembler = VectorAssembler(inputCols=feature_cols, outputCol="features")
df = assembler.transform(df)

# Scale features
scaler = MinMaxScaler(inputCol="features", outputCol="scaled_features")
df = scaler.fit(df).transform(df)

# Split data into train and test sets
train_df, test_df = df.randomSplit([0.8, 0.2], seed=42)

# c) Train a classification model to predict employee promotions
classifier = LogisticRegression(featuresCol="scaled_features", labelCol="PromotionStatus")
clf_model = classifier.fit(train_df)
clf_predictions = clf_model.transform(test_df)

# d) Evaluate and visualize model performance
clf_evaluator = BinaryClassificationEvaluator(labelCol="PromotionStatus")
auc = clf_evaluator.evaluate(clf_predictions)
print("Classification AUC:", auc)

# Visualization - Classification (Promotion Prediction)
clf_pandas = clf_predictions.select("PromotionStatus", "prediction").toPandas()
plt.figure(figsize=(6, 4))
plt.hist([clf_pandas["PromotionStatus"][clf_pandas["prediction"] == 0],
          clf_pandas["PromotionStatus"][clf_pandas["prediction"] == 1]],
         bins=2, label=["Not Promoted", "Promoted"], color=["blue", "red"])
plt.xticks([0, 1])
plt.xlabel("Actual Promotion")
plt.ylabel("Count")
plt.title("Promotion Prediction - Classification")
plt.legend()
plt.show()

# e) Deploy the model to make future prediction (Example)
# Save the model
clf_model.save("hdfs://localhost:9000/user/220968002/week10/q2_clf_model")

# Load the model for future predictions
from pyspark.ml.classification import LogisticRegressionModel
loaded_model = LogisticRegressionModel.load("hdfs://localhost:9000/user/220968002/week10/q2_clf_model")

# Assume 'new_data' is a new DataFrame with the same schema as test_df (without 'PromotionStatus')
# new_predictions = loaded_model.transform(new_data)
# new_predictions.select("employee_id", "prediction").show() #show the predicted promotion status

spark.stop()
