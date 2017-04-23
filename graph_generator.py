import random
import numpy as np

MAX_LIGHT_YEARS = 1
EDGE_RANGE = (3, 8)

array = [1]
for i in range(99):
	array = [0] + array

n = 0
s = []
starfile = open('stars.txt', 'r')
for star in starfile:
	s = [star.strip()] + s
	n += 1

m = np.zeros((n, n))
for i in range(n):
	for j in range(i+1,n):
		if random.choice(array):
			c = round(random.random()*MAX_LIGHT_YEARS, 3)
		else:
			c = 0
		m[i][j] = c
		m[j][i] = c

print(n)
for i in range(n):
	print(s[i], end='')
	for j in range(n):
		if m[i][j] != 0:
			print(' ', end='')
			print(s[j], end=' ')
			print(m[i][j], end='')
	print()
	
