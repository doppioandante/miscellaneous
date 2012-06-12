from array import array
from math import sqrt
from bisect import bisect_left, bisect_right


class prime_generator(object):
    def __init__(self):
        self.sieve = array('b')
        self.sieve.fromlist([0, 0])
        # NOTE: upper_bound == len(sieve)-1 for values <= to max_size
        self.upper_bound = 1
        self.prime_cache = array('L')
        self.max_size = 10 ** 7

    def generate(self, upper_bound):
        if upper_bound > self.max_size:
            # Do not use eratosthenes' sieve
            self._generate_2(upper_bound)
            return

        if upper_bound <= self.upper_bound:
            return

        # extend our sieve if needed
        for i in range(0, upper_bound - self.upper_bound):
            self.sieve.append(1)

        for n in range(2, int(sqrt(upper_bound))+1):
            if not self.sieve[n]:
                continue

            # we got a prime, save it and mark all the multiples
            startPos = max(n * n, self.upper_bound + n - (self.upper_bound%n))

            for m in range(startPos, upper_bound+1, n):
                self.sieve[m] = 0

        self._cache_primes(upper_bound)
        self.upper_bound = upper_bound

    def _generate_2(self, upper_bound):
        self.generate(self.max_size)

        for i in range(self.upper_bound+1, upper_bound+1):
            prime = True
            limit = int(sqrt(upper_bound))
            for p in self.prime_cache:
                if p > limit:
                    break
                if i % p == 0:
                    prime = False
                    break

            if prime:
                self.prime_cache.append(i)

        self.upper_bound = upper_bound

    def _cache_primes(self, upper_bound):
        for i in range(self.upper_bound+1, upper_bound+1):
            if self.sieve[i]:
                self.prime_cache.append(i)

    def get_primes(self, m, n):
        assert m <= n <= self.upper_bound

        r1 = bisect_left(self.prime_cache, m)
        r2 = bisect_right(self.prime_cache, n)

        return self.prime_cache[r1:r2]

g = prime_generator()
size = 1024
toFind = 10001

g.generate(size)
arr = g.prime_cache
while len(arr) < toFind:
    size *= 2
    g.generate(size)
    arr = g.prime_cache

print(arr[toFind-1])
