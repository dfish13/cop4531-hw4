import random

MAX_LIGHT_YEARS = 1
EDGE_RANGE = (3, 8)

n = 0
s = []
starfile = open('stars.txt', 'r')
for star in starfile:
	s = [star.strip()] + s
	n += 1

print(n)
for i in range(n):
	print(s[i], end='')
	for j in range(0, random.randint(*EDGE_RANGE)):
		print(' ', end='')
		print(s[random.randint(0, n-1)], end=' ')
		print(round(random.random()*MAX_LIGHT_YEARS, 3), end='')
	print()
	
