import random

MAX_WEIGHT = 100


d = dict()
s = []
fin = open('b.txt', 'r')
n = int(fin.readline())
for i in range(n):
	vert = fin.readline().strip()
	d[vert] = i
	s = [vert] + s

print(n)
for i in range(n):
	print(s[i], end='')
	for j in range(0, random.randint(20, 50)):
		print(' ', end='')
		print(s[random.randint(0, n-1)], end=' ')
		print(round(random.random()*MAX_WEIGHT, 3), end='')
	print()
	
