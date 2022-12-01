
# BCC compiler implemented in BIPLAN

# Program is stored in memory somehow

@[0] = 'A'
@[1] = '#'
@[2] = '2'
@[3] = 10
@[4] = 0

# Basic BCC functions are tested

print keyword('A'), " ", keyword('0')
print address('$'), " ", address('A')
print in_string(0, 2), " ", in_string(0, 0)
print check_delimeter(0, '"', '"', 0)

remove_comments(0)

remove(0, 'A')

for $i = 0 to 3
  print char @[$i]
next

stop

# Implementation

function keyword($c)
return ($c >= 97) && ($c <= 122) || ($c >= 65) && ($c <= 90) || ($c == 95)

function address($c)
return ($c == 36) || ($c == 58) || ($c == 126) || ($c == 102)

function in_string($prog, $pos, locals: $in_str, $p)
  $p = $prog
  while($pos >= $p)
    if ($pos == $p) && (@[$p] == 34) && not $in_str result = false break end
    if address(@[$p - 1]) ++$p continue end
    if @[$p] == 34 result = not result end
    ++$p
  next
return result

function check_delimeter($prog, $a, $b, $c, locals: $ia, $ib, $p)
  $p = $prog
  while @[$p] != 0
    if not in_string($prog, $p) && not address(@[$p - 1])
      if (@[$p] == $a) ++$ia end
      if ((@[$p] == $b) || (@[$p] == $c)) ++$ib end
    end
    ++$p
  next
  if $ia == $ib return 1 end
return 0

function remove_comments($prog, locals: $i, $j, $in_str)
  if $fail return 0 end
  $i = $prog $j = $prog
  while @[$j] != 0
    @[$i] = @[$j]
    ++$j
    if @[$i] == 34 $in_str = not $in_str end
    if @[$i] != 35
      ++$i
    else
      if $in_str ++$i
      else while (@[$j] != 13) && (@[$j] != 10) ++$j next end
    end
  next
  @[$i] = 0
return 0

function remove($prog, $v, locals: $i, $j, $in_str)
  if $fail return 0 end
  $i = $prog $j = $prog
  while @[$j] != 0
    @[$i] = @[$j]
    ++$j
    if @[$i] == 34 $in_str = not $in_str end
    if @[$i] != $v ++$i else if $in_str ++$i end end
  next
  @[$i] = 0
return 0
