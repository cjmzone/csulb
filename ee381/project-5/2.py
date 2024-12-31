import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm


a, b = 0, 1  
popMean = (a + b) / 2 
popVariance = ((b - a) ** 2) / 12  
popSTD = np.sqrt(popVariance)


n = 100  
num_samples = 1000 
np.random.seed(42)
samples = np.random.uniform(a, b, (num_samples, n))

sampleMeans = samples.mean(axis=1)

theoreticalMean = popMean
theoreticalSTD = popSTD / np.sqrt(n)

plt.figure(figsize=(10, 6))
plt.hist(sampleMeans, bins=30, density=True, alpha=0.6, color='skyblue', label="Sample Means Histogram")

x = np.linspace(min(sampleMeans), max(sampleMeans), 1000)
pdf = norm.pdf(x, loc = theoreticalMean, scale = theoreticalSTD)
plt.plot(x, pdf, 'r-', label="Theoretical Normal Distribution")

plt.title("Histogram of Sample Means vs. Theoretical Normal Distribution")
plt.xlabel("Sample Mean")
plt.ylabel("Density")
plt.axvline(popMean, color='green', linestyle='--', label="Theoretical Mean")
plt.legend()
plt.show()

print(f"Theoretical Mean of Sample Means: {popMean:.4f}")
print(f"Theoretical Standard Deviation of Sample Means: {theoreticalSTD:.4f}")
