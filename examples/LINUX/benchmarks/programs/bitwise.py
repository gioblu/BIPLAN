
a = 0
b = 2
c = 2
d = 1

for i in range(100000):
    a = i
    d = a ^ b
    d = b | (a + 1)
    d = c & i