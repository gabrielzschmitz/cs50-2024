def checkSize(creditCardNumber):
    size = len(creditCardNumber)
    if int(creditCardNumber[0]) < 1 or int(creditCardNumber[0]) > 9:
        return -1
    if size != 13 and size != 15 and size != 16:
        return -1

    return size


def luhnAlgorithm(creditCardNumber, size):
    addup = 0
    i = size - 1

    while i >= 0:
        if i - 1 >= 0:
            digit = int(creditCardNumber[i - 1]) * 2
            if digit >= 10:
                addup += (digit % 10) + 1
            else:
                addup += digit

        addup += int(creditCardNumber[i])
        i -= 2

    return addup


def printType(creditCardNumber, size):
    number = int(creditCardNumber[0]) * 10 + int(creditCardNumber[1])
    if size == 15 and (number == 34 or number == 37):
        print("AMEX")
    elif size != 15 and int(number / 10) == 4:
        print("VISA")
    elif size == 16 and 51 <= number <= 55:
        print("MASTERCARD")
    else:
        print("INVALID")


def main():
    try:
        creditCardNumber = input("Number: ")

        size = checkSize(creditCardNumber)
        if size == -1:
            print("INVALID")
            return

        if luhnAlgorithm(creditCardNumber, size) % 10 != 0:
            print("INVALID")
            return

        printType(creditCardNumber, size)
    except ValueError:
        print("INVALID")


if __name__ == "__main__":
    main()
