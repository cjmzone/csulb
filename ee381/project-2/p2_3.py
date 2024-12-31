import random

P0 = 0.40
P1 = 1 - P0
E0 = 0.02
E1 = 0.015
N = 10000

r1Total = 0
r1S1 = 0

for _ in range(N):
    S = 0 if random.uniform(0, 1) <= P0 else 1
    
    if S == 0:
        R = 1 if random.uniform(0, 1) <= E0 else 0
    else:
        R = 1 if random.uniform(0, 1) > E1 else 0
    
    if R == 1:
        r1Total += 1
        if S == 1:
            r1S1 += 1

conditionalProbability = r1S1 / r1Total if r1Total > 0 else 0
print(f"Conditional probability P(S = 1 | R = 1): {conditionalProbability}")
