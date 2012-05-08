
def solve(scores, surprising, treshold):
	if treshold == 0:
		return len(scores)

	possibleScores = 0
	surprisingScores = 0
	for score in scores:
		if score >= treshold + 2*max(0,treshold-1) :
			possibleScores += 1
			
		elif score >= treshold + 2*max(0,treshold-2):
			surprisingScores += 1
			
	return possibleScores + min(surprising, surprisingScores) 

T = input()

for t in xrange(1, T+1):
	data = [int(datum) for datum in raw_input().split()]
	
	assert len(data) >= 4
	
	S = int(data[1])
	p = int(data[2])
	
	scores = data[3:]
	
	print "Case #{0}: {1}".format(t, solve(scores,S,p)) 
