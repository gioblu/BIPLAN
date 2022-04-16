
# When the compiler is built BIPLAN libraries are copied in /usr/local/BIPLAN
# Include them from there

include "/usr/local/BIPLAN/time.bpl" # Includes time library

@date_epoch = epoch(29, 3, 2022, 12, 10, 10)

print "Epoch: ", @date_epoch

:date_string = ""

date(@date_epoch, :date_string)

print " Date: ", :date_string

stop