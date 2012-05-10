from sys import stdin

class memoize:
    def __init__(self,func):
        self.func = func
        self.cache = {}

    def __call__(self,n):
        if n not in self.cache:
            self.cache[n] = self.func(n)

        return self.cache[n]


@memoize
def coins(n):
    if n == 0:
        return n

    return max(n, coins(n//2)+coins(n//3)+coins(n//4))

for line in stdin.xreadlines():
    value = int(line)
    print coins(value)