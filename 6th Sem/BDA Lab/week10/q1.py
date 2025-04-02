import matplotlib.pyplot as plt
import pandas as pd
from pyspark.sql import SparkSession
from pyspark.ml.feature import StringIndexer, VectorAssembler, MinMaxScaler
from pyspark.ml.regression import LinearRegression
from pyspark.ml.classification import LogisticRegression
from pyspark.ml.evaluation import RegressionEvaluator, BinaryClassificationEvaluator

# Initialize Spark session
spark = SparkSession.builder.appName("question1").getOrCreate()

# Load CSV file
file_path = "hdfs://localhost:9000/user/220968002/week10/employee_attrition.csv"
df = spark.read.csv(file_path, header=True, inferSchema=True)

# Display dataset sample and schema
print("Dataset Sample")
df.show(5)
print("Dataset Schema")
df.printSchema()

# Convert categorical features to numerical using StringIndexer
overtime_indexer = StringIndexer(inputCol="OverTime", outputCol="overtime_index")
jobrole_indexer = StringIndexer(inputCol="JobRole", outputCol="jobrole_index")
department_indexer = StringIndexer(inputCol="Department", outputCol="department_index")

df = overtime_indexer.fit(df).transform(df)
df = jobrole_indexer.fit(df).transform(df)
df = department_indexer.fit(df).transform(df)

# Assemble features separately for regression and classification
assembler_reg = VectorAssembler(
    inputCols=["Age", "department_index", "jobrole_index", "YearsAtCompany", "Education", "WorkLifeBalance", "overtime_index", "JobSatisfaction"],
    outputCol="features_reg")
df = assembler_reg.transform(df)

assembler_cls = VectorAssembler(
    inputCols=["Age", "department_index", "jobrole_index", "YearsAtCompany","MonthlyIncome", "Education", "WorkLifeBalance", "overtime_index", "JobSatisfaction"],
    outputCol="features_cls")
df = assembler_cls.transform(df)

# Scale features
scaler_reg = MinMaxScaler(inputCol="features_reg", outputCol="scaled_features_reg")
scaler_model_reg = scaler_reg.fit(df)
df = scaler_model_reg.transform(df)

scaler_cls = MinMaxScaler(inputCol="features_cls", outputCol="scaled_features_cls")
scaler_model_cls = scaler_cls.fit(df)
df = scaler_model_cls.transform(df)

# Split data into training and testing sets
train_df, test_df = df.randomSplit([0.8, 0.2], seed=42)

# Classification Model (Predicting Attrition)
classifier = LogisticRegression(featuresCol="scaled_features_cls", labelCol="Attrition")
clf_model = classifier.fit(train_df)
clf_predictions = clf_model.transform(test_df)
clf_evaluator = BinaryClassificationEvaluator(labelCol="Attrition")
auc = clf_evaluator.evaluate(clf_predictions)
print("Classification AUC:", auc)

# Regression Model (Predicting Monthly Income)
lr = LinearRegression(featuresCol="scaled_features_reg", labelCol="MonthlyIncome")
reg_model = lr.fit(train_df)
reg_predictions = reg_model.transform(test_df)
reg_evaluator = RegressionEvaluator(labelCol="MonthlyIncome", metricName="rmse")
rmse = reg_evaluator.evaluate(reg_predictions)
print("Regression RMSE:", rmse)

# Convert predictions to Pandas DataFrame
reg_pandas = reg_predictions.select("MonthlyIncome", "prediction").toPandas()
clf_pandas = clf_predictions.select("Attrition", "prediction").toPandas()

# Visualization - Regression
plt.figure(figsize=(8, 5))
plt.scatter(reg_pandas["MonthlyIncome"], reg_pandas["prediction"], alpha=0.5, color="blue", label="Predicted")
plt.plot([reg_pandas["MonthlyIncome"].min(), reg_pandas["MonthlyIncome"].max()],
         [reg_pandas["MonthlyIncome"].min(), reg_pandas["MonthlyIncome"].max()],
         color="red", linestyle="--", label="Perfect Prediction")
plt.xlabel("Actual Salary")
plt.ylabel("Predicted Salary")
plt.title("Salary Prediction - Regression")
plt.legend()
plt.show()

# Visualization - Classification
plt.figure(figsize=(6, 4))
plt.hist([clf_pandas["Attrition"][clf_pandas["prediction"] == 0],
          clf_pandas["Attrition"][clf_pandas["prediction"] == 1]],
         bins=2, label=["No Churn", "Churn"], color=["blue", "red"])
plt.xticks([0, 1])
plt.xlabel("Actual Churn")
plt.ylabel("Count")
plt.title("Churn Prediction - Classification")
plt.legend()
plt.show()

# Save Models to HDFS
reg_model.save("hdfs://localhost:9000/user/220968002/week10/regression_model")
clf_model.save("hdfs://localhost:9000/user/220968002/week10/classification_model")

# Load and use saved classification model
from pyspark.ml.classification import LogisticRegressionModel
loaded_clf = LogisticRegressionModel.load("hdfs://localhost:9000/user/220968002/week10/classification_model")
new_predictions = loaded_clf.transform(test_df)
new_predictions.select("Attrition", "prediction").show(5)

# Stop Spark Session
spark.stop()

