
# This program computes 100.000 times the 40th number of the Fibonacci series.
# It is used as an example and to benchmark BIPLAN against python.
# Run also fib.py using python for performance comparison

for $i = 1 to 100000
    fibonacci(40)
next
print $next
stop

function fibonacci($n)
  $a    = 0
  $b    = 1
  $next = 0
  for $r = 1 to $n
    $a = $b
    $b = $next
    $next = $a + $b
  next
return $next
