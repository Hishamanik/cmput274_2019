# Construct a dictionary mapping binary strings to English words

# Use the dictionary to decode the binary string

numberOfElements = int(input())
dictionary = {}

for i in range(numberOfElements):
	key, value = [str(x) for x in input().split()]
	dictionary[key] = value



code = str(input())
x = 0
counter = 1
length = len(code)

for i in range(counter,length+1):
	if code[x:counter] in dictionary:
		print(dictionary[code[x:counter]], end=" ")
		x = counter
	counter += 1