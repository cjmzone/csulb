import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import binom

numOfRolls = 1000
numOfExperiments = 10000
probabilities = [0.10, 0.20, 0.15, 0.25, 0.30]

p_singleSuccess = probabilities[0] ** 3

xValues = np.arange(0, 10)

binomialPMF = binom.pmf(xValues, numOfRolls, p_singleSuccess)

plt.figure(figsize=(10, 6))
plt.stem(xValues, binomialPMF, basefmt="r-", linefmt="b-", markerfmt="bo")
plt.xlabel('Number of Successes in n=1000 Trials')
plt.ylabel('Probability')
plt.title('Bernoulli Trials: PMF - Binomial Formula')
plt.grid(True)
plt.show()