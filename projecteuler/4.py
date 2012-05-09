from itertools import combinations_with_replacement, izip

# If I substitute itertools with plain loops, I get a performance boost, but who cares

def is_palindrome(number):
	toStr = str(number)
	
	indices = xrange(0,len(toStr))
	
	for i, j in izip(indices, reversed(indices)):
		if toStr[i] != toStr[j]:
			return False
			
	return True

result = 0
for n1, n2 in combinations_with_replacement(reversed(xrange(100, 999+1)), 2):
	product = n1*n2
	if is_palindrome(product):
		result = max(product, result)
		
print result