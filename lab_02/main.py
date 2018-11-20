import time

def main():
	#a = [[i for i in range(3)] for j in range(3)]
	#b = [[i for i in range(3)] for j in range(3)]
	a = [[1 ,2, 3], [4, 5, 6], [7, 8, 9]]
	b = [[1 ,2, 3], [4, 5, 6], [7, 8, 9]]
	#start1 = time.time()
	print(multiplication(a, b))
	#end1 = time.time()
	#start2 = time.time()
	print(vineyard(a, b))
	#end2 = time.time()
	#start3 = time.time()
	print(grapefull_vineyard(a, b))
	#end3 = time.time()

	#print(end1 - start1)
	#print(end2 - start2)
	#print(end3 - start3)

def multiplication(a, b):
	length_a = len(a)
	length_b = len(b)
	length_c = length_a + 1
	result = [[0 for i in range(length_a)] for j in range(length_b)]
	#2 + n(2 + m(2 + q(2 + 8)))
	#2 + n(2 + m(2 + 10q))
	#2 + n(2 + 2m + 10mq)
	#2 + 2n + 2mn + 10qmn
	for i in range(length_a): # 2 + n(2 +  body)
		for j in range(length_b): # m(2 + body)
			for k in range(length_a): # q( 2 + 8)
				result[i][j] += a[i][k] * b[k][j] # 8
	return result

def vineyard(a, b):
	lenght_a = len(a) 
	lenght_b = len(b)
	lenght_c = len(b[0])
	
	result = [[0 for i in range(lenght_c)] for j in range(lenght_a)]
	row = [0 for i in range(lenght_a)]
	column = [0 for i in range(lenght_c)]

	for i in range(lenght_a):
		for j in range (0, lenght_b // 2):
			row[i] = row[i] + a[i][2 * j] * a[i][2 * j + 1]

	for i in range(lenght_c):
		for j in range(0, lenght_b // 2):
			column[i] = column[i] + b[2 * j][i] * b[2 * j + 1][i]

	for i in range(lenght_a):
		for j in range(lenght_c):
			result[i][j] = -row[i] - column[j]
			for k in range(lenght_b // 2):
				result[i][j] = result[i][j] + (a[i][2 * k] + b[2 * k + 1][j]) * (a[i][2 * k + 1] + b[2 * k][j])

	if lenght_b % 2:
		for i in range(lenght_a):
			for j in range(0, lenght_c):
				result[i][j] = result[i][j] + a[i][lenght_b - 1] * b[lenght_b - 1][j]

	return result


def grapefull_vineyard(a, b):
	lenght_a = len(a)
	lenght_b = len(b)
	lenght_c = len(b[0])
	
	d = lenght_b // 2
	result = [[0 for i in range(lenght_c)] for j in range(lenght_a)]
	row = [0 for i in range(lenght_a)]
	column = [0 for i in range(lenght_c)]

	for i in range(lenght_a):
		for j in range (d):
			row[i] += a[i][2 * j] * a[i][2 * j + 1]

	for i in range(lenght_c):
		for j in range(d):
			column[i] += b[2 * j][i] * b[2 * j + 1][i]

	for i in range(lenght_a):
		for j in range(lenght_c):
			result[i][j] = -row[i] - column[j]
			for k in range(d):
				index = 2 * k
				result[i][j] += (a[i][index] + b[index + 1][j]) * (a[i][index + 1] + b[index][j])

	if lenght_b % 2:
		for i in range(lenght_a):
			for j in range(0, lenght_c):
				result[i][j] += a[i][lenght_b - 1] * b[lenght_b - 1][j]

	return result


if __name__ == '__main__':
	main()

