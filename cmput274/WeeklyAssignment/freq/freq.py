#-----------------------------
# Name: Al Hisham Anik
# ID: 1585385
# CMPUT274, Fall 2019
#
#Exercise 3: Word Frequency
#-----------------------------

#This module imports command line-argument from the bash
import sys
x = []
y = sys.argv

#This if,else statement checks if the input from command-
#line has the desired number of arguments
if len(y) < 2:
	print('There are too few command-line argument')
	print('To process a plain text file e.g textfile you need to type in python3 freq.py textile')
	exit()
elif len(y) >2:
	print('There are too many command-line arguments')
	print('To process a plain text file e.g textfile you need to type in python3 freq.py textile')
	exit()
else:
	fname = y[1]


def readCipher():
	'''This function reads the contents from the input file 
	from the command line '''

	f_in = open(fname, 'r')
	cipher_msg = (f_in.read().strip())
	cipher_msg_updated = (cipher_msg.split())
	f_in.close()
	return cipher_msg_updated

def CountFrequency(fcontent):
	'''This function stores different words from the list
	generated from the file and counts the frequency of the words
	Input: contents from the file
	Output: frequency of each words'''

	length_of_msg = len(fcontent)
	freq = {}

	for items in fcontent:
		freq[items] = fcontent.count(items)
	return freq

def CountRatio(freq):
	''' This function finds out the total number of each unique word 
	from the list and calculate each of the words' ratio 
	Input: frequency dictionry containing each words with their frequency
	Output: Returns the ratio of each unique words'''

	ratio_dict = {}
	total = sum(list(freq.values()))
#This loop is ude to perform ratio count of each words in the frequency list and
#rounds the ratio to 3 decimal places using the round function
	for counter in range(0,len(list(freq.keys()))):
		ratio_dict[list(freq.keys())[counter]] = round(list(freq.values())[counter] / total, 3)
	return ratio_dict

def PrintData(freq, ratio_dict, fname):
	''' This function writes out the frequncy table in a output file 
	The outfile takes in the name of the file that was read and returns
	a file with the same name with an extension out'''

	outfilename = fname + ".out"
	file = open(outfilename, 'w')

#This sorted function sorts the word of the frequency table in lexocographic order
	sequence = list(sorted(freq))

	for element in sequence:
		word = str(element)
		frequency = str(freq[element])
		ratio = str(ratio_dict[element])
		file.write(element +" "+ frequency +" "+ ratio+"\n")

'''Main function'''
if __name__ == '__main__':
	fcontent = readCipher()
	freqcounter = CountFrequency(fcontent)
	ratioCounter = CountRatio(freqcounter)

#Prints the frequency table
	FrequencyTable = PrintData(freqcounter,ratioCounter, fname)