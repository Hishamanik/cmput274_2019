# read in the input
x1, y1, x2, y2 = map(int, input().split())
x3, y3, x4, y4 = map(int, input().split())

# now solve the problem. good luck :D

change1_in_y = y2-y1
change1_in_x = x2-x1

change2_in_y  = y4 -y3
change2_in_x = x4 - x3

if change1_in_x == 0 and change2_in_x == 0:
	print("parallel")

else:
	gradient1 = change1_in_y / change1_in_x
	gradient2 = change2_in_y / change2_in_x
	if gradient1 == gradient2:
		print("parallel")
	else:
		print("not parallel")