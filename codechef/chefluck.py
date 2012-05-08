T = input() 

for x in xrange(T):
	digits = input()
	res = -1 
	
	for x in reversed(xrange(0,digits+1,7)):
		carry = (digits-x)%4
		print carry
		if (digits-x)%4 == 0:
			res = x
			break
			
	print res