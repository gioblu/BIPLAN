import subprocess

s = "This is a test string.\n"
p = subprocess.Popen(['sh', '-c', 'cat > /tmp/biplan-benchmark-pipes.txt'], stdin=subprocess.PIPE)
for i in range(1000):
    p.stdin.write(s.encode())
p.stdin.close()
p.wait()
