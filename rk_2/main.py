#items = [('one', 'two'), ('three', 'four'), ('five', 'six'), ('string', 'a')] 

#sorted_items = sorted(items, key=lambda x: x[1][-1]) 
#print(sorted_items)

x = [1, 2, 3, 4, 5] 
x[-1::-2] = [-1, -3, -5] 
#[-5, 2, -3, 4, -1]
print(x)