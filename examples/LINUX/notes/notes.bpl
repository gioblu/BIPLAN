
print "Notes 0.1 - Giovanni Blu Mitolo 2023", char LF, "Digit note's filename: "
@i = 0
@c = 0
:s = ""
:n = ""

get_string(:n)

@f = file open :n, 4

print "Digit note: "
@c = 0
@i = 0

get_string(:s)

file write @f, :s
file close @f

print "Note saved successfully, bye.", char LF

stop

function get_string($s)
  while @c != LF
    @c = input
    if @c >= 0 
      print char @c
      // Handle character deletion
      if @c == 8 && @i > 0 
        print " ", char @c  
        --@i 
      else 
        :[$s][@i] = @c 
        ++@i 
      end
    end
  next
return 0
