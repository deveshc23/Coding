from Map_function import User
from Python.Map_function import users

accounts={
    'checking':1958.00,
    'savings':3695.50
}

def add_balance(amount:float,name:str = 'checking')->float:
    """Function to update the balance of an account and return the new balance"""
    accounts[name]+=amount
    return accounts[name]

add_balance(500.00)

print(accounts['checking'])


def create_account(name:str,holder:str,account_holders: list = []):
    account_holders.append(holder)
    return {
        'name':name,
        'main_account_holder':holder,
        'account_holders':account_holders
    }

a1=create_account('checking','Ross')
a2=create_account('savings','Monica')

print(a2)

"""The default parameter gets read when the function is created not when the function is read
    Hence the list gets updated in the second call"""

user_objects=[User(username=data['username'],password=data['password']) for data in users]

user_objects=[User(**data) for data in users]
"""This is a  method for unpacking a dictionary by using **"""

