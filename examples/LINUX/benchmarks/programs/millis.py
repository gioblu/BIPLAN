import time

incr = 0

for i in range(100000):
    incr = time.time() * 1000

print(incr)