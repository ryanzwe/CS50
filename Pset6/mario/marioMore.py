import cs50


def main():
    # Obtain the height value from the issue, and prompt for a new number if it isn't valid
    height = cs50.get_int("Height: ")
    while height <= 0 or height > 23:
        height = cs50.get_int("Height: ")
    # Print out the required white spaces for the jumps alongside the pounds
    for i in range(height):
        for j in range(height):
            PrintStair(j, i, True, height)
        print("  ", end="")
        for j in range(height, 0, -1):
            PrintStair(j-1, i, False, height)
        print("")
    return


# Function to print out the stars or white space
def PrintStair(j, i, drawWhiteSpace, height):
    spacesReq = (height - i - 1)
    if j < spacesReq:
        if(drawWhiteSpace):
            print(" ", end="")
    else:
        print("#", end="")
    return


#Calling the main for the program
if __name__ == "__main__":
    main()
