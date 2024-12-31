import random

E1 = 0.015  
N = 100000  

total_S1 = 0  
success_S1_R1 = 0  

for _ in range(N):
    S = 1  
    T = random.uniform(0, 1)
    R = 1 if T > E1 else 0

    total_S1 += 1
    if R == 1:
        success_S1_R1 += 1

conditionalProbability = success_S1_R1 / total_S1
print(f"Conditional probability P(R = 1 | S = 1): {conditionalProbability}")
