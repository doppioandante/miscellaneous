from itertools import combinations_with_replacement


# If I substitute itertools.* with plain loops I get a performance boost, but who cares
def is_palindrome(number):

    toStr = str(number)
    middle = (len(toStr)) // 2
    
    for i in range(0,middle):
        if toStr[i] != toStr[len(toStr) - i - 1]:
            return False

    return True

result = 0
max_digits = 3

# Greatest number with max_digits digits 
upperBound = 10**max_digits - 1
# Lowest number with max_digits digits
lowerBound = 10**(max_digits-1)

for n1, n2 in combinations_with_replacement(reversed(range(lowerBound, upperBound)), 2):
    product = n1 * n2
    if is_palindrome(product):
        result = max(product, result)

print(result)
