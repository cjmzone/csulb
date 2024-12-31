import numpy as np
import matplotlib.pyplot as plt
import random

# Input: probability vector summing to 1
# Output: side of die based on input probability
def nSideDie(p):
    sides = len(p)
    roll = np.random.random()
    prob_sum = 0
    for i in range(0,sides):
        prob_sum = prob_sum + p[i]
        if i == 0:
            if roll <= prob_sum:
                value = i + 1
            else:
                value = 0
        else:
            if roll > prob_sum - p[i] and roll <= prob_sum:
                value = i + 1
    return value

def problem1():
    # Function test: Plot 10,000 rolls
    # Probability vector given by professor
    #   1      2       3      4     5     6     7
    p=[0.10,  0.15,  0.20,  0.05,  0.30, 0.10, 0.10]

    # Generate 1000 rolls
    rolls = [nSideDie(p) for x in range(10000)]
    side = range(1,len(p)+1)
    sideCounts = [rolls.count(x)/10000 for x in side]

    # Stem plot graphing
    plt.stem(side,sideCounts)
    plt.title('PMF of 7 sided die')
    plt.xlabel('Face')
    plt.ylabel('Occurences of face')
    plt.show()

problem1()