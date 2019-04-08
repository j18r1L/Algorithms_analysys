class Node(object): 
    def __init__(self, data): 
    	self.data = data
    	#self.value = value 
    	self.children = [] 

    def add_child(self, obj): 
    	self.children.append(obj) 
#Мама мыла деревянную раму


def main():
	list1 = [["мама мыла"], ["мама деревянную"], ["мама раму"]]
	list2 = [["мыла мама"], ["мыла деревянную"], ["мыла раму"]]
	list3 = [["деревянную мама"], ["деревянную мыла"], ["деревянную раму"]]
	list4 = [["раму мама"], ["раму мыла"], ["раму деревянную"]]


	n = Node(5)
	p = Node(6)
	q = Node(7)
	n.add_child(p)
	n.add_child(q)
	print(n.children)
	print(n.data)

	for c in n.children:
		print(c.data)

if __name__ == '__main__':
	main()
