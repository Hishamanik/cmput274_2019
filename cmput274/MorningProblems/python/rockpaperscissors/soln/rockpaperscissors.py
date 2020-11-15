num_matches = int(input())
counter = 0
counterA = 0
counterB = 0
counterAlice = 0
counterBob  = 0
for i in range(num_matches):
	x = input().split()
	counter = 0
	for j in x:
		counter += 1
		if 'PR' == x[counter-1] :
			counterA += 1
		elif 'RP' == x[counter-1]:
			counterB +=1
		elif 'RR' == x[counter-1]:
			counterA +=0
		elif 'PP' == x[counter-1]:
			counterB +=0
		elif 'SS' == x[counter-1]:
			counterA +=0
		elif 'PS' == x[counter-1]:
			counterB +=1
		elif 'SP' == x[counter-1]:
			counterA +=1
		elif 'RS' == x[counter-1]:
			counterA +=1
		elif 'SR' == x[counter-1]:
			counterB +=1
	counter = 0

	if counterA > counterB:
		counterAlice += 1
	elif counterA == counterB:
		counterBob += 0
	else:
		counterBob +=1
	counterA =0
	counterB =0
		
if counterA > counterB:
	counterAlice += 1
elif counterA == counterB:
	counterBob += 0
else:
	counterBob +=1



Bob = counterBob
Alice = counterAlice

if counterBob > counterAlice:
	print("Bob", Bob)
elif counterBob < counterAlice:
	print("Alice", Alice)
else:
	print("Alice", Alice)