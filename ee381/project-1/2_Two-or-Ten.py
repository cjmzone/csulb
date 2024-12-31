import numpy as np
import matplotlib.pyplot as plt

def roll_2or10():
    qualifiers = [2,10]
    count = 0

    while True:
        sum = np.random.randint(1, 7) + np.random.randint(1, 7)
        count += 1

        if sum in qualifiers:
            return count

def problem2():
    num_of_rolls = 100000
    rolls = [roll_2or10() for x in range(num_of_rolls)]
    roll_counts = np.bincount(rolls)
    pmf = roll_counts / num_of_rolls

    plt.stem(np.arange(len(pmf)), pmf, basefmt=" ")
    plt.xlabel('Number of Rolls until Success')
    plt.ylabel('Probability')
    plt.title('PMF of Rolls Until Success (Sum of 2 or 10) in 100,000 Rolls')
    plt.show()

problem2()