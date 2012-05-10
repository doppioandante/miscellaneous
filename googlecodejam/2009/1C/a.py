def solve(string):
    symbols = []
    for digit in string:
        if digit not in symbols:
            symbols += digit

    base = max(2, len(symbols))
    values = [1,0] + range(2, base)

    result = 0
    for digit in string:
        result *= base
        result += values[symbols.index(digit)]

    return result

T = int(input())
for t in xrange(1, T+1):
    result = solve(raw_input())
    print "Case #%d: %d" %(t, result) 