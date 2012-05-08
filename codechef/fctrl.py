from sys import stdin

T = input()

for t in xrange(T):
	value = int( stdin.readline() )
	
	res = 0
	q = 5
	while value:
		value //= q
		res += value
		
	print res

