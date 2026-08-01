import numpy as np
import pandas as pd
import yfinance as yf
import matplotlib.pyplot as plt
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv1D, MaxPooling1D, Flatten, Dense
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler

# Fetch AAPL stock data from Yahoo Finance
ticker = 'AAPL'
data = yf.download(ticker, start='2010-01-01', end='2024-01-01')

# Feature Engineering
data['day_of_week'] = data.index.dayofweek
data['month'] = data.index.month
data['day_of_year'] = data.index.dayofyear

# Select the features and target variable
features = data[['Close', 'day_of_week', 'month', 'day_of_year']]
target = data['Close'].values

# Normalize features
scaler = MinMaxScaler()
features_scaled = scaler.fit_transform(features)

# Prepare time series data
X = features_scaled.reshape((features_scaled.shape[0], features_scaled.shape[1], 1))
y = target

# Split data into training and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, shuffle=False)

# Define the model
model = Sequential([
    Conv1D(filters=64, kernel_size=2, activation='relu', input_shape=(X_train.shape[1], 1)),
    MaxPooling1D(pool_size=2),
    Flatten(),
    Dense(50, activation='relu'),
    Dense(1)
])

model.compile(optimizer='adam', loss='mse')
model.fit(X_train, y_train, epochs=20, verbose=1)
y_pred = model.predict(X_test)

# Plotting the results
plt.figure(figsize=(14, 7))
plt.plot(data.index[-len(y_test):], y_test, label='Actual Prices', color='b')
plt.plot(data.index[-len(y_test):], y_pred, label='Predicted Prices', color='r')
plt.title('Actual vs Predicted Prices for AAPL')
plt.xlabel('Date')
plt.ylabel('Price')
plt.legend()
plt.show()