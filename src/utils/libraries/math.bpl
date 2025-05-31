
// Common mathematical functions
// Giovanni Blu Mitolo 2024

// Compute absolute value
function abs($v)
  if $v < 0 $v = -$v end
return $v

// Checks if an ASCII character is numeric (0..9)
// $v must be an integer, returns true if numeric, false if not numeric
function numeric($v)
	return (($v >= 48) && ($v <= 57))

// Computes a number of the fibonacci series
function fibonacci($a, locals: $b, $r)
  $b = 1
  for #r = 0 to $a
    $a = $b
    $b = $r
    $r = $a + $b
  next
return $r
