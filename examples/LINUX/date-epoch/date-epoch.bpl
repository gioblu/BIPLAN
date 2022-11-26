
// When the compiler is built BIPLAN the standard library 
// is copied in /usr/local/BIPLAN 
// You can include it from there

include "/usr/local/BIPLAN/time.bpl"

@date_epoch = epoch(10, 10, 2022, 20,35,20)

print "Epoch: ", @date_epoch

:date_string = ""

date(@date_epoch, :date_string)

print " Date: ", :date_string

stop