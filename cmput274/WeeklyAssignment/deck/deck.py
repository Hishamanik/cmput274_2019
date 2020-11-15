#-----------------------------
# Name: Al Hisham Anik
# ID: 1585385
# CMPUT274, Fall 2019
#
#Weekly Exercise 4: Deck
#-----------------------------


#This two import function imports the command line argument and the copy module
import sys
import copy

#This a class storing playing cards
class Deck:
    """
    Stores playing cards
    """
#This method copies the list of cards and initialize the private attribute deck
    def __init__(self, cards):
        '''Initializes attribute for deck of cards
        
        Arguments:
            cards: list of two-character strings representing cards
        '''
        self.__deck = copy.copy(cards)

#This method remove the top card from the deck and return the content
#If there are no cards this method return False       
    def deal(self):
        '''Deals one card from top of deck.
        
        Returns:
            Either the top card (first element in the deck list), or
            False if there are no cards left in the deck
        '''   
        if len(self.__deck) > 0:
            return self.__deck.pop(0)
        else:
            return False   

#This method returns tuple of two values The first value is a Boolean Value 

    def validate(self):
        '''Checks whether the deck is a valid 52 card deck or not.'''
        first = ['2','3','4','5','6','7','8','9','T','J','Q','K','A']     
        second = ['S','D','C','H']
       
       #Returns:
          #'''(is_valid, msg): a tuple containing a Boolean value indicating whether
                           # the deck is valid (True) or not (False), and a string
                            #that is either empty (when deck is valid) or contains
                            #information about why the deck is no valid '''  

#If the first value is valid the second value will be an empty string
#If the deck is not valid then it will return a appropiate message
        if len(self.__deck)<52:
            return (False, "Incomplete deck")    
        elif len(self.__deck)>52:
            return(False, "Deck contains duplicate cards")  
        for card in self.__deck:
            if not(card[0] in first) or not(card[1] in second):
                return(False, "Card is not a valid card".format(card))
        return (True, '')  
#This method return string representation  
    def __str__(self):
        '''Creates custom string to represent deck object
        
        Returns:
           String representation of deck object
        '''         
        length = len(self.__deck)
        Deck_val = ''

        for i in range(0, length-1):
            Deck_val = Deck_val + "{}-".format(self.__deck(i))
        Deck_val = Deck_val + self.__deck[-1]
        return Deck_val

#Main function
if __name__ == "__main__":
    arg = sys.argv
    counting_len_of_argument = len(arg)

#This if else statement checks if the appropriate command line argument has been enterned or not
    if counting_len_of_argument<2:
        print("Too few input arguments! For a valid input argument follow the example as demonstrated below:")
        print("python3 deck.py <file-name>")
        exit()
    elif counting_len_of_argument >2:
        print("Too many arguments! For a valid input argument follow the example as demonstrated below:")
        print("python3 deck.py <file-name>")
        exit()
    else:
#This parts reads the command line argument and also opens the file given as file name
        fname = arg[1]
        fin = open(fname, 'r')
        deck_content = []

#This part formats the file contents
        for i in fin:
            newline = i.strip('\n')
            line_strip = newline.strip()
            line_uppercase = line_strip.upper()
            deck_content.append(line_uppercase)

#this part create an instance for the class 
        cards = Deck(deck_content)
        card_Valid = cards.validate()

        if card_Valid[0] == False:
            print(card_Valid[1])
            exit()
#This part counts the number of cards and determines the number of rounds 
#This also deals when to stop the game
        else:
            first =['2','3','4','5','6','7','8','9','T','J','Q','K','A']
            total_card_numbers = len(deck_content)
            number_of_rounds = total_card_numbers // 2
            for j in range(1,number_of_rounds+1):
                player = cards.deal()
                dealer = cards.deal()

#This part deals with the outcome of the game and declares the result of each round accordingly
                player_point = first.index(player[0])
                dealer_point = first.index(dealer[0])

                if player_point < dealer_point:
                    print("Round {}: Dealer wins!".format(j))
                elif player_point > dealer_point:
                    print("Round {}: Player wins!".format(j))
                else:
                    print("Round {}: Tie!".format(j))

