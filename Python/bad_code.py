import pandas as pd
"""Module documentation: This module provides greeting and addition functionality."""
def greet(name):
    """This function is used for greeting by using someone's name"""
    print("Hello " + name)

def add(num1, num2):
    """This function adds two numbers."""
    return num1 +  num2

def unused_func():
    """This function is currently unused."""

greet("World")
print(add(3,  4))
