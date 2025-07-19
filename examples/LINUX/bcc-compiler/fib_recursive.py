import datetime

begin_time = datetime.datetime.now()

def fibonacci(n):
   if n <= 1:
       return n
   else:
       return(fibonacci(n-1) + fibonacci(n-2))

print(fibonacci(10))
print(datetime.datetime.now() - begin_time)
