
def main():
	a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
	b = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
	print(a, b)
	print(multiplication(a, b))
	print(vineyard(a, b))
	print(grapefull_vineyard(a, b))

def multiplication(a, b):
	length_a = len(a)
	length_b = len(b)
	result = [[0 for i in range(3)] for j in range(3)]
	for i in range(length_a):
		for j in range(length_b):
			for k in range(length_a):
				result[i][j] += a[i][k] * b[k][j]
	return result

#G размером a x b на матрицу H размером b x c
#G = a
#H = b
#a = len(a) = lenght_a
#b = len(a[0]]) = lenght_b
#b = len(b) = lenght_b
#c = len(b[0]]) = lenght_c

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

