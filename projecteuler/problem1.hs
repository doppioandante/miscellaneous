sumUpTo upto m = let n = (upto `div` m)
		 in (`div` 2) $ m * n * (n+1)

main = print $ sumUpTo 999 3 + sumUpTo 999 5 - sumUpTo 999 15 
			
