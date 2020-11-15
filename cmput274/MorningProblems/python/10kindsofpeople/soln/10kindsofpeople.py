# read the input

a= []
b =[]
x, y = map(int, input().split())
z = list(input())

for i in range (y):
	a_in, b_in = map(int, input().split())
	a.append(a_in)
	b.append(b_in)
# solve the problem
counter = 0
for j in range(y):
	r= a[counter]
	s = b[counter]
	if s ==1:
		numbers = z[0:s]
	else:
		numbers = z[r-1:s]
	if '1' in numbers and '0' in numbers:
		print("both")
	elif '1' in numbers and not('0' in numbers):
		print("one")
	elif '0' in numbers and not('1' in numbers):
		print('zero')
	counter +=1

