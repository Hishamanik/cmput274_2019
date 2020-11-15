num_matches = int(input())
counter = 0
counterA = 0
counterB = 0
counterAlice = 0
counterBob  = 0
for i in range(num_matches):
	x = input().split()
	for j in x:
		counter += 1
		if ('PR' == x[counter-1]):
			print('A')
		else:
			print('B')
	counter = 0