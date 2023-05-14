
// Common graphics macros and functions
// Giovanni Blu Mitolo 2022

// Change text color

macro TXT_BLACK  system "echo '\033[30m'"
macro TXT_RED    system "echo '\033[31m'"
macro TXT_GREEN  system "echo '\033[32m'"
macro TXT_YELLOW system "echo '\033[33m'"
macro TXT_BLUE   system "echo '\033[34m'"
macro TXT_PURPLE system "echo '\033[35m'"
macro TXT_CYAN   system "echo '\033[36m'"
macro TXT_WHITE  system "echo '\033[37m'"

// Change background color

macro BG_BLACK  system "echo '\033[0;40m'"
macro BG_RED    system "echo '\033[0;41m'"
macro BG_GREEN  system "echo '\033[0;42m'"
macro BG_YELLOW system "echo '\033[0;43m'"
macro BG_BLUE   system "echo '\033[0;44m'"
macro BG_PURPLE system "echo '\033[0;45m'"
macro BG_CYAN   system "echo '\033[0;46m'"
macro BG_WHITE  system "echo '\033[0;47m'"

macro BT_RESET system "echo '\033[0m'"

macro SHOW_CURSOR system "echo '\e[?25h'"
macro HIDE_CURSOR system "echo '\e[?25l'"

// Draw a rectangle at a given x and y position, with a given width and height
function draw_rect($x, $y, $w, $h, $c)
  cursor $x, $y
  for #y = 0 to $h + 1
    for #x = 0 to $w + 1
      if (#x == 0) || (#y == 0) || 
        (#x == $w) || (#y == $h)
        cursor $x + #x, $y + #y
        print char $c
      end
    next
  next
return 0

// Draw a line with Bresenham's line algorithm 
function draw_line($x, $y, $xx, $yy, $c, locals: $dx, $sx, $dy, $sy, $e, $ee)
  $dx =  abs($xx - $x)
  if $x < $xx $sx = 1 else $sx = -1 end
  $dy = -abs($yy - $y)
  if $y < $yy $sy = 1 else $sy = -1 end
    $e = $dx + $dy
  while true
    cursor $x + 1, $y + 1
    print char $c
    if ($x == $xx) && ($y == $yy) break end
    $ee = 2 * $e
    if $ee >= $dy
      $e = $e + $dy
      $x = $x + $sx
    end
    if $ee <= $dx
      $e = $e + $dx
      $y = $y + $sy
    end
  next
return 0

