import logging

# logger=logging.getLogger("MyApp")
# logger.setLevel(logging.DEBUG)

# console_logger=logging.StreamHandler()
# console_logger.setLevel(logging.INFO)
# formatter=logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
# console_logger.setFormatter(formatter)

# logger.addHandler(console_logger)
# def divide(a,b):
#     logger.info(f"Dividing {a} by {b}")
#     try:
#         result=a/b
#         logger.debug(f"Result: {result}")
#         return result
#     except ZeroDivisionError:
#         logger.error("Tried to divide by zero",exc_info=True)
#         #exc_info will log the trace of the exception as well
#         return None

# divide(10, 2)
# divide(5, 0)

gen=(x*x for x in range(10))

print(type(gen))
print(next(gen))
print(next(gen))
print(next(gen))
print(next(gen))    