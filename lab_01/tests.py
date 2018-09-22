import time
import random
import string
import main

def test():
	word = ''.join(random.choice(string.ascii_lowercase) for x in range(100))
	word.split()
	
	word1 = ['g', 'k']
	word2 = ['g', 'k']
	f1 = open('out1.txt', 'w')
	f2 = open('out2.txt', 'w')
	f3 = open('out3.txt', 'w')
	for i in range(1, 1002, 100):
		print(i)
		start = time.time()
		main.levenshtein(word1, word2)
		end = time.time()
		print('time levenshtein: ', end - start)
		zapis =  str(i - 1) + ' ' + str(int((end - start) * 1000)) + '\n'
		f1.write(zapis)
		start = time.time()
		main.demerau_levenshtein(word1, word2)
		end = time.time()
		print('time demerau_levenshtein: ', end - start, '\n')
		zapis = str(i - 1) + ' ' + str(int((end - start) * 1000)) + '\n'
		f2.write(zapis)
		
		word1 += word
		word2 = word1
	
	for i in range(1, 11):
		word1 = word[:i]
		word2 = word1
		start = time.time()
		main.recursion(word1, word2)
		end = time.time()
		print('time recurs: ', end - start)
		zapis =  str(i) + ' ' + str(int((end - start) * 1000)) + '\n'
		f3.write(zapis)
	
	f1.close()
	f2.close()

if __name__ == '__main__':
	main()

