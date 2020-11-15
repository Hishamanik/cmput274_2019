numbers = int(input())
l = []
count = 0 
while count<numbers:
	l.append(1)
	if len(l)>=2:
		try:
			while l[-1] == l[-2]:
				v = l[-1]
				del l[-1]
				del l[-1]
				l.append(v+1)
			if l[-1] != l[-2]:
				count+=1
		except:
			count +=1
			continue
	else:
		count+=1

string = ''
for i in range(len(l)-1):
	string = string+str(l[i]) + ' '
string = string + str(l[-1])
print(string)