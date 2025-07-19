
// Common mathematical functions
// Giovanni Blu Mitolo 2024

// Compute absolute value of an integer
function abs($v)
  if $v < 0 $v = -$v end
return $v

// Extract a single digit from an integer value
// $v = value from which the digit should be extracted from
// $n = the position of the digit to be extracted
// ($n = 0 extracts the rightmost digit)
function digit($v, $n)
return ($v / (1 * (($n * 10) + 1))) % 10;

// Checks if an ASCII character is numeric (0..9)
// returns true if numeric, false if not numeric
function numeric($v)
return (($v >= 48) && ($v <= 57))

// Extract sign from integer, returns 1 if positive -1 if negative
function sign($v)
return ($v > 0) - ($v < 0)

// Computes a number of the fibonacci series
function fib($a, locals: $b, $r)
  $b = 1
  for #r = 0 to $a
    $a = $b
    $b = $r
    $r = $a + $b
  next
return $r

// Integer square root (linear search, ascending) using addition
function sqrt($v, locals: $l, $a, $d)
  $l = 0
  $a = 1
  $d = 3
  while ($a <= $v)
    $a = $a + $d  // ($a + 1) ^ 2
    $d = $d + 2
    $l = $l + 1
  next
return $l

// Computes integer power of a base raised to an exponent  
function pow($b, $e, locals: $r)
  if $e == 0 $r = 1 end
  $r = $b
  for #i = 0 to $e - 1
    $r = $r * $b
  next
return $r

// Checks if the given integer is a prime number or not
function prime($n, locals: $r)
  $r = 1  
  for #i = 2 to $n - 1
    if $n % #i == 0 
      $r = 0 
      break
    end
  next
return $r 

