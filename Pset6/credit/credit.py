import cs50

# Function to return an integer into a list
def returnList(cnum):
    cardList = []
    while cnum > 1:
        cardList.insert(0, cnum % 10)
        cnum //= 10
    return cardList


# Function to calculate lunhs sum
def luhnSum(cnum, startIDX, multiplier):
    total = 0
    tempAdd = 0
    #Loop through the card number spacing every second digit, and checking for pdoucts
    for i in range(len(cnum) - startIDX,0,-2):
        tempAdd = cnum[i-1] * multiplier
        if(tempAdd >= 10):
            tempAdd = tempAdd % 10 + (tempAdd//10) % 10
        total += tempAdd
    return total

# Function to return what type of card it is, or invalid if false
def cardType(cardDigits):
    cardLen = len(cardDigits)
    doubles = (cardDigits[0]*10) + cardDigits[1]
    # Visa is either 13 or 16 long, always starting with 4
    if(cardLen == 13 and cardDigits[0] == 4):
        return "VISA"
    # Amex is always 15 long starting with 34 or 37
    if(cardLen == 15):
        if(doubles == 34 or doubles == 37):
            return "AMEX"
    #Visa and Mastercard in this category are 16 long and start with 4, 51, or 55
    if(cardLen == 16):
        if(cardDigits[0] == 4):
            return "VISA"
        if(doubles >= 51 and doubles <= 55):
            return "MASTERCARD"
    return "INVALID"



# Main function to process and return a valid card
def main():
    cnum = cs50.get_int("Number: ")
    cardDigits = returnList(cnum)
    lSum = luhnSum(cardDigits, 1, 2) + luhnSum(cardDigits, 0, 1)
    validCard = (lSum % 10) == 0
    
    if(validCard):
        print(cardType(cardDigits))
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
