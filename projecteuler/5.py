from collections import defaultdict
from itertools import chain
from functools import reduce
from operator import mul

# list of factors for the numbers from 2 to 20
# each factor is in the form (prime_factor, exponent)
factor_list = [
    [(2, 1)],
    [(3, 1)],
    [(2, 2)],
    [(5, 1)],
    [(2, 1), (3, 1)],
    [(7, 1)],
    [(2, 3)],
    [(3, 2)],
    [(2, 1), (5, 1)],
    [(11, 1)],
    [(2, 2), (3, 1)],
    [(13, 1)],
    [(2, 1), (7, 1)],
    [(3, 1), (5, 1)],
    [(2, 4)],
    [(17, 1)],
    [(2, 1), (3, 2)],
    [(19, 1)],
    [(2, 2), (5, 1)]
]

# Compute lcm
lcm = defaultdict(lambda: 0)
for base, exp in chain.from_iterable(factor_list):
    lcm[base] = max(lcm[base], exp)

# first compute base^exp for all the factor in lcm, then multiply them
print(reduce(mul, (base ** exp for base, exp in lcm.items())))
