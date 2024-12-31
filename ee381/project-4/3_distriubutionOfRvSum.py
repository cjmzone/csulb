
import numpy as np
import matplotlib.pyplot as plt

N = 10000  
lambda_param = 2  
num_bins = 50  

U = np.random.uniform(0, 1, N)  
T = -np.log(1 - U) / lambda_param  

plt.figure(figsize=(10, 6))
plt.hist(T, bins=num_bins, density=True, alpha=0.6, color='blue', label='Histogram')

t = np.linspace(0, np.max(T), 1000)
f_T = lambda_param * np.exp(-lambda_param * t)
plt.plot(t, f_T, 'r', lw=2, label='Exponential PDF')

plt.title('Histogram of Battery Lifetime and Exponential PDF')
plt.xlabel('Battery Lifetime (T)')
plt.ylabel('Probability Density')
plt.legend()
plt.grid(True)
plt.show()
