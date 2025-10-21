def prime(n):
    r = 1
    for i in range(2, n):
        if n % i == 0:
            r = 0
            break
    return r

c = 0
for i in range(10000):
    c = prime(i)

