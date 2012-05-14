try:
    from math import factorial
except:
    def factorial(n):
        res = 1
        while n != 0:
            res *= n
            n -= 1

        return res

def combinations(n, k):
    den1 = min(k, n-k)
    den2 = n - den1

    num  = 1
    for p in xrange(den2+1, n+1):
        num *= p

    return num / factorial(den1)

T = input()

# (n)*(n-1)*...*(n-k+1)
# ---------------------
#  k*(k-1)*...*(k-k+1)

for t in xrange(T):
    n, k = [int(x) for x in raw_input().split()]
    print( combinations(n-1, n-k) )
    # x1 + x2 + x3 + ... + xk = n (1)
    # with 1 <= xi <= n-k
    # set xi' as x1-1, then we can rewrite (1) as
    # x1'+1 + x2'+1 + x3'+1 + ... + xk'+1 = n
    # x1' + x2' + x3' + ... + xk' = n-k
    # with 0 <= xi' <= n-k
    # then the possibilities are (n-k)+k-1 choice n-k = n-1 choice n-k

