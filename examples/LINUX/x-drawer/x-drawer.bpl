
// X drawer, you pass 3, you get:

// X X 
//  X
// X X

// Giovanni Blu Mitolo 2022

print "
X drawer example
Please input resolution between 3 and 9:" 

@res = 0 

while @res < 3 
  @res = input 
  if (@res >= 0) @res = number @res end 
next 

for #y = 0 to @res  
  for #x = 0 to @res
    if #x == #y || (#x + #y == (@res - 1)) print "X" 
    else print " " 
    end 
  next 
  print "
" 
next 

stop

 