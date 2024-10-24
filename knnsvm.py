import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score

# Step 1: Load the dataset
data = pd.read_csv('emails.csv')

# Step 2: Preprocess the data
# Checking for missing values
print(data.isnull().sum())

# The dataset might need encoding for the target variable, assuming 'spam' column indicates 1 for spam and 0 for not spam
X = data.drop('spam', axis=1)  # Features
y = data['spam']  # Target variable

# Standardizing the features for better performance with KNN and SVM
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Step 3: Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Step 4: Train the KNN model
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)

# Train the SVM model
svm = SVC(kernel='linear')  # Using a linear kernel
svm.fit(X_train, y_train)

# Step 5: Make predictions and evaluate performance
# Predictions for KNN
y_pred_knn = knn.predict(X_test)

# Predictions for SVM
y_pred_svm = svm.predict(X_test)

# Evaluation for KNN
print("KNN Evaluation:")
conf_matrix_knn = confusion_matrix(y_test, y_pred_knn)
accuracy_knn = accuracy_score(y_test, y_pred_knn)
precision_knn = precision_score(y_test, y_pred_knn)
recall_knn = recall_score(y_test, y_pred_knn)

print("Confusion Matrix (KNN):")
print(conf_matrix_knn)
print(f"Accuracy (KNN): {accuracy_knn:.2f}")
print(f"Precision (KNN): {precision_knn:.2f}")
print(f"Recall (KNN): {recall_knn:.2f}")

# Evaluation for SVM
print("\nSVM Evaluation:")
conf_matrix_svm = confusion_matrix(y_test, y_pred_svm)
accuracy_svm = accuracy_score(y_test, y_pred_svm)
precision_svm = precision_score(y_test, y_pred_svm)
recall_svm = recall_score(y_test, y_pred_svm)

print("Confusion Matrix (SVM):")
print(conf_matrix_svm)
print(f"Accuracy (SVM): {accuracy_svm:.2f}")
print(f"Precision (SVM): {precision_svm:.2f}")
print(f"Recall (SVM): {recall_svm:.2f}")
