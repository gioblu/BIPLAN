include "/usr/local/BIPLAN/graphics.bpl"

macro HINT "Press WASD to move the rectangle, press Q to terminate the program"

@x = 5
@y = 5

@c = HIDE_CURSOR

print restart, HINT
draw_rect(@x, @y, 10, 5, 'X')

while true
  @k = input
  if @k == 'q' 
    break
  end
  if @k != 0
     print restart, HINT
     if @k == 'd' ++@x end
     if (@k == 'a') && (@x > 2) --@x end
     if (@k == 'w') && (@y > 2) --@y end
     if @k == 's' ++@y end

     draw_rect(@x, @y, 10, 5, 'X')
  end
next

@c = SHOW_CURSOR

stop
