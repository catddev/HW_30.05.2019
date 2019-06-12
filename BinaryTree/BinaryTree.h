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
	Node<T>*& search_prevPtr_helper(Node<T>* cur_ptr, Node<T>* ptr);
public:
	Btree();
	~Btree();
	void add(T el);
	void del(T el);

	void print();

	bool search(T el);
	Node<T>*& search_ptr(T el);
	Node<T>*& search_prevPtr(T el, Node<T>* ptr);
	int getSize();

};

template<typename T>
inline Btree<T>::Btree()
{
	root = 0;
	size = 0;
}

template<typename T>
inline Btree<T>::~Btree()//correct destructor?
{
	if (size != 0)
	{
		int counter = size;//or (size-1)??? not counting root

		while (counter > 0) {
			Node<T>*ptr1l = root->getLeftPtr();
			Node<T>*ptr1r = root->getLeftPtr();
			Node<T>*ptr2l = root->getRightPtr();
			Node<T>*ptr2r = root->getRightPtr();
			while (true) {
				if (ptr1l->getLeftPtr() == 0 && ptr1l->getRightPtr() == 0) {
					ptr1l = 0;
					counter--;
				}
				if (ptr2l->getLeftPtr() == 0 && ptr2l->getRightPtr() == 0) {
					ptr2l = 0;
					counter--;
				}
				if (ptr1r->getLeftPtr() == 0 && ptr1r->getRightPtr() == 0) {
					ptr1r = 0;
					counter--;
				}
				if (ptr2r->getLeftPtr() == 0 && ptr2r->getRightPtr() == 0) {
					ptr2r = 0;
					counter--;
				}
				if (ptr1l == 0 || ptr2l == 0 || ptr1r == 0 || ptr2r == 0)
					break;
				if (ptr1l->getLeftPtr() != 0) ptr1l = ptr1l->getLeftPtr();
				if (ptr1r->getRightPtr() != 0) ptr1r = ptr1r->getRightPtr();
				if (ptr2l->getLeftPtr() != 0) ptr2l = ptr2l->getLeftPtr();
				if (ptr2r->getRightPtr() != 0) ptr2r = ptr2r->getRightPtr();
			}
		}
		root->getLeftPtr() = 0;
		root->getRightPtr() = 0;

		cout << "Destructor!" << endl;//why no pause?
	}
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
inline Node<T>*& Btree<T>::search_prevPtr(T el, Node<T>* ptr)
{
	Node<T>*tmp = 0;

	if (root->getLeftPtr() == ptr || root->getRightPtr() == ptr)
		return root;

	if (el < root->getEl() && root->getLeftPtr() != 0)
		tmp = search_prevPtr_helper(root->getLeftPtr(), ptr);
	else if (el >= root->getEl() && root->getRightPtr() != 0)
		tmp = search_prevPtr_helper(root->getRightPtr(), ptr);

	return tmp;

}

template<typename T>
inline Node<T>*& Btree<T>::search_prevPtr_helper(Node<T>*cur_ptr, Node<T>* ptr)
{
	Node<T>*tmp = 0;
	if (cur_ptr != 0)
		if (cur_ptr->getLeftPtr() == ptr || cur_ptr->getRightPtr() == ptr)
			return cur_ptr;

	if (cur_ptr->getLeftPtr() != 0) {
		tmp = search_prevPtr_helper(cur_ptr->getLeftPtr(), ptr);
	}

	if (tmp == 0) {
		if (cur_ptr->getRightPtr() != 0)
			tmp = search_prevPtr_helper(cur_ptr->getRightPtr(), ptr);
	}
}

template<typename T>
inline void Btree<T>::del(T el)
{
	Node<T>*tmp = 0;
	Node<T>*tmp_prev = 0;
	if (search(el)) {
		tmp = search_ptr(el);
		if (tmp != root)
			tmp_prev = search_prevPtr(el, tmp);
	}
	else {
		cout << "No such an element at the Tree" << endl;
		return;
	}

	if (tmp->getLeftPtr() == 0 && tmp->getRightPtr() == 0) {
		if (tmp == root) {
			delete root;//root = 0 what is the difference?
			size--;
			return;
		}

		if (el < tmp_prev->getEl())
			tmp_prev->getLeftPtr() = 0;
		else
			tmp_prev->getRightPtr() = 0;
	}
	else if (tmp->getLeftPtr() != 0 && tmp->getRightPtr() != 0) {

		Node<T>*newPtr = tmp->getRightPtr();
		while (newPtr->getLeftPtr() != 0)
			newPtr = newPtr->getLeftPtr();

		if (tmp == root) {
			newPtr->getLeftPtr() = root->getLeftPtr();
			root = 0;
			root = newPtr;
			size--;
			return;
		}

		if (newPtr->getRightPtr() != 0)
			tmp->getRightPtr()->getLeftPtr() = newPtr->getRightPtr();

		if (tmp_prev->getLeftPtr() == tmp)
			tmp_prev->getLeftPtr() = newPtr;

		else
			tmp_prev->getRightPtr() = newPtr;


		newPtr->getLeftPtr() = tmp->getLeftPtr();
		if (newPtr != tmp->getRightPtr())
			newPtr->getRightPtr() = tmp->getRightPtr();

	}
	else {
		if (tmp == root) {
			if (tmp->getLeftPtr() != 0) {
				root = 0;
				root = tmp->getLeftPtr();
			}
			else {
				root = 0;
				root = tmp->getRightPtr();
			}
		}

		else if (tmp_prev->getLeftPtr() == tmp)
			if (tmp->getLeftPtr() != 0)
				tmp_prev->getLeftPtr() = tmp->getLeftPtr();
			else
				tmp_prev->getLeftPtr() = tmp->getRightPtr();

		else if (tmp_prev->getRightPtr() == tmp)
			if (tmp->getLeftPtr() != 0)
				tmp_prev->getRightPtr() = tmp->getLeftPtr();
			else
				tmp_prev->getRightPtr() = tmp->getRightPtr();
	}

	delete tmp;// tmp=0 is incorrect???
	size--;
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
	if (size == 0) {
		cout << "Empty Tree!" << endl;
		return;
	}
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