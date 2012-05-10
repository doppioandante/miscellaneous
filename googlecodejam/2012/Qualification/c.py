import cStringIO
import sys

#sys.stdout = cStringIO.StringIO()

def shift(number,length):
    firstDigit = number // 10**(length-1)

    return (firstDigit + number*10) - firstDigit*10**length

def solve(A, B):
    numberLength = len(str(A))
    assert numberLength == len(str(B))

    lookup = set()

    count = 0
    for number in xrange(A, B+1):
        if number in lookup:
            continue

        original = number

        recycled = 1
        while True:
            number = shift(number, numberLength)

            if number == original:
                break

            if original < number <= B:
                assert number not in lookup
                recycled += 1
                lookup.add( number )

        count += recycled*(recycled-1)/2


    return count


T = input()
for t in xrange(1, T+1):
    A, B = [int(x) for x in raw_input().split()]

    print "Case #{0}: {1}".format(t, solve(A,B))


#sys.__stdout__.write(sys.stdout.getvalue())