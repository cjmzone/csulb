import numpy as np

def generatePasscodes(m):
    return np.random.randint(0, 10000, size=m)

def doesPasscodeExist(passcode, m):
    passcodes = generatePasscodes(m)
    return passcode in passcodes

def simulate_experiments(passcode, m, N=1000):
    count = 0
    for _ in range(N):
        # Run the experiment: does the hacker's list contain the passcode?
        if doesPasscodeExist(passcode, m):
            count += 1
    # Calculate the probability of success
    return count / N

def problem5():
    # Generate a random 4-digit passcode for the user
    myPasscode = np.random.randint(0, 10000)
    print(f"My Passcode: {myPasscode}")
    
    # Part 1: When the hacker creates a list of m = 10^4 random passcodes
    m1 = 10000
    probability_m1 = simulate_experiments(myPasscode, m1)
    print(f"Probability of success when m = 10^4: {probability_m1:.4f}")

    # Part 2: When the hacker creates a list of m = 10^6 random passcodes
    m2 = 1000000
    probability_m2 = simulate_experiments(myPasscode, m2)
    print(f"Probability of success when m = 10^6: {probability_m2:.4f}")

    # Part 3: Find m such that the probability is approximately 0.5 (trial and error)
    def find_m_for_p_target(p_target=0.5):
        m = 1000  # Start with a smaller value for m
        step = 1000
        while True:
            probability = simulate_experiments(myPasscode, m)
            print(f"m = {m}, Probability = {probability:.4f}")
            if abs(probability - p_target) < 0.01:  # If the probability is close to 0.5
                break
            m += step  # Increase m by a step size
        return m

    m_approx = find_m_for_p_target(p_target=0.5)
    print(f"Approximate m for probability ~ 0.5: {m_approx}")
problem5()