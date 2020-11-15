#--------------------------
#Name: Al Hisham Anik
#ID: 1585385
#CMPUT 274, Fall 2019
#Assignment-1: Validator 
#--------------------------

#Function that analyzes an input password to determine if the password is
#Secure,Insecure or Invalid
def validate(password):

	#Variables which includes character that should 
	#or should not contain in the password string
	special_character = ['!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '`', '{', '|', '}', '~']
	forbidden_character= ['', '_','-']

	#Variables included to ease the use of print statement
	value = 'Secure'
	Invalid = 'Invalid'
	Insecure = 'Insecure'
	
	if len(password) < 8:
		return Invalid

	if len(password) > 8:
		if any(char in forbidden_character for char in password):
			return Invalid
		if not any(char in special_character for char in password):
			return Insecure
		if not any(char.isupper() for char in password):
			return Insecure
		if not any(char.islower() for char in password):
			return Insecure
		if not any(char.isdigit() for char in password):
			return Insecure
	return value

#  Main code containg input string of password
if __name__ == "__main__":
	print(validate("helloworld!"))


#Part Two

#This function generates a password of length n
def generate(n):
	special_character = ['!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '`', '{', '|', '}', '~']
	import random
	import string

# Only if the length specified by the user input is greater than 8 
#then only the function evaluate	
	if n > 8:
		for i in range(n):
			Secured_password = string.ascii_letters + string.digits + random.choice(special_character)
			password = ''.join(random.choice(Secured_password) for i in range (n))
		return password

#  Main Code containing user input which asks for desire length of password required
if __name__ == "__main__":
	print(generate(50))