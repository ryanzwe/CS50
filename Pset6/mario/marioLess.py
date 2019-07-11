import cs50

# obtain users requested height
print("Choose a positive height less than 23")
height = cs50.get_int()
while height <= 0 or height > 23:
    height = cs50.get_int("Height: ")
    
# column
for i in range(height):
    # Calculate spaces needed per row
    spaceReq = height - i - 1
    line = ""
    # row
    for j in range(height):
        #If there are spaces required, print nothing instead of a #
        if j < spaceReq:
            line += " "
        else:
            line += "#"
    print(line)