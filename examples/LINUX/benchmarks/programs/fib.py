def fibonacci(n):
 a = 0
 b = 1
 nxt = 0
 for x in range(0, n):
     a = b
     b = nxt
     nxt = a + b
 return nxt

for i in range(100000):
 fibonacci(40)

print(fibonacci(40))
