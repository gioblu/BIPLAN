
# When the compiler is built BIPLAN libraries are copied in /usr/local/BIPLAN
# Include them from there

include "/usr/local/BIPLAN/time.bpl" # Includes time library

print "Epoch: ", epoch(29, 3, 2022, 12, 10, 10)

:date = "ciao"

date(epoch(29, 3, 2022, 12, 10, 10), :date)

print " Date: ", :date

stop