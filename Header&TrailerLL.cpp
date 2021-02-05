#include <iostream>

using namespace std;

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};

template <class Type>
class HeaderTrailerLinkedList
{
	private:
		nodeType<Type> *header;
		nodeType<Type> *trailer;
		nodeType<Type> *first;
		int count;
		
	public:
		HeaderTrailerLinkedList();
		void initializeList();
		bool isEmptyList() const;
		void destroyList();
		void print() const;
		int length() const;
		bool search(const Type& searchItem) const;
		void insert(const Type& insertItem);
		void deletenode(const Type& deleteItem);
		void copyList(const HeaderTrailerLinkedList<Type>& otherList);
};

template <class Type>
HeaderTrailerLinkedList<Type>::HeaderTrailerLinkedList() 
{
	header = new nodeType<Type>;
	trailer = new  nodeType<Type>;
	first = new nodeType<Type>;
	first->link = header;
	header->link = trailer;
	trailer->link = NULL;
	count = 0;
}
template <class Type>
int HeaderTrailerLinkedList<Type>::length() const 
{
	return count;
}

template <class Type>
void HeaderTrailerLinkedList<Type>::initializeList()
{
	destroyList();
}

template <class Type>
void HeaderTrailerLinkedList<Type>::deletenode(const Type& deleteItem)
{
	if(!isEmptyList())
    {
		nodeType<Type> *current, *trailcurrent;
		current = header->link;
		trailcurrent = header; 
		while(current != trailer)
		{
			if(current->info == deleteItem) 
			{
				trailcurrent->link = current->link;
				delete current;
				count--;
				break;
			}
			trailcurrent = current;
			current = current->link;
		}
	}
}

template <class Type>
void HeaderTrailerLinkedList<Type>::destroyList()
{
	if(!isEmptyList())
    {
		nodeType<Type> *current, *temp;
		current = header->link;
		while(current != trailer)
		{
			temp = current->link;
			delete current;
			current = temp;
		}
		header->link = trailer;	
	}
}
template <class Type>
void HeaderTrailerLinkedList<Type>::insert(const Type& insertItem)
{
	nodeType<Type> *newnode = new nodeType<Type>;
	newnode->info = insertItem;
	if(header->info <= insertItem || header->link == trailer)
	{
		if(header->link == trailer) trailer->info = insertItem-1;
		header->info = insertItem+1;
		newnode->link = header->link;
		header->link = newnode;
	}
	else
	{
		nodeType<Type> *current, *trailcurrent;
		current = header->link;
		trailcurrent = header;
		while(current != trailer)
		{
			if(current->info <= insertItem)
			{
				newnode->link = current;
				trailcurrent->link = newnode;
				break;
			}
			trailcurrent = current;
			current = current->link;
		}
		if(current == trailer)
		{
			newnode->link = trailer;
			trailcurrent->link = newnode;
			trailer->info = insertItem-1;
		}		
	}
	count++;
}

template <class Type>
bool HeaderTrailerLinkedList<Type>::search(const Type& searchItem) const
{
    if(!isEmptyList())
    {
		nodeType<Type> *current;
		current = header->link; 
		while(current != trailer)
		{
			if(current->info == searchItem) return true;
			current = current->link;
		}
		return false;
	}
}

template <class Type>
bool HeaderTrailerLinkedList<Type>::isEmptyList() const
{
	return (header == NULL);
}
template <class Type>
void HeaderTrailerLinkedList<Type>::print() const
{
    if(!isEmptyList())
    {
    	cout << "Header: " << header->info << endl;
		nodeType<Type> *current;
		current = header->link;
		cout << "List: ";
		while(current != trailer)
		{
			cout << current->info << " ";
			current = current->link;
		}
		cout << endl;
		cout << "Trailer: " << trailer->info;    
    }
}
template <class Type>
void HeaderTrailerLinkedList<Type>::copyList(const HeaderTrailerLinkedList<Type>& otherList)
{
	nodeType<Type> *current, *trailcurrent;
	header->info = otherList.header->info;
	current = otherList.header->link;
	trailcurrent = header;
	while(current != otherList.trailer)
	{
		nodeType<Type> *newnode = new nodeType<Type>;
		newnode->info = current->info;
		trailcurrent->link = newnode;
		trailcurrent = newnode;
		current = current->link;
	}
	trailcurrent->link = trailer;
	trailer->info = otherList.trailer->info;
}
int main()
{
	HeaderTrailerLinkedList<int> C;
	C.insert(22);
	C.insert(56);
	C.insert(18);
	C.insert(25);
	C.print();
	C.destroyList();
	cout << endl;
	C.print();
	C.insert(57);
	C.insert(45);
	C.insert(48);
	C.deletenode(45);
	cout << endl;
	C.print();
	HeaderTrailerLinkedList<int> D;
	D.copyList(C);
	cout << endl;
	D.print();
	return 0;
}
