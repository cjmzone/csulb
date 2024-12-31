import numpy as np

class Card:
    def __init__(self, value, color):
        self.value = value
        self.color = color
    
    def __repr__(self):
        return f"{self.value} of {self.color}"

def buildDeck():
    colors = ["clubs", "hearts", "spades", "diamonds"]
    values = ["A", "2","3","4","5","6","7","8","9","10","J","Q","K"]
    deck = [Card(value, color) for value in values for color in colors]  
    return deck

def drawCards(deck):
    cardsDrawn = np.random.choice(deck, size = 5, replace = False)
    return cardsDrawn

def isFourOfAKind(cardsDrawn):
    values = [card.value for card in cardsDrawn]
    for x in values:
        if values.count(x) == 4:
            return True
    return False

def simulate(n):
    deck = buildDeck()
    count = 0

    for x in range(n):
        drawnCards = drawCards(deck)
        if isFourOfAKind(drawnCards):
            count = count + 1
    
    pmf = count / n
    return count, pmf

def problem4():
    n = 1000000
    count, pmf = simulate(n)
    print("Count: ", count)
    print("Probability: ", pmf)

problem4()