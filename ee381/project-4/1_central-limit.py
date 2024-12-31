import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import norm

a, b = 1, 3 
N = 10000  

mu_w = (a + b) / 2
sigmaW= np.sqrt((b - a) ** 2 / 12)

stack_sizes = [1, 5, 10, 15]
results = []

for n in stack_sizes:
  
    mu_s = n * mu_w
    sigmaS = sigmaW * np.sqrt(n)
    results.append((n, mu_s, sigmaS))
    
    stackThicknesses = [np.sum((b - a) * np.random.rand(n) + a) for _ in range(N)]
 
    plt.figure(figsize=(8, 5))
    plt.hist(stackThicknesses, bins=30, density=True, alpha=0.6, color='g', label="Simulated PDF")
    
    x = np.linspace(min(stackThicknesses), max(stackThicknesses), 1000)
    plt.plot(x, norm.pdf(x, mu_s, sigmaS), 'r-', lw=2, label="Normal PDF")
    
    plt.title(f"Stack of {n} Books")
    plt.xlabel("Thickness (cm)")
    plt.ylabel("Density")
    plt.legend()
    plt.grid()
    plt.show()

results_df = pd.DataFrame(results, columns=["Number of Books (n)", "Mean Thickness (cm)", "Std. Dev. Thickness (cm)"])
print(results_df)
