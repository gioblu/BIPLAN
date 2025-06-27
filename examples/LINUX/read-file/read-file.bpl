
// This program reads and prints itself in the console

@f = file open "read-file.bip", 0
@i = 0

while(@i != EOF)
  @i = file read @f
  print char @i
next

file close @f
stop
