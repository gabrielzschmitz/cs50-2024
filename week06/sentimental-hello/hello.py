"""
Program Description:
--------------------
The hello.py program, located in the sentimental-hello folder, is a simple Python
script that prompts the user for their name and then prints a personalized
greeting. The program utilizes two functions, get_name and hello, to achieve
this functionality.

Implementation Details:
-----------------------
- The get_name function uses the input() function to prompt the user for their
name and returns the entered name as a string.
- The hello function takes a name parameter and prints a greeting message
using an f-string. The greeting format is "Hello, {name}!"
- The program retrieves the user's name using the get_name function and then
invokes the hello function to print the personalized greeting.

Usage:
------
Execute the program by running the command: python hello.py

Note: Provide your name when prompted, and the program will greet you
accordingly.
"""


def get_name():
    return input("What is your name? ")


def hello(name):
    print(f"Hello, {name}!")


name = get_name()
hello(name)
