

// Get number of days in a month
// $m must be an integer, returns an integer
function days($m, locals: $r)
  if ($m == 0) || ($m == 2) || ($m == 4) ||
    ($m == 6) || ($m == 7) || ($m == 9) || ($m == 11) $r =  31
  else
    if ($m == 3) || ($m == 5) || ($m == 8) || ($m == 10) $r = 30
    else $r = 28 end
  end
return $r

// Get if a given year is a leap year or not
// $y must be an integer, returns an integer
function leap_year($y, locals: $r)
  if $y % 4 && $y % 100 && $y % 400 $r = false
  else $r = true end
return $r

// Get number of seconds since 1 Jan 1970
// All parameters must be integers, returns an integer
function epoch($D, $M, $Y, $h, $m, $s, locals: $r)
  for #i = $Y to 1970
    if leap_year(#i) $r = $r + (366 * 86400)
    else  $r = $r + (365 * 86400) end
  next
  for #i = 0 to $M - 1
    $D = $D + days(#i)
  next
  $r = ($r + (($D - 1) * 86400) + ($h * 3600) + ($m * 60) + $s)
  // If is January and is a leap year subtract one day (still not occurred)
  if $M == 1 && leap_year($Y) $r = $r - 86400 end
return $r

// Format 2 digits portions of a date (days, months, hours, minutes and seconds)
// All parameters must be integers, returns an integer
function format($day, $dest, $n)
  if $day < 9
    :[$dest][$n] = '0'
    :[$dest][$n + 1] = '0' + $day
  else
    :[$dest][$n] = '0' + (($day / 10) % 10)
    :[$dest][$n + 1] = '0' + ($day % 10)
  end
return 0

// Generate date from epoch
// $e must be an integer, $str must be a reference to a string
function date($e, $str, locals: $D, $M, $Y, $h, $m, $s, $r)
  $D = $e / 86400
  $Y = 1970
  $r = 0
  while $D >= 365
    if leap_year($Y) $r = 366 else $r = 365 end
    $D = $D - $r
    $e = $e - (86400 * $r)
    $Y = $Y + 1
  next
  $D = $D + 1
  for #i = 0 to 12
    if #i == 1 && leap_year($Y)
      if $D - 1 < 0 break end
      --$D
    end
    if $D - days(#i) < 0 break end
    $r = days(#i)
    $D = $D - $r
    ++$M
    $e = $e - (86400 * $r)
  next
  if $D > 0
    ++$M
    $e = $e - (($D - 1) * 86400)
  else $e = $e - 86400 end
  if leap_year($Y) && ($M > 1) $e = $e - 86400 end
  $h = ($e / 3600)
  $m = ($e % 3600) / 60
  $s = ($e % 3600) % 60
  format($D, $str, 0)
  :[$str][2] = '/'
  format($M, $str, 3)
  :[$str][5] = '/'
  :[$str][6] = '0' + (($Y / 1000) % 10)
  :[$str][7] = '0' + (($Y / 100) % 10)
  :[$str][8] = '0' + (($Y / 10) % 10)
  :[$str][9] = '0' + ($Y % 10)
  :[$str][10] = ' '
  format($h, $str, 11)
  :[$str][13] = ':'
  format($m, $str, 14)
  :[$str][16] = ':'
  format($s, $str, 17)
return $str