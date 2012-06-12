n = 1000-1

def sumUpTo(n):
    return n*(n+1) // 2

def multipleSum(m, n):
    return m * sumUpTo(n // m)

print(multipleSum(3, n)+multipleSum(5, n)-multipleSum(15, n))
