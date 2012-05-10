from math import sqrt

def generate_primes(limit):
    sieve = [True] * (limit+1)
    sieve[0] = False
    sieve[1] = False

    primes = []

    for n in xrange(2,limit+1):
        if not sieve[n]:
            continue

        primes.append( n )

        for i in xrange( 2*n, limit+1, n ):
            sieve[i] = False

    return primes


number = 600851475143
primes = generate_primes(int(sqrt(number)))
for divisor in reversed(primes):
    if number % divisor == 0:
        print divisor
        break