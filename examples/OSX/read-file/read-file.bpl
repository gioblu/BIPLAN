
// This program reads and prints itself in the console

@f = file open "read-file.bip", 0
@i = 0

while(true)
  @i = file read @f
  if @i == EOF break end
  print char @i
next

file close @f
stop
