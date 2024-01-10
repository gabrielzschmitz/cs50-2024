def count_infos(text):
    letters = sum(c.isalpha() for c in text)
    words = len(text.split())
    sentences = sum(c in ".?!" for c in text)
    return letters, words, sentences


def main():
    text = input("Text: ")

    letters, words, sentences = count_infos(text)

    L = float((letters / words) * 100)
    S = float((sentences / words) * 100)

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print("Grade {}".format(index))


if __name__ == "__main__":
    debug = 0
    main()
