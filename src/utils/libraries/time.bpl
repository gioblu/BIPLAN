

function is_leap($year) 
  if $year % 4 && $year % 100 && $year % 400 result = false
  else result = true end
return result

function new_epoch($D, $M, $Y, $h, $m, $s, $r)
  if $r == 0 $r = 1 end
  for $i = $Y to 1970
    if is_leap($i) result = result + (366 * 86400)
    else  result = result + (365 * 86400) end
  next
  for $i = 0 to $M - 1
    if ($i == 0) || ($i == 2) || ($i == 4) || 
       ($i == 6) || ($i == 7) || ($i == 9) || ($i == 11) $D = $D + 31
    else
      if ($i == 3) || ($i == 5) || ($i == 8) || ($i == 10) $D = $D + 30
      else $D = $D + 28 end
    end
  next
  result = (result + (($D - 1) * 86400) + ($h * 3600) + ($m * 60) + $s) * $r
return result 