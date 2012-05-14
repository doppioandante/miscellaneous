from collections import defaultdict

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
for factors in factor_list:
    for factor, exp in factors:
        lcm[factor] = max(lcm[factor], exp)

print reduce(lambda a, b: a * b, (p ** e for p, e in lcm.iteritems()))
