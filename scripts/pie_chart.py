
import matplotlib.pyplot as plt

import pandas as pd
from sqlalchemy import create_engine

# PostgreSQL connection string
engine = create_engine("postgresql+psycopg2://inicio_admin:mypassword@localhost:5432/inicio_db")

# Load transactions into DataFrame
df = pd.read_sql("SELECT * FROM transactions", engine)

# Ensure 'amount' is numeric
df['amount'] = pd.to_numeric(df['amount'])

# Group by ticker
holdings = df.groupby('ticker')['amount'].sum()

# Plot pie chart
plt.figure(figsize=(6,6))
plt.pie(holdings, labels=holdings.index, autopct='%1.1f%%', startangle=90)
plt.title('Relative Holdings by Ticker')
plt.tight_layout()

# Save image
plt.savefig('docs/img/holdings_pie.png')  # Save to same folder as dashboard.php
plt.close()