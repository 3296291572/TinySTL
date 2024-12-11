#ifndef TINY_LIST
#define TINY_LIST


#include<iostream>
using namespace std;

namespace tinystl {

template<typename T>
struct ListNode
{
	ListNode<T>* _prev;
	ListNode<T>* _next;
	T _data;

	ListNode(const T& x = T()) :_prev(nullptr), _next(nullptr), _data(x){}
};

template<typename T,typename Ref,typename Ptr>
struct list_iterator
{
	typedef ListNode<T> node;
	typedef list_iterator iterator;
	node* _node;

	list_iterator(node* node)
		:_node(node)
	{}

	iterator operator++()
	{
		_node = _node->_next;
		return *this;
	}

	iterator operator++(int)
	{
		iterator tmp = *this;
		_node = _node->_next;
		return tmp;
	}

	iterator operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	iterator operator--(int)
	{
		iterator tmp = *this;
		_node = _node->_prev;
		return tmp;
	}

	bool operator==(const iterator& it)const
	{
		return _node == it._node;
	}

	bool operator!=(const iterator& it)const
	{
		return _node != it._node;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}
};

template<typename T>
class list {
	typedef ListNode<T> Node;
private:
	Node* _head;
	size_t _size;
public :
	typedef list_iterator<T,T&,T> iterator;
	typedef list_iterator<T, const T&, const T*> const_iterator;
	
	iterator begin()
	{
		return iterator(_head->_next);
	}

	iterator end()
	{
		return iterator(_head);
	}

	const_iterator begin()const
	{
		return const_iterator(_head->_next);
	}

	const_iterator end()const
	{
		return const_iterator(_head);
	}

	void emptyinit()
	{
		_head = new Node();
		_head->_next = _head;
		_head->_prev = _head;
		_size = 0;
	}


	list() {
		emptyinit();
	}


	list(const list& x)
	{
		emptyinit();
		for (auto e : x)
		{
			push_back(e);
		}
	}

	void clear()
	{
		iterator it = begin();
		while (it != end())
		{
			Node* node = it._node;
			it++;
			erase(node);
		}
		_size = 0;
	}

	~list()
	{
		clear();
		delete _head;
		_head = nullptr;
	}

	void Push_back(const T& x)
	{
		Node* newnode = new Node(x);
		Node* tail = _head->_prev;
		tail->_next = newnode;
		newnode->_prev = tail;
		newnode->_next = _head;
		_head->_prev = newnode;
		_size++;
	}
	
	Node* insert(Node* pos, const T& x)
	{
		Node* prev = pos->_prev;
		Node* next = pos->_next;
		Node* newnode = new Node(x);
		newnode->prev = prev;
		newnode->next = next;
		prev->_next = newnode;
		next->_prev = newnode;
		_size++;
		return newnode;
	}

	void erase(Node* pos)
	{
		if (pos == nullptr)return;
		Node* prev = pos->_prev;
		Node* next = pos->_next;
		prev->_next = next;
		next->_prev = prev;
		delete pos;
		_size--;
	}

	void pop_back()
	{
		erase(--end());
	}

	void pop_front()
	{
		erase(begin());
	}
	
	void print_list()
	{
		iterator it = begin();
		while (it != end())
		{
			cout << *it << ' ';
			it++;
		}
		cout << endl;
	}

	int Size()
	{
		return _size;
	}
};
}
#endif