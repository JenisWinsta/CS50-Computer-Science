from cs50 import get_int  # import statements

height = get_int("Height: ")

# input check
while (height < 1 or height > 8):
    height = get_int("Height: ")

# conditionals
if height > 0 and height < 9:
    for i in range(height):
        for j in range(height):
            if (i+j+1) < height:
                print(" ", end="")
            else:
                print("#", end="")
        print()
