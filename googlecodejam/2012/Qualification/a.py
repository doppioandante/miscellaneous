from collections import OrderedDict

translated = "zy qeeour language is impossible to understandthere are twenty six factorial possibilitiesso it is okay if you want to just give up"
original   = "qa zooejp mysljylc kd kxveddknmc re jsicpdrysirbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcdde kr kd eoya kw aej tysr re ujdr lkgc jv"

translation_table = OrderedDict(zip(original, translated))

T = input()

for t in xrange(1, T+1):
	string = raw_input()
	result = "".join([translation_table[x] for x in string])
	
	print "Case #{0}: {1}".format(t, result)