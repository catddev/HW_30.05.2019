#pragma once;
#include"Node.h"

template<typename T>
class Btree {
	Node<T>* root;
	int size;
	void add_helper(T el, Node<T>*& nodePtr);//PRIVATE METHOD!
	void print_helper(Node<T>* ptr);
	bool search_helper(T el, Node<T>* ptr);
	Node<T>* &search_ptr_helper(T el, Node<T>*ptr);
public:
	Btree();
	void add(T el);
	void del(T el);

	void print();

	bool search(T el);
	Node<T>*& search_ptr(T el);
	int getSize();

};

template<typename T>
inline Btree<T>::Btree()
{
	root = 0;
	size = 0;
}

template<typename T>
inline void Btree<T>::add(T el)
{
	if (root == 0) {
		root = new Node<T>(el);
		size++;
	}
	else {
		if (el < root->getEl()) {
			add_helper(el, root->getLeftPtr());
		}
		else
			add_helper(el, root->getRightPtr());
	}
}

template<typename T>
inline void Btree<T>::del(T el)
{
	Node<T>*tmp = search_ptr(el);
	if (tmp != 0)
		search_ptr(el) = nullptr;
	//delete search_ptr(el);

	/*if(tmp->getPrevPtr()!=0)
		if(el < tmp->getPrevPtr()->getEl())
			tmp->getPrevPtr()->getLeftPtr()
	if ( tmp != 0 && tmp!=root)
			tmp;*/

	size--;
}

template<typename T>
inline void Btree<T>::add_helper(T el, Node<T>*& nodePtr)
{
	if (nodePtr == 0) {//RECURSION!!!
		nodePtr = new Node<T>(el);
		size++;
	}

	else {
		if (el < nodePtr->getEl())
			add_helper(el, nodePtr->getLeftPtr());
		else
			add_helper(el, nodePtr->getRightPtr());
	}
}

template<typename T>
inline void Btree<T>::print_helper(Node<T>* ptr)
{
	static int t = 0;//STATIC!!! to see tree's structure, статик, потому что функция рекурсивная, т.е. каждый раз нужно оставаться на том же значении
	t++;//счетчик для отcтупов
	if (ptr->getLeftPtr() != 0) {
		print_helper(ptr->getLeftPtr());
	}

	for (int i = 0; i < t; i++)
		cout << " ";

	cout << ptr->getEl() << endl;
	if (ptr->getRightPtr() != 0) {
		print_helper(ptr->getRightPtr());
	}
	t--;
}

template<typename T>
inline void Btree<T>::print()
{
	//по возрастанию
	if (root->getLeftPtr() != 0)
		print_helper(root->getLeftPtr());//left part is less

	if (root != 0)
		cout << root->getEl() << endl;//root

	if (root->getRightPtr() != 0)
		print_helper(root->getRightPtr());//right part's elements are larger
}

template<typename T>
inline bool Btree<T>::search_helper(T el, Node<T>* ptr)
{
	bool f = false;//NOT static!!!

	if (ptr != 0)
		if (ptr->getEl() == el)
			return true;

	if (ptr->getLeftPtr() != 0)
		f = search_helper(el, ptr->getLeftPtr());

	//если уже f стал true, то не нужно далее ничего искать!!!
	if (f == false)//обязательное условие, иначе всегда будет по правой части ставить false, даже если в левой уже нашел true
		if (ptr->getRightPtr() != 0)
			f = search_helper(el, ptr->getRightPtr());

	return f;
}

template<typename T>
inline bool Btree<T>::search(T el)
{
	bool f = false;
	if (el == root->getEl())
		return true;

	if (root->getLeftPtr() != 0)
		f = search_helper(el, root->getLeftPtr()); //можно сразу вернуть другую функцию типа булиан!!!!!!!!!!!

	//если уже f стал true, то не нужно далее ничего искать!!!
	if (f == false)//обязательное условие, иначе всегда будет по правой части ставить false, даже если в левой уже нашел true
		if (root->getRightPtr() != 0)
			f = search_helper(el, root->getRightPtr());

	return f;
}

template<typename T>
inline Node<T> *& Btree<T>::search_ptr(T el)
{
	Node<T>*tmp = 0;
	if (el == root->getEl())
		return root;//!

	if (root->getLeftPtr() != 0)
		tmp = search_ptr_helper(el, root->getLeftPtr()); //можно сразу вернуть указатель

	if (tmp == 0)//обязательное условие
		if (root->getRightPtr() != 0)
			tmp = search_ptr_helper(el, root->getRightPtr());

	return tmp;
}

template<typename T>
inline Node<T>*& Btree<T>::search_ptr_helper(T el, Node<T>* ptr)
{
	Node<T>*tmp = 0;
	if (ptr != 0)
		if (ptr->getEl() == el)
			return ptr;

	if (ptr->getLeftPtr() != 0)
		tmp = search_ptr_helper(el, ptr->getLeftPtr());

	//если уже f стал true, то не нужно далее ничего искать!!!
	if (tmp == 0)//обязательное условие, иначе всегда будет по правой части ставить false, даже если в левой уже нашел true
		if (ptr->getRightPtr() != 0)
			tmp = search_ptr_helper(el, ptr->getRightPtr());

	return tmp;
}

template<typename T>
inline int Btree<T>::getSize()
{
	return size;
}