import numpy as np

# Define the data (Y_ij)
Y = np.array([
    [64, 49, 50],  # Coating 1
    [53, 51, 48],  # Coating 2
    [47, 45, 50],  # Coating 3
    [51, 43, 52]   # Coating 4
])

# Step 1: Calculate the grand mean (Y..)
grand_mean = Y.mean()

# Step 2: Calculate row means (Y_i.)
row_means = Y.mean(axis=1)

# Step 3: Calculate column means (Y_.j)
col_means = Y.mean(axis=0)

# Step 4: Compute residuals based on the formula
residuals = Y - row_means[:, np.newaxis] - col_means + grand_mean

# Step 5: Compute SSE by summing the squared residuals
squared_residuals = residuals**2
SSE = squared_residuals.sum()

print("SSE:", SSE)
