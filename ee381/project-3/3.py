import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import binom, poisson

# Parameters
n_rolls = 1000   # Number of rolls per experiment
n_experiments = 10000   # Number of experiments
success_condition = (1, 1, 1)   # Condition for a success (all dice roll a '1')

# Probability distribution for each die
probabilities = [0.10, 0.20, 0.15, 0.25, 0.30]
sides = [1, 2, 3, 4, 5]

# Part 1: Experimental Bernoulli Trials
# Run the experiments
success_counts = []
for _ in range(n_experiments):
    rolls = np.random.choice(sides, size=(n_rolls, 3), p=probabilities)
    successes = np.sum(np.all(rolls == success_condition, axis=1))
    success_counts.append(successes)

# Calculate experimental PMF
unique, counts = np.unique(success_counts, return_counts=True)
pmf_values = counts / n_experiments

# Plot Experimental PMF
plt.figure(figsize=(10, 6))
plt.stem(unique, pmf_values, basefmt="r-", linefmt="b-", markerfmt="bo")
plt.xlabel('Number of Successes in n=1000 Trials')
plt.ylabel('Probability')
plt.title('Bernoulli Trials: PMF - Experimental Results')
plt.grid(True)
plt.show()

# Part 2: Binomial Distribution
# Probability of success in a single roll (p) for Binomial calculation
p_single_success = probabilities[0] ** 3  # Probability of rolling three 1s with the given distribution

# Define possible values of X (number of successes)
x_values = np.arange(0, 10)  # Setting a reasonable range for PMF based on expected values

# Calculate Binomial PMF
binomial_pmf = binom.pmf(x_values, n_rolls, p_single_success)

# Plot Binomial PMF
plt.figure(figsize=(10, 6))
plt.stem(x_values, binomial_pmf, basefmt="r-", linefmt="b-", markerfmt="bo")
plt.xlabel('Number of Successes in n=1000 Trials')
plt.ylabel('Probability')
plt.title('Bernoulli Trials: PMF - Binomial Formula')
plt.grid(True)
plt.show()

lambda_param = n_rolls * p_single_success

poisson_pmf = poisson.pmf(x_values, lambda_param)

# Plot Poisson PMF
plt.figure(figsize=(10, 6))
plt.stem(x_values, poisson_pmf, basefmt="r-", linefmt="b-", markerfmt="bo")
plt.xlabel('Number of Successes in n=1000 Trials')
plt.ylabel('Probability')
plt.title('Bernoulli Trials: PMF - Poisson Approximation')
plt.grid(True)
plt.show()
