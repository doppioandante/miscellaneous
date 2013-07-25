main = putStrLn $ show result
	where
		result = 
			let upto = 999
			in sumMultiplesUpTo upto 3 + sumMultiplesUpTo upto 5 - sumMultiplesUpTo upto 15 
			
		sumMultiplesUpTo upto m = let n = (upto `div` m) in (`div` 2) $ m * n * (n+1)   
