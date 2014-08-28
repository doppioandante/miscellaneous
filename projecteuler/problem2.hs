fibs = 0 : 1 : zipWith (+) fibs (tail fibs)  

main = print $ sum . (filter even) . (takeWhile (\x -> x < 4000000)) $ fibs 
