
# Get number of days in a month

function days($m)
  if ($m == 0) || ($m == 2) || ($m == 4) || 
     ($m == 6) || ($m == 7) || ($m == 9) || ($m == 11) result =  31
  else
    if ($m == 3) || ($m == 5) || ($m == 8) || ($m == 10) result = 30
    else result = 28 end
  end
return result

# Get if a given year is a leap year or not

function leap_year($y) 
  if $y % 4 && $y % 100 && $y % 400 result = false
  else result = true end
return result

# Get the amount of leap seconds from 1972 to a given year

function leap_seconds($y) 
  if $y >= 1972 result = 2 end
  if $y >= 1973 result = result + 1 end
  if $y >= 1974 result = result + 1 end
  if $y >= 1975 result = result + 1 end
  if $y >= 1976 result = result + 1 end
  if $y >= 1977 result = result + 1 end
  if $y >= 1978 result = result + 1 end
  if $y >= 1979 result = result + 1 end
  if $y >= 1981 result = result + 1 end
  if $y >= 1982 result = result + 1 end
  if $y >= 1983 result = result + 1 end
  if $y >= 1985 result = result + 1 end
  if $y >= 1987 result = result + 1 end
  if $y >= 1989 result = result + 1 end
  if $y >= 1990 result = result + 1 end
  if $y >= 1992 result = result + 1 end
  if $y >= 1993 result = result + 1 end
  if $y >= 1994 result = result + 1 end
  if $y >= 1995 result = result + 1 end
  if $y >= 1997 result = result + 1 end
  if $y >= 1998 result = result + 1 end
  if $y >= 2005 result = result + 1 end
  if $y >= 2008 result = result + 1 end
  if $y >= 2012 result = result + 1 end
  if $y >= 2015 result = result + 1 end
  if $y >= 2016 result = result + 1 end
return result

# Get number of seconds since 1 Jan 1970

function epoch($D, $M, $Y, $h, $m, $s, $r)
  if $r == 0 $r = 1 end
  for $i = $Y to 1970
    if leap_year($i) result = result + (366 * 86400)
    else  result = result + (365 * 86400) end
  next
  for $i = 0 to $M - 1
    $D = $D + days($i)
  next
  result = (result + (($D - 1) * 86400) + ($h * 3600) + ($m * 60) + $s) * $r
  # If is January and is a leap year subtract one day (still not occurred)
  if $M == 1 && leap_year($Y) result = result - 86400 end
return result 

# Format 2 digits portions of a date (days, months, hours, minutes and seconds)

function format($day, $dest, $n)
  if $day < 9 
    :[$dest][$n] = '0'
    :[$dest][$n + 1] = '0' + $day
  else 
    :[$dest][$n] = '0' + (($day / 10) % 10)  
    :[$dest][$n + 1] = '0' + ($day % 10)
  end
return 0

# Generate date from epoch

function date($e, $str, locals: $D, $M, $Y, $h, $m, $s, $et, $o)
  $D = $e / 86400
  $Y = 1970
  result = 0
  while $D >= 365
    if leap_year($Y) result = 366 else result = 365 end
    $D = $D - result 
    $e = $e - (86400 * result)
    $Y = $Y + 1
  next
  $D = $D + 1
  for $i = 0 to 12
    if $i == 1 && leap_year($Y)
      if $D - 1 < 0 break end
      --$D 
    end
    if $D - days($i) < 0 break end 
    result = days($i)
    $D = $D - result
    ++$M
    $e = $e - (86400 * result)
  next
  if $D > 0 ++$M end
  $e = $e - (($D - 1) * 86400)
  $h = ($e / 3600)
  $m = ($e % 3600) / 60
  $s = ($e % 3600) % 60
  
  # TODO - Why doesn't work?
  #
  # if $D < 9 
  #   :[$str][0] = '0'
  #   string $D, :[$str], 1 
  # else 
  #   string $D, :[$str]
  # end
  # :[$str][2] = '/'
  # if $M < 9
  #   :[$str][3] = '0'
  #   string $M, :[$str], 4
  # else string $M, :[$str], 3 end
  # :[$str][5] = '/'
  # string $Y, :[$str], 6
  # :[$str][10] = ' '
  # string $h, :[$str], 11
  # :[$str][13] = ':'
  # string $m, :[$str], 14
  # :[$str][16] = ':'
  # string $s, :[$str], 17

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