import main
import time

def tests():
	times = [[0 ,0 ,0]]
	u = 0
	for i in range(1, 3):
		for j in range(100, 201, 100):

			a = [[k for k in range(j)] for l in range(j)]
			b = [[k for k in range(j)] for l in range(j)]

			start1 = time.time()
			main.multiplication(a, b)
			end1 = time.time()
			time_1 = end1 - start1

			start2 = time.time()
			main.vineyard(a, b)
			end2 = time.time()
			time_2 = end2 - start2

			start3 = time.time()
			main.grapefull_vineyard(a, b)
			end3 = time.time()
			time_3 = end3 - start3

			times[u][0] = (time_1 + times[u][0]) / 2
			times[u][1] = (time_2 + times[u][1]) / 2
			times[u][2] = (time_3 + times[u][2]) / 2
			u += 1

	for i in times:
		print(i)
	
			

if __name__ == '__main__':
	tests()