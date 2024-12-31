import numpy as np

x = np.array([5,10,15,20,25,30,45,60])
y = np.array([16.3,9.7,8.1,4.2,3.4,2.9,1.9,1.3])

lnX = np.array(np.log(x))
lnY = np.array(np.log(y))

meanLnX = np.mean(lnX)
meanLnY = np.mean(lnY)

b = np.sum((lnX - meanLnX) * (lnY - meanLnY)) / np.sum((lnX - meanLnX) ** 2)

a = meanLnY - b * meanLnX

sumOfProducts = np.sum((lnX - meanLnX )* (lnY - meanLnY))
sumOfSquares = np.sum((lnX - meanLnX) ** 2)

bb = sumOfProducts / sumOfSquares

aa = meanLnY - bb * meanLnX

linearModel = a + b*meanLnX
print("linearModel: ", linearModel)

mositure = 20
print("mositure: ", aa + bb*np.log(mositure))

