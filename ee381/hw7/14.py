import numpy as np

# Data
temperatures = np.array([170, 172, 173, 174, 174, 175, 176, 177, 180, 180, 180, 180, 180, 181, 181, 182, 182, 182, 182, 184, 184, 185, 186, 188])
ratios = np.array([0.84, 1.31, 1.42, 1.03, 1.07, 1.08, 1.04, 1.80, 1.45, 1.60, 1.61, 2.13, 2.15, 0.84, 1.43, 0.90, 1.81, 1.94, 2.68, 1.49, 2.52, 3.00, 1.87, 3.08])

# Calculate means
temp_mean = temperatures.mean()
ratio_mean = ratios.mean()

print("Temperature Mean:", temp_mean)
print("Ratio Mean:", ratio_mean)

# Calculate b1 (slope) and b0 (intercept)
numerator = np.sum((temperatures - temp_mean) * (ratios - ratio_mean))
denominator = np.sum((temperatures - temp_mean) ** 2)
b1 = numerator / denominator
b0 = ratio_mean - b1 * temp_mean

print("b_1 (slope):", b1)
print("b_0 (intercept):", b0)

# Calculate the regression line and residuals
regressionLine = b0 + b1 * temperatures
residuals = ratios - regressionLine

# Calculate SSE
SSE = np.sum(residuals ** 2)

print("SSE:", SSE)
