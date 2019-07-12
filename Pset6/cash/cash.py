import cs50


def main():
    # Obtain the users money and check its over 0.00
    inputMoney = cs50.get_float("Change Owed: ")
    if inputMoney <= 0:
        inputMoney = cs50.get_float()
    # Convert the users money into cents
    inputMoney *= 100
    changeOwed = HandleChange(inputMoney)
    print(changeOwed)
    return


# Function to return the lowest needed quantity back to the user
def HandleChange(inputMoney):
    coins = [25, 10, 5, 1]
    returnMoney = 0
    i = 0
    while i < 4:
        if coins[i] <= inputMoney:
            inputMoney -= coins[i]
            returnMoney += 1
            i = 0
        else:
            i += 1
    return returnMoney


if __name__ == "__main__":
    main()
