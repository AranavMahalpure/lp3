# Importing the required libraries
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA

# Load the dataset
df = pd.read_csv('sales_data_sample.csv')

# Check the first few rows
print(df.head())

# Step 1: Drop irrelevant columns and handle missing values
df = df.dropna()  # Drop any rows with missing values if present

# Step 2: Select relevant features for clustering
# For demonstration, let's select numeric columns like 'SALES', 'QUANTITYORDERED', and 'PRICEEACH'
df_features = df[['SALES', 'QUANTITYORDERED', 'PRICEEACH']]

# Step 3: Standardize the data using StandardScaler
scaler = StandardScaler()
df_scaled = scaler.fit_transform(df_features)

# Check the scaled data
print(df_scaled[:5])  # Display the first 5 rows of scaled data

# Step 1: Calculate WCSS (Within-cluster sum of squares) for different number of clusters
wcss = []
for i in range(1, 11):  # Trying different numbers of clusters from 1 to 10
    kmeans = KMeans(n_clusters=i, init='k-means++', max_iter=300, n_init=10, random_state=42)
    kmeans.fit(df_scaled)
    wcss.append(kmeans.inertia_)

# Step 2: Plot the Elbow Method graph
plt.figure(figsize=(8,5))
plt.plot(range(1, 11), wcss, marker='o', linestyle='--')
plt.title('Elbow Method to Find Optimal Number of Clusters')
plt.xlabel('Number of clusters')
plt.ylabel('WCSS')
plt.show()

# Step 1: Apply K-Means clustering with optimal number of clusters (from elbow method)
optimal_clusters = 3  # Choose this based on the elbow plot
kmeans = KMeans(n_clusters=optimal_clusters, init='k-means++', max_iter=300, n_init=10, random_state=42)
df['Cluster'] = kmeans.fit_predict(df_scaled)

# Step 2: Add cluster labels to the original dataframe
print(df.head())  # Check the dataframe with clusters

# Step 1: Apply PCA to reduce dimensionality to 2D for visualization
pca = PCA(n_components=2)
df_pca = pca.fit_transform(df_scaled)

# Step 2: Create a new dataframe for the PCA results
df_pca_df = pd.DataFrame(data=df_pca, columns=['PCA1', 'PCA2'])
df_pca_df['Cluster'] = df['Cluster']

# Step 3: Visualize the clusters
plt.figure(figsize=(8,5))
sns.scatterplot(x='PCA1', y='PCA2', hue='Cluster', data=df_pca_df, palette='Set1')
plt.title('Clusters Visualized Using PCA')
plt.show()
