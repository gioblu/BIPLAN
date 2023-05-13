include "/usr/local/BIPLAN/math.bpl"

// Constant value test

@v = PI
print "Value of PI is: ", fixed @v, "
"

// Compute square root of 2

print "Square root of 2: ", fixed sqrt 2.0, "
"

// Compute degrees to radians converison

print "45 degrees in radians: ", fixed deg_to_rad(45.0), "
"

// Compute sin(45.0)

print "Sin of 45 degrees: ", fixed sin deg_to_rad(45.0), "
"

// Compute sin(90.0)

print "Sin of 90 degrees: ", fixed sin deg_to_rad(90.0), "
"

// Compute cos(45.0)

print "Cos of 45 degrees: ", fixed cos deg_to_rad(45.0), "
"

// Compute cos(90.0)

print "Cos of 90 degrees: ", fixed cos deg_to_rad(90.0), "
"

// Compute tan(45.0)

print "Tan of 45 degrees: ", fixed tan deg_to_rad(45.0), "
"

// Compute tan(10.0)

print "Tan of 10 degrees: ", fixed tan deg_to_rad(10.0), "
"

stop