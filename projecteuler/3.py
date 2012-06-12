from math import sqrt

# not so optimized, but will do it
def generate_primes(limit):
    sieve = [True] * (limit+1)
    sieve[0] = False
    sieve[1] = False

    primes = []

    for n in range(2,limit+1):
        if not sieve[n]:
            continue

        primes.append( n )

        for i in range( 2*n, limit+1, n ):
            sieve[i] = False

    return primes


number = 600851475143
primes = generate_primes(int(sqrt(number)))
for divisor in reversed(primes):
    if number % divisor == 0:
        print(divisor)
        break
