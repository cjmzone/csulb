import numpy as nump
import matplotlib.pyplot as plot

def nsided_die(p):
    return nump.random.choice(nump.arange(1, len(p) + 1), p = p)

def problem1():

    p = [0.20, 0.05, 0.10, 0.25, 0.30, 0.10]
    num_of_rolls = 1000 
    results = [nsided_die(p) for x in range(num_of_rolls)]
    count = nump.bincount(results)[1:]

    plot.stem(nump.arange(1, len(p) + 1), count / num_of_rolls)
    plot.title('PMF of 6-sided Die after 1000 Rolls')
    plot.xlabel('Face')
    plot.ylabel('Probability')
    plot.show()

problem1()