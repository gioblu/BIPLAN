import datetime

begin_time = datetime.datetime.now()

def fibonacci(n):
   if n <= 1:
       return n
   else:
       return(recur_fibo(n-1) + recur_fibo(n-2))


for i in range(100000):
 fibonacci(40)

print(fibonacci(40))
print(datetime.datetime.now() - begin_time)
