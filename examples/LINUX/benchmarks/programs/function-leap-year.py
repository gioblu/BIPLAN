def leap_year(y):
  r = 0
  if(y % 4 == 0 and y % 100 != 0) or (y % 400 == 0):
    r = True
  else:
    r = False
  return r

i = 0
for i in range(100000):
    i = leap_year(i)

