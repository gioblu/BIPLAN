include "/usr/local/BIPLAN/math.bpl"

print "Example of use of math.bpl functions", char LF

print "Square root of 144: ", sqrt(144), char LF
print "40th number of the fibonacci series: ", fib(40), char LF
print "absolute value of -10: ", abs(-10), char LF
print "is 'A' numeric:  ", numeric('A'), char LF
print "last digit of the number 1239: ", digit(1239, 0), char LF
print "Power of base 12 exponent 2: ", pow(12, 2), char LF
print "17 is a prime number: ", prime(17), char LF
print "Second digit of number 16: ", digit(16, 0), char LF

@sign = sign(-2)

if @sign 
	@sign = '+'
else 
	@sign = '-'
end

print "Sign of -2: ", char @sign, char LF

@prime = prime(10)

print "10 is a prime number: " 

if @prime print "true"
else print "false" end

stop