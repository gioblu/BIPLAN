
include "/usr/local/BIPLAN/graphics.bpl"

macro WIDTH  99
macro HEIGHT 33

for #i = 0 to WIDTH * HEIGHT
  mem[#i] = '$' + random 80
next

print restart

@t = TXT_GREEN  
@c = HIDE_CURSOR

for #z = 0 to HEIGHT 
  for #x = 0 to WIDTH
    for #y = 0 to random #z + 1
      cursor #x, #y
      print char mem[#x + (#y * WIDTH)]
    next 
    delay 1
  next
next

@c = SHOW_CURSOR
cursor 0, 35

stop
