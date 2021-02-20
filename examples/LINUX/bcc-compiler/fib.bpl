print fibonacci(40)
stop
function fibonacci($n)
  $a    = 0
  $b    = 1
  $next = 0
  $r    = 0
  while $r < $n
    $r = $r + 1
    $a = $b
    $b = $next
    $next = $a + $b
    if $next < 0 return end
  next
return $next
