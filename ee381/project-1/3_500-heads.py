import numpy as np
import matplotlib.pyplot as plot

def tossCoin():
    tosses = np.random.randint(2, size=1000)
    return np.sum(tosses)

def fiveHundredHeads(n):
    count = 0
    for x in range(n):
        heads = tossCoin()
        if heads == 500:
            count = count + 1

    pmf = count / n
    return count, pmf

def problem3():
    n = 100000
    count, pmf = fiveHundredHeads(n)

    print("Count: ", count)
    print("Probability: ", pmf)

problem3()
