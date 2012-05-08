T = input() 

for x in xrange(T):
	jewels = set( raw_input() )
	count = 0
	for digit in raw_input():
		if digit in jewels:
			count += 1
	
	print count