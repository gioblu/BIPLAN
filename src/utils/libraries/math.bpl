
// Common mathematical functions
// Giovanni Blu Mitolo 2023

include "/usr/local/BIPLAN/math-constants.bpl"

// Compute absolute value
function abs($v)
  if $v < 0 $v = -$v end
return $v

// Converts radians to degrees
// $r must be a fixed point number, returns a fixed point number 
function rad_to_deg($r)
	return $r * ((180.0) / PI)

// Converts degrees to radians
// $d must be a fixed point number, returns a fixed point number 
function deg_to_rad($d)
	return ($d * PI) / (180.0)

// Checks if an ASCII character is numeric (0..9) 
// $v must be an integer, returns true if numeric, false if not numeric
function numeric($v)
	return (($v >= 48) && ($v <= 57))

// Computes a number of the fibonacci series
function fibonacci($a, locals: $b)
  $b = 1
  for #r = 0 to $a
    $a = $b
    $b = result
    result = $a + $b
  next
return result
