data = list(input().split())
x = []
counter  = 0
num = data[0]

for i in data:
	frequency = data.count(i)
	if(frequency> counter):
		counter = frequency
		num = frequency


for j in data:
	current_frequency = data.count(j)
	if(current_frequency>= num):
		element = j
		x.append(element)

math = int((len(x) / num))
new_list = list(set(x))
new_list2 = sorted(new_list)

for elem in new_list2:
	print(elem)