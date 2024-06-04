import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
import joblib

# Load the dataset
data = pd.read_csv("weather_data.csv")

# Prepare the features and target variable
X = data[['Temperature', 'Wind_Speed', 'Dew_Point', 'Visibility']].values
y = data['Rainfall'].values

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Train the Random Forest classifier
clf = RandomForestClassifier(n_estimators=100, random_state=42)
clf.fit(X_train, y_train)

# Save the trained model
joblib.dump(clf, 'rainfall_prediction_model.joblib')

# Function to predict rainfall based on input features
def predict_rainfall(temperature, wind_speed, dew_point, visibility):
    input_data = np.array([[temperature, wind_speed, dew_point, visibility]])
    clf = joblib.load('rainfall_prediction_model.joblib')
    prediction = clf.predict(input_data)
    if prediction[0] == 1:
        return "Rainfall is predicted"
    else:
        return "No rainfall is predicted"

# Example usage
temperature = input("Enter temparature")
wind_speed = input("Enter wind_speed")
dew_point = input("Enter dew_point")
visibility = input("Enter visibility")

result = predict_rainfall(temperature, wind_speed, dew_point, visibility)
print(result)