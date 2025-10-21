def sum(a, b):
 return a + b

for i in range(100000):
 if sum(i, 1) < i:
    print("This string should never appear")

