import sys

T = int(sys.stdin.readline())

for t in xrange(T):
	palindrome_length = int(sys.stdin.readline())
	print palindrome_length - (palindrome_length%2)
