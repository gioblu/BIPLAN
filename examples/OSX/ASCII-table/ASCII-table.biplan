
// Prints a readable ASCII table

print restart, char LF, " ASCII TABLE", char LF, char LF, "  32: Spc"

for #i = 33 to 127
  if #i < 100 print " " end
  print #i, ": ", char #i, "  "
  if (#i - 31) % 6 == 0 print char LF, " " end
next

print "127: Del"

stop