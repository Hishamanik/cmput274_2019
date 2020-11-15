import os.path
fname = input("Enter a filename: ")
while not os.path.isfile(fname):
	print('File doesnot exist')
	fname= input("Enter a filename: ")
fin = open(fname,'r')
for line in fin:
	line= line.strip('\n')
	print(line)
fin.close()