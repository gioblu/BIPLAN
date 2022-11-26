// Giovanni Blu Mitolo 2022
// This program saves a test string in memory
// then prints the data from memory

:test_string = "Simplicity is best."

for #i = 0 to size :test_string
	mem[#i] = :test_string[#i]
next

for #i = 0 to size :test_string
	print char mem[#i]
next

stop

