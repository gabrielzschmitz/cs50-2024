def count_change(cents, coin):
    count = 0
    while cents >= coin:
        cents -= coin
        count += 1
    return count


while True:
    try:
        cents = float(input("Change owed: "))
        if cents >= 0:
            break
    except ValueError:
        print("Invalid input. Please enter a non-negative numeric value.")

cents = round(cents * 100)  # Convert dollars to cents

quarters = count_change(cents, 25)
cents -= quarters * 25

dimes = count_change(cents, 10)
cents -= dimes * 10

nickels = count_change(cents, 5)
cents -= nickels * 5

pennies = count_change(cents, 1)

change_amount = quarters + dimes + nickels + pennies
print(change_amount)
