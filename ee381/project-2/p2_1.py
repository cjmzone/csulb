import random

E0 = 0.02  
E1 = 0.015  
P0 = 0.4    

def transmittedMsg(S):
    randomNumber = random.uniform(0, 1)
    if S == 0:
        return 1 if randomNumber <= E0 else 0  
    else:
        return 0 if randomNumber <= E1 else 1  

N = 100000  
counter = 0  
S = 0 

for x in range(N):
    M = random.uniform(0, 1)
    S = 0 if M <= P0 else 1
    
    R = transmittedMsg(S)
    
    if S != R:
        counter += 1

failureProbability = counter / N
print("Probability of Transmission failure:", failureProbability)
