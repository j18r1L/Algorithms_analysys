import random
import tests
from time import time

def main():
	array = [(random.randint(0, 9)) for i in range(100)]
	print(bubble_sort(array))
	print(gnome_sort(array))
	print(vibor_sort(array))
	#tests.test()


def bubble_sort(array):
	length = len(array)
	length1 = length - 1
	start = time()
	#Bad
	#2 + 2n + 12mn
	#Good 
	#2 + 2n + 7mn
	for i in range(length): # 2 + n(2 + )
		for j in range(length1, i, -1): # m(2 + ) 
			index = j - 1 #2
			if array[j] < array[index]: # 3
				array[j], array[index] = array[index], array[j] #5
	end = time() - start
	return end

def gnome_sort(array):
	length = len(array)
	start = time()
	#Good
	#1 + 7n
	#Bad
	#1 + 15n
	i = 1 # 1
	while i < length: # n(1 + )
		if not i or array[i - 1] <= array[i]: #5
			i += 1 # 1
		#Bad
		else:
			array[i], array[i - 1] = array[i - 1], array[i] # 7
			i -= 1 # 1
	end = time() - start
	return end

def vibor_sort(array):
	start = time()
	length = len(array)
	length_1 = length - 1
	#Bad
	#2 + 10n + 6mn
	#Good
	#2 + 10n + 5mn
	for k in range(length_1): #2 + n(2 + )
		m = k #1
		i = k + 1 # 2
		while i < length: #m(1 + )
			if array[i] < array[m]: #3
				m = i #1
			i += 1 #1
		array[k], array[m] = array[m], array[k] #5
	end = time() - start
	return end 

if __name__ == '__main__':
	main()

