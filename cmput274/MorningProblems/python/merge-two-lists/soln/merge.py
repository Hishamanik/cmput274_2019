# Get the input
leftlane = list(input().split())
# now do something similar to get the list of vehicles in the right lane
rightlane = list(input().split())
# Solve the problem
traffic = []
numbersleft = len(leftlane)
numbersright = len(rightlane)
counter = 0
size = 0
size_left = len(leftlane)
size_right = len(rightlane)


# if numbersleft >= numbersright:
# 	for i in range(0,numbersleft):
# 		path = leftlane[counter] + " " + rightlane[counter]
# 		traffic.append(path)
# 		counter +=1
# elif numbersleft < numbersright:
# 	for i in range(0,numbersright):
# 		path = leftlane[counter] + " " +rightlane[counter]
# 		traffic.append(path)
# 		counter +=1

if (size_left < size_right):
	for i in range(size_left):
		path = leftlane[i] + " " + rightlane[i]
		traffic.append(path)
	for j in range(size_left, size_right):
		path = rightlane[j]
		traffic.append(path)

if (size_right < size_left):
	for i in range(size_right):
		path = leftlane[i] + " " + rightlane[i]
		traffic.append(path)
	for j in range(size_right, size_left):
		path = leftlane[j]
		traffic.append(path)

if (size_right == size_left):
	for i in range(size_left):
		path = leftlane[i] + " " + rightlane[i]
		traffic.append(path)

my_list = list(map(str, traffic))
string = " ".join(my_list)
print(string)