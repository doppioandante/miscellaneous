from array import array
from math import sqrt
from bisect import bisect_left, bisect_right
from itertools import repeat 

def is_present_sorted(array, x, low = 0, high = None):  
    hi = hi or len(array)  
    pos = bisect_left(array, x, low, high)
    return (pos != hi and array[pos] == x) 


class prime_generator:
    def __init__(self, max_sieve_size = 10000000):
        self.sieve = array('b', [0, 0])
        self.sieve_size = 1
        self.max_sieve_size = max_sieve_size

        self.primes = list()
        self.primes_upper_bound = 1


    def upper_bound(self):
        return max(self.sieve_size, self.primes_upper_bound)


    def is_prime(self, n):
        self.generate(n)

        if n <= self.sieve_size:
            return self.sieve[n]
        else:
            # TODO: what if search begins after the last prime found using the sieve?
            return is_present_sorted(self.primes, n)      


    def get_primes(self, m, n):
        assert m <= n

        self.generate(n)
        self._cache_primes(n)

        r1 = bisect_left(self.primes, m)
        r2 = bisect_right(self.primes, n)

        # Hoping that slicing in python does not perform a copy operation      
        return self.primes[r1:r2]         


    def generate(self, upper_bound):
        if upper_bound > self.upper_bound():                      
            if upper_bound > self.sieve_size and self.sieve_size != self.max_sieve_size:
                old_upper_bound = upper_bound

                assert upper_bound > self.sieve_size
                upper_bound = min(self.max_sieve_size, upper_bound)            

                # extend our sieve if needed
                self.sieve.extend(repeat(1, upper_bound - self.sieve_size))

                for n in range(2, int(sqrt(upper_bound)) + 1):
                    if self.sieve[n]:
                        # we've got a prime, save it and mark all the multiples
                        startPos = max(n * n, self.sieve_size + n - (self.sieve_size % n))

                        # mark the multiples
                        for m in range(startPos, upper_bound + 1, n):
                            self.sieve[m] = 0

                self.sieve_size = upper_bound
                upper_bound = old_upper_bound     
            
            if upper_bound > self.max_sieve_size:          
                assert upper_bound > self.primes_upper_bound
                assert self.sieve_size <= self.max_sieve_size

                self._cache_primes(self.max_sieve_size)
                assert self.primes_upper_bound >= self.max_sieve_size   

                for n in range(self.primes_upper_bound + 1, upper_bound + 1):
                    is_prime = True

                    limit = int(sqrt(n))

                    for prime in self.primes:
                        if n % prime == 0:
                            is_prime = False

                        if (not prime) or prime > limit:   
                            break

                    if is_prime:
                        self.primes.append(n)

                self.primes_upper_bound = upper_bound


    def _cache_primes(self, upper_bound):
        if upper_bound > self.primes_upper_bound and upper_bound <= self.max_sieve_size:
            
            for n in range(self.primes_upper_bound + 1, upper_bound + 1):
                if self.sieve[n]:
                    self.primes.append(n)

            self.primes_upper_bound = upper_bound        
                    

def find_divisors(number):
    gen = prime_generator()
    return (prime for prime in gen.get_primes(int(sqrt(number))) if number % prime == 0)


