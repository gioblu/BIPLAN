# This program computes 100.000 times the 40th number of the Fibonacci series.
# It is used as an example and to benchmark BIPLAN against python.
# Run also fib.py using python for performance comparison

for $i = 0 to 100000
  fibonacci(40)
next

print fibonacci(40)

stop

function fibonacci($n, locals: $a, $b)
  ++$b
  for $r = 0 to $n
    $a = $b
    $b = result
    result = $a + $b
  next
return result
