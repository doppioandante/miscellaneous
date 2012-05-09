from math import sqrt

T = int(input())

def solve():
		points = int(input())
				
		x, y, z = 0, 0, 0 # coordinates of the center of mass
		vx, vy, vz = 0, 0, 0 # speed 
				
		for i in xrange(points):
				values = [int(value) for value in raw_input().split()]

				x += values[0]
				y += values[1]
				z += values[2]

				vx += values[3]
				vy += values[4]
				vz += values[5]

		# (x+vx(t))^2 + (y+vy(t))^2 + (z+vz(t))^2 =
		# = (vx^2 + vy^2 + vz^2)t^2 + 2(x*xv + y*vy + z*vz)t + (x^2 + y^2 + z^2)
		a = vx**2 + vy**2 + vz**2
		b = 2*(x*vx + y*vy + z*vz)
		c = x**2+y**2+z**2
		tMin = 0
		
		if a != 0:
				tMin = max(-b/(2.0*a), 0)

		dMin = sqrt(tMin*(a*tMin+b)+c)/(float(points))

		return (dMin, tMin)

for t in xrange(1, T+1):
		result = solve()
		print "Case #%s: %.8f %.8f" %(t, float(result[0]), float(result[1]))