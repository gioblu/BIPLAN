def factorial(n):
   result = 1
   for i in range(2, n + 1):
      result *= i
   return result 


for i in range(100000):
   factorial(20)