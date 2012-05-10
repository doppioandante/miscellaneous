# 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89
# ^        ^        ^          ^
# 2 | F(k*3) holds for k  >= 0
# Base case: 2 | 0
# Inductive hypotesis: 2 | F(k*3)
# 2 | F((k+1)*3 )
# 2 | F(3k+3)
# 2 | F(3k+2) + F(3k+1)
# 2 | F(3k+1) + F(3k) + F(3k+1)
# 2 | 2*F(3k+1) + F(3k) ; 2|2*F(3k+1) and F(3k) (for inductive hypotesis)
# then 2 | F(k*3)

# F(3k) = F(3k-1) + F(3k-2) = F(3k-2) + F(3k-3) + F(3k-2) =
# = 2*F(3k-2) + F(3k-3) = 2*[F(3k-3)+F(3k-4)] + F(3k-3) =
# = 3*F(3k-3) + 2*[F(3k-4)] = 3*F(3k-3) + (F(3k-4) + F(3k-5)) +F(3k-6) =
# = 4*F(3k-3) + F(3k-6) = 4*F(3(k-1)) + F(3(k-2))
# EF(n)=F(n/3) -> E(n) = 4*E(n-1) + E(n-2)


limit = 4000000

a = 0
b = 2
sum = 0

while a < limit:
    sum += a
    a, b = b, 4*b+a

print sum
