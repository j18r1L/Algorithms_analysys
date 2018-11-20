import main
import random
from time import time

def test():
	random_one()
	good_one()
	bad_one()
	

	
#Рандом
def random_one():
	results = []
	result_bubble = 0
	result_gnome = 0
	result_vibor = 0

	for i in range (100, 1001, 100): #Исходные массивы
		array = [(random.randint(0, 10000)) for j in range(i)]
		result_bubble_prev = main.bubble_sort(array)
		result_gnome_prev = main.gnome_sort(array)
		result_vibor_prev = main.vibor_sort(array)
		'''
		for j in range(1): #Кол-во повторяющихся экспериментов
			result_bubble = (main.bubble_sort(array) + result_bubble_prev) / 2
			result_gnome = (main.gnome_sort(array) + result_gnome_prev) / 2
			result_vibor = (main.vibor_sort(array) + result_vibor_prev) / 2
		'''
		results.append([result_bubble_prev, result_gnome_prev, result_vibor_prev])
	print("\nrandom_one")
	for i in range(len(results)):
		print((i + 1) * 100, ";", results[i][0],";",results[i][1],";", results[i][2])

#Наилучший случай
def good_one():
	results = []
	array = []
	for i in range (100, 1001, 100):
		for j in range(i - 99, i + 1):
			array.append(j)
		result_bubble_prev = main.bubble_sort(array)
		result_gnome_prev = main.gnome_sort(array)
		result_vibor_prev = main.vibor_sort(array)
		'''
		for j in range(1): #Кол-во повторяющихся экспериментов
			result_bubble = (main.bubble_sort(array) + result_bubble_prev) / 2
			result_gnome = (main.gnome_sort(array) + result_gnome_prev) / 2
			result_vibor = (main.vibor_sort(array) + result_vibor_prev) / 2
		'''
		results.append([result_bubble_prev, result_gnome_prev, result_vibor_prev])
	print("\ngood_one")
	for i in range(len(results)):
		print((i + 1) * 100, ";", results[i][0],";",results[i][1],";", results[i][2])

#Наихудший случай
def bad_one():
	results = []
	array = []
	for i in range (999, 98, -100):
		for j in range(i + 1, i - 99, -1):
			array.append(j)
		result_bubble_prev = main.bubble_sort(array)
		result_gnome_prev = main.gnome_sort(array)
		result_vibor_prev = main.vibor_sort(array)
		'''
		for j in range(1): #Кол-во повторяющихся экспериментов
			result_bubble = (main.bubble_sort(array) + result_bubble_prev) / 2
			result_gnome = (main.gnome_sort(array) + result_gnome_prev) / 2
			result_vibor = (main.vibor_sort(array) + result_vibor_prev) / 2
		'''
		results.append([result_bubble_prev, result_gnome_prev, result_vibor_prev])
	print("\nbad_one")
	for i in range(len(results)):
		print((i + 1) * 100, ";", results[i][0],";",results[i][1],";", results[i][2])
