
counter = 0
x_in, y_in= map(int, input().split())
Jar = 0
a = []
b =[]
for i in range (y_in):
	a_in, b_in= map(int, input().split())
	a.append(a_in)
	b.append(b_in)

for j in (b):
	x = a[counter]
	y = b[counter]
	if (y -x) < x_in:
		Jar +=0
	else:
		Jar +=1
	counter +=1
print(Jar)

