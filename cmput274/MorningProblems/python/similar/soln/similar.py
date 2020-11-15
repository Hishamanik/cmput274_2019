#----------------------------------------
#Name : Al Hisham Anik
#ID: 1585385
#CMPUT 274 , Fall 2019
#Morning Exercise: Similar Movie Scores
#----------------------------------------



# Read in the input
a,b,c = map(int, input().split())

# Solve the problem and output the result
if a == b == c :
	print ('same')
if a==b!=c:
	print('similar')
if a==c!=b:
	print('similar')
if b==c!=a:
	print('similar')
if a!=b and a!=c and b!=c:
	print('distinct')