from math import sqrt

T = int(input())

def solve():
		points = int(input())
		
		xSum, ySum, zSum = 0, 0, 0
		vxSum, vySum, vzSum = 0, 0, 0
		
		for i in xrange(points):
				values = [int(x) for x in raw_input().split()]
				
				xSum += values[0]
				ySum += values[1]
				zSum += values[2]
				
				vxSum += values[3]
				vySum += values[4]
				vzSum += values[5]

		# (a+d(t))^2 + (b+e(t))^2 + (c+f(t))^2 =
		# = a^2 + b^2 + c^2 + 2t*(a*d + b*t + c*f) + t^2*(d+e+f)
		a = vxSum**2 + vySum**2 + vzSum**2
		b = 2*(xSum*vxSum + ySum*vySum + zSum*vzSum)
		c = xSum**2+ySum**2+zSum**2
		tMin = 0
		
		if a != 0:
			tMin = max(-b/(2.0*a), 0)

		dMin = sqrt(tMin*(a*tMin+b)+c)/(float(points))
		
		return (dMin, tMin)

for t in xrange(1, T+1):
		result = solve()
		print "Case #%s: %.8f %.8f" %(t, float(result[0]), float(result[1]))