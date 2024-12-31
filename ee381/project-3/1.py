import numpy as np
import matplotlib.pyplot as plt

numOfrolls = 1000   
numOfexperiments = 10000   
successCondition = (1, 1, 1)   

probabilities = [0.10, 0.20, 0.15, 0.25, 0.30]
sides = [1, 2, 3, 4, 5]

successes = []
for _ in range(numOfexperiments):
    rolls = np.random.choice(sides, size=(numOfrolls, 3), p=probabilities)
    successes = np.sum(np.all(rolls == successCondition, axis=1))
    successes.append(successes)

unique, counts = np.unique(successes, return_counts=True)
pmfValues = counts / numOfexperiments

plt.figure(figsize=(10, 6))
plt.stem(unique, pmfValues, basefmt="r-", linefmt="b-", markerfmt="bo")
plt.xlabel('Number of Successes in n=1000 Trials')
plt.ylabel('Probability')
plt.title('Bernoulli Trials: PMF - Experimental Results')
plt.grid(True)
plt.show()
