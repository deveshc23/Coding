import functools
import time
import logging
from typing import Callable, TypeVar, Any, cast
logger=logging.getLogger(__name__)
F = TypeVar('F', bound=Callable[..., Any])
def timer(func:F)->F:
    @functools.wraps(func)
    def wrapper(*args,**kwargs):
        start_time=time.time()
        print("Before function call")
        func(*args, **kwargs)
        print("After function call")
        end_time = time.time()
        print(f"Function {func.__name__} took {end_time - start_time:.4f} seconds to run")
    return cast(F, wrapper)

@timer
def multiplication(a:int,b:int)->int:
    time.sleep(2)
    print(a*b)

if __name__ == "__main__":
    multiplication(5, 10)