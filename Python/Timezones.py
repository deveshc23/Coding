from datetime import datetime, timezone, timedelta

today=datetime.now(timezone.utc)
tomorrow=today+timedelta(days=1)

print(today.strftime('%d-%m-%Y %H:%M:%S'))

user_date=input("Enter the date")
user_date=datetime.strftime(user_date,'%Y-%m-%d')