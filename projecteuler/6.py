n = 100

def sumUpTo(n):
    return n*(n+1) // 2

def sumSquaresUpTo(n):
    return n*(n+1)*(2*n+1) // 6

print(sumUpTo(n)**2 - sumSquaresUpTo(n))
