import numpy as np
import matplotlib.pyplot as plt

mu = 50  
sigma = 10 
n = 25  
numSamples = 500 
z = 1.96  


np.random.seed(42)  
samples = np.random.normal(mu, sigma, (numSamples, n))

sampleMeans = samples.mean(axis=1)
standardError = sigma / np.sqrt(n)
lowerBounds = sampleMeans - z * standardError
upperBounds = sampleMeans + z * standardError


containsMu = (lowerBounds <= mu) & (upperBounds >= mu)
coverageRate = containsMu.mean() * 100  

plt.figure(figsize=(10, 6))
for i in range(numSamples):
    plt.plot([i, i], [lowerBounds[i], upperBounds[i]], color='blue', alpha=0.5)
    plt.scatter(i, sampleMeans[i], color='red', s=10)

plt.axhline(mu, color='green', linestyle='--', label="True Mean (50)")
plt.title(f"Confidence Intervals for {numSamples} Samples\nCoverage Rate: {coverageRate:.2f}%")
plt.xlabel("Sample Index")
plt.ylabel("Sample Mean and CI")
plt.legend()
plt.show()

print(f"Out of {numSamples} confidence intervals, {containsMu.sum()} contain the true mean.")
print(f"Coverage rate: {coverageRate:.2f}%")
