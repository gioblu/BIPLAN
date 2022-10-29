
// This program reads and prints itself in the console

@f = file open "read-file.bip", 0
label @loop
@i = file read @f
if @i != EOF
  print char @i
  jump @loop
end
file close @f
stop
