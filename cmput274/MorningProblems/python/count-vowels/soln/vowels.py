# read the input
sentence = input()
# solve the problem
makelist = sentence
vowels = ['a','e','i','o','u', 'A', 'E', 'I','O','U']

count = 0 
for i in makelist:
	if (i in vowels):
		count +=1

# output the result
print(count)