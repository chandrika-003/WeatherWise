import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.impute import SimpleImputer
from sklearn.pipeline import Pipeline
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.metrics import mean_squared_error

df = pd.read_csv('weatherAUS.csv')

required_columns = ['Rainfall', 'MinTemp', 'MaxTemp', 'Pressure3pm']
df = df.dropna(subset=required_columns)

df['Temp'] = (df['MinTemp'] + df['MaxTemp']) / 2

X = df[['Temp', 'Pressure3pm']]
y = df['Rainfall']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

pipeline = Pipeline([
    ('imputer', SimpleImputer(strategy='mean')),
    ('regressor', GradientBoostingRegressor(random_state=42))
])

pipeline.fit(X_train, y_train)

predictions = pipeline.predict(X_test)

mse = mean_squared_error(y_test, predictions)
print("Mean Squared Error:", mse)

input_data = pd.DataFrame({
    'Temp':[34.1],
    'Pressure3pm': [1010.11] 
})

predicted_rainfall = pipeline.predict(input_data)
predicted_label = "No Rain(Low Chances)" if predicted_rainfall[0] < 1 else ("Moderate Chances" if predicted_rainfall[0] < 2 else "High Chances")
print("Predicted Rainfall:", predicted_label)