
# Common mathematical functions
# Giovanni Blu Mitolo 2022

include "/usr/local/BIPLAN/math-constants.bpl"

# Converts radians to degrees
# $r must be a fixed point number, returns a fixed point number 
function rad_to_deg($r)
	return $r * ((180 * precision) / PI)

# Converts degrees to radians
# $d must be a fixed point number, returns a fixed point number 
function deg_to_rad($d)
	return ($d * PI) / (180.0)

# Checks if an ASCII character is numeric (0..9) 
# $v must be an integer, returns true if numeric, false if not numeric
function numeric($v)
	return (($v >= 48) && ($v <= 57))

