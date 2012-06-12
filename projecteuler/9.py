from math import sqrt
#a = m^2 - n^2
#b = 2*m*n
#c = m^2+n^2

# a+b+c = 1000
# m^2-n^2 +2*m*n + m^2+n^2 = 1000
# 2m^2 + 2*m*n = 1000
# m^2 + m*n = 500
# m^2 + m*n - 500 = 0
# m(m+n) = 500 with 0 < n < m

m, n = 20, 5

# (m^2-n^2)*2*m*n*(m^2+n^2)
# (m^4-n^4)*2*m*n
# 2*m*n(m^4-n^4)
print(2*m*n*(m**4 - n**4))
