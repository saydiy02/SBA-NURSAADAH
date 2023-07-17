import math
import threading

def print_fibo():
  a, b = 0, 1
  while a <= 10000:
    print(f"Fibonacci: {a}")
    a, b = b, a+b

def print_sq():
  for c in range(1, 10001):
    print(f"Square: {c*c}")

def print_cb():
  for c in range(1, 10001):
    print(f"Cube: {c*c*c}")

fibo_thread = threading.Thread(target=print_fibo)
sq_thread = threading.Thread(target=print_sq)
cb_thread = threading.Thread(target=print_cb)

fibo_thread.start()
sq_thread.start()
cb_thread.start()

fibo_thread.join()
sq_thread.join()
cb_thread.join()
