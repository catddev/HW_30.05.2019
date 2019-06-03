#pragma once;
#include"Node.h"

template<typename T>
class Btree {
	Node<T>* root;
	int size;
	void add_helper(T el, Node<T>*& nodePtr);
	void print_helper(Node<T>* ptr);
	bool search_helper(T el, Node<T>* ptr);
	Node<T>* &search_ptr_helper(T el, Node<T>*ptr);
	Node<T>* &del_helper(Node<T>* ptr);
public:
	Btree();
	//~BTree();
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
inline void Btree<T>::add_helper(T el, Node<T>*& nodePtr)
{
	if (nodePtr == 0) {
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
inline void Btree<T>::del(T el)
{
	Node<T>*tmp = 0;
	if (search(el))
		tmp = search_ptr(el);
	else {
		cout << "No such an element at the Tree" << endl;
		return;
	}

	if (tmp->getLeftPtr() == 0 && tmp->getRightPtr() == 0) {
		tmp = 0;
		delete tmp;//? nullptr //NULL
		size--;
		return;
	}
	else if (tmp->getLeftPtr() != 0 && tmp->getRightPtr() != 0)
		tmp = del_helper(tmp->getRightPtr());
	else {
		if (tmp->getEl() < root->getEl()) {
			if (tmp->getRightPtr() == 0)
				tmp->getPrevPtr()->getLeftPtr() = tmp->getLeftPtr();
			else
				tmp->getPrevPtr()->getLeftPtr() = tmp->getRightPtr();
	}
		else {
			if (tmp->getRightPtr() == 0)
				tmp->getPrevPtr()->getRightPtr() = tmp->getLeftPtr();
			else
				tmp->getPrevPtr()->getRightPtr() = tmp->getRightPtr();
		}
	tmp = NULL;
	size--;
	}
		
}
template<typename T>
inline Node<T>*& Btree<T>::del_helper(Node<T>* ptr)
{
	Node<T>*tmp = 0;
	if (ptr->getLeftPtr() == 0) {
		tmp = ptr;
		//if (ptr->getRightPtr() == 0)
			ptr = NULL;
	/*	else
			ptr->getPrevPtr()->getLeftPtr() = ptr->getRightPtr();*/
		size--;
	}

	else 
		del_helper(ptr->getLeftPtr());
	
	return tmp;
}

template<typename T>
inline void Btree<T>::print_helper(Node<T>* ptr)
{
	static int t = 0;
	t++;
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
	if (root->getLeftPtr() != 0)
		print_helper(root->getLeftPtr());

	if (root != 0)
		cout << root->getEl() << endl;

	if (root->getRightPtr() != 0)
		print_helper(root->getRightPtr());
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

	if (f == false)
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

	if (el < root->getEl() && root->getLeftPtr() != 0)
		f = search_helper(el, root->getLeftPtr());

	//first variant
	/*if (f == false)
		if (root->getRightPtr() != 0)
			f = search_helper(el, root->getRightPtr());*/

	//OR:
	else if (el >= root->getEl() && root->getRightPtr() != 0)
		f = search_helper(el, root->getRightPtr());

	return f;
}

template<typename T>
inline Node<T> *& Btree<T>::search_ptr(T el)
{
	Node<T>*tmp = 0;
	if (el == root->getEl())
		return root;

	if (el < root->getEl() && root->getLeftPtr() != 0)
		tmp = search_ptr_helper(el, root->getLeftPtr());

	//first variant
	//if (tmp == 0)
	//	if (root->getRightPtr() != 0)
	//		tmp = search_ptr_helper(el, root->getRightPtr());

	//OR:
	else if (el >= root->getEl() && root->getRightPtr() != 0)
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

	if (ptr->getLeftPtr() != 0) {
		tmp = search_ptr_helper(el, ptr->getLeftPtr());
	}

	if (tmp == 0) {
		if (ptr->getRightPtr() != 0)
			tmp = search_ptr_helper(el, ptr->getRightPtr());
	}

	return tmp;
}



template<typename T>
inline int Btree<T>::getSize()
{
	return size;
}