import random

P0 = 0.40
E0 = 0.02
E1 = 0.015
N = 10000

def transmitMessage(S):
    receivedBits = []
    for _ in range(3):
        if S == 0:
            R = 1 if random.uniform(0, 1) <= E0 else 0
        else:
            R = 0 if random.uniform(0, 1) <= E1 else 1
        receivedBits.append(R)
    return receivedBits

def decodeMessage(receivedBits):
    return 1 if sum(receivedBits) >= 2 else 0

errorCount = 0

for _ in range(N):
    S = 0 if random.uniform(0, 1) <= P0 else 1
    receivedBits = transmitMessage(S)
    decodedBit = decodeMessage(receivedBits)
    if S != decodedBit:
        errorCount += 1

errorProbability = errorCount / N
print(f"Probability of incorrect decoding: {errorProbability}")
