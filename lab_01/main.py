import time
import tests
import PIL

def main():
	word1 = enter()
	word2 = enter()
	if len(word1) < len(word2):
		word1, word2 = word2, word1
	print()

	result_mtr = levenshtein(word1, word2)
	print('result levenshtein: ', result_mtr, '\n')


	mtr = demerau_levenshtein(word1, word2)
	print('demerau_levenshtein: ', mtr, '\n')


	start = time.time()
	result_rec = recursion(word1, word2)
	end = time.time()
	print('time recurs: ', end - start)
	print('recurs: ', result_rec, '\n')
	tests.test()

def enter():
	symbol = str(input('Enter word: '))
	while (len(symbol) == 0):
		print('Entered word empty!')
		symbol = str(input('Enter word: '))
	symbol = '1' + symbol
	return symbol

def levenshtein(word1, word2):
	array = [i for i in range(len(word1))]
	result_array = [1]
	print(array)
	start = time.time()
	for i in range(1, len(word2)):
		for j in range(1, len(word1)):
			if (word2[i] == word1[j]):
				result = min(array[j - 1], array[j] + 1, result_array[j - 1] + 1)
			else:
				result = min(array[j - 1] + 1, array[j] + 1, result_array[j - 1] + 1)
			result_array.append(result)
		array = result_array
		print(result_array)
		result = result_array[-1]
		result_array = [i + 1]
	end = time.time()
	print('time matrix: ', end - start)
	return result

def demerau_levenshtein(word1, word2):
	l1, l2 = len(word1), len(word2)
	mtr = [[0 for x in range(l2)] for y in range(l1)]
	for i in range(l1):
		for j in range(l2):
			mtr[0][j] = j
			mtr[i][0] = i
	start = time.time()
	for i in range(1, l1):
		for j in range(1, l2):
			if (i > 1) and (j > 1) and (word1[i] == word2[j - 1]) and (word1[i - 1] == word2[j]) and (word1[i] == word2[j]):
				mtr[i][j] = min(mtr[i - 1][j] + 1, mtr[i][j - 1] + 1, mtr[i - 1][j - 1], mtr[i - 2][j - 2] + 1)
			elif (i > 1) and (j > 1) and (word1[i] == word2[j - 1]) and (word1[i - 1] == word2[j]) and (word1[i] != word2[j]):
				mtr[i][j] = min(mtr[i - 1][j] + 1, mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + 1, mtr[i - 2][j - 2] + 1)
			elif word1[i] == word2[j]:
				mtr[i][j] = min(mtr[i - 1][j] + 1, mtr[i][j - 1] + 1, mtr[i - 1][j - 1])
			elif word1[i] != word2[j]:
				mtr[i][j] = min(mtr[i - 1][j] + 1, mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + 1)

	end = time.time()
	for i in range(l1):
		for j in range(l2):
			print(mtr[i][j], end=' ')
		print()
	print('time demerau_lev: ', end - start)
	return mtr[i][j]


def recursion(word1, word2):
	l1 = len(word1)
	l2 = len(word2)
	if l1 == 0 or l2 == 0:
		return max(l1,l2)
	if word1[-1] == word2[-1]:
		result = min([recursion(word1[:-1], word2) + 1, recursion(word1, word2[:-1]) + 1, recursion(word1[:-1], word2[:-1])])
	else:
		result = min([recursion(word1[:-1], word2) + 1, recursion(word1, word2[:-1]) + 1, recursion(word1[:-1], word2[:-1]) + 1])
	return result

if __name__ == '__main__':
	main()

