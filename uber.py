# Step 1: Importing Libraries
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error, r2_score
from geopy.distance import great_circle
import datetime

# Step 2: Load the dataset
df = pd.read_csv('uber_fare_dataset.csv')

# Step 3: Check the first few rows
print(df.head())

# Step 4: Handle missing values
print(df.isnull().sum())  # Check for missing values
df = df.dropna()  # Drop rows with missing values

# Step 5: Convert pickup_datetime to datetime format
df['pickup_datetime'] = pd.to_datetime(df['pickup_datetime'], errors='coerce')

# Step 6: Extract useful features from the datetime
df['hour'] = df['pickup_datetime'].dt.hour
df['day'] = df['pickup_datetime'].dt.day
df['month'] = df['pickup_datetime'].dt.month
df['year'] = df['pickup_datetime'].dt.year
df['day_of_week'] = df['pickup_datetime'].dt.dayofweek

# Step 7: Feature engineering - calculate the distance using latitude and longitude
def haversine_distance(row):
    pickup = (row['pickup_latitude'], row['pickup_longitude'])
    dropoff = (row['dropoff_latitude'], row['dropoff_longitude'])
    return great_circle(pickup, dropoff).kilometers

df['distance_km'] = df.apply(haversine_distance, axis=1)

# Step 8: Drop irrelevant columns
df = df.drop(columns=['key', 'pickup_datetime'])

# Print the updated dataframe
print(df.head())


# Visualize outliers using boxplot
plt.figure(figsize=(10, 5))
sns.boxplot(df['fare_amount'])
plt.title("Fare Amount Outliers")
plt.show()

plt.figure(figsize=(10, 5))
sns.boxplot(df['distance_km'])
plt.title("Distance Outliers")
plt.show()

# Remove outliers using Z-score for 'fare_amount' and 'distance_km'
from scipy import stats
df = df[(np.abs(stats.zscore(df['fare_amount'])) < 3)]
df = df[(np.abs(stats.zscore(df['distance_km'])) < 3)]

# Check the dataset after removing outliers
print(df.shape)

# Correlation matrix
correlation_matrix = df.corr()

# Plotting the heatmap of the correlation matrix
plt.figure(figsize=(12, 8))
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm')
plt.title("Correlation Matrix")
plt.show()


# Step 1: Define features (X) and target (y)
X = df[['distance_km', 'hour', 'day', 'month', 'year', 'day_of_week']]
y = df['fare_amount']

# Step 2: Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Step 3: Linear Regression model
lr_model = LinearRegression()
lr_model.fit(X_train, y_train)

# Step 4: Random Forest model
rf_model = RandomForestRegressor(n_estimators=100, random_state=42)
rf_model.fit(X_train, y_train)

# Step 5: Predictions
lr_predictions = lr_model.predict(X_test)
rf_predictions = rf_model.predict(X_test)

# Evaluation function to calculate RMSE and R2
def evaluate_model(y_true, y_pred):
    rmse = np.sqrt(mean_squared_error(y_true, y_pred))
    r2 = r2_score(y_true, y_pred)
    return rmse, r2

# Linear Regression evaluation
lr_rmse, lr_r2 = evaluate_model(y_test, lr_predictions)
print(f"Linear Regression - RMSE: {lr_rmse}, R2: {lr_r2}")

# Random Forest Regression evaluation
rf_rmse, rf_r2 = evaluate_model(y_test, rf_predictions)
print(f"Random Forest - RMSE: {rf_rmse}, R2: {rf_r2}")
