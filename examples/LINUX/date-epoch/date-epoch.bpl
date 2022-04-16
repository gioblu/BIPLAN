
# When the compiler is built BIPLAN libraries are copied in /usr/local/BIPLAN
# Include them from there

include "/usr/local/BIPLAN/time.bpl" # Includes time library

@date_string = epoch(29, 3, 2022, 12, 10, 10)

print "Epoch: ", @date_string

:date_string = ""

date(@date_string, :date_string)

print " Date: ", :date_string

stop