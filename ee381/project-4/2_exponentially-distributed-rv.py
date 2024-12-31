import numpy as np
import matplotlib.pyplot as plt

alpha = 2  
N = 10000  

U = np.random.uniform(0, 1, N)

T = (-1 / alpha) * np.log(1 - U)

def f_t(t, alpha=2):
    return np.where(t >= 0, 2 * np.exp(-2 * t), 0)

plt.figure(figsize=(10, 6))

plt.hist(T, bins=50, density=True, alpha=0.6, color='blue', label="Histogram of T")

t_vals = np.linspace(0, max(T), 500)
pdf_vals = f_t(t_vals, alpha=alpha)
plt.plot(t_vals, pdf_vals, 'r-', linewidth=2, label=r"$f(t) = 2e^{-2t}$")


plt.xlabel("T", fontsize=12)
plt.ylabel("Density", fontsize=12)
plt.title("Histogram of Exponentially Distributed RV $T$ and PDF $f(t)$", fontsize=14)
plt.legend()
plt.grid(True)

plt.show()
