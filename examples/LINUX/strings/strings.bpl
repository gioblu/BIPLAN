include "/usr/local/BIPLAN/strings.bpl"

:s = "This is a test string"

print "Printing entire string: ", :s, char LF


print "Printing string character by character: "

for #i = 0 to size :s
	print char :s[#i]
next

print char LF, "Printing string from \"a\" onwards: "

@p = find_char(:s, 'a')

for #i = @p to size :s
	print char :s[#i]
next

print char LF

stop