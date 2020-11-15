number = int(input())
x = list(map(int, input().split()))
y = list(map(int, input().split()))

x.sort()
y.sort()

counter = 0
value = 0
for i in range(0,len(x)):
	value += x[counter]* y[counter]
	counter +=1
print(value)