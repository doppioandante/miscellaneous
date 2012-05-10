n = 1000-1

def sum(n):
    return n*(n+1)/2

def multipleSum(m,n):
    return m*sum(n//m)

print multipleSum(3,n)+multipleSum(5,n)-multipleSum(15,n)