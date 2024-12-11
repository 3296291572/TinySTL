#ifndef TING_DEQUEUE
#define TING_DEQUEUE
#include<iostream>

namespace tinystl
{
	template<typename T>
	class dequeue
	{
	public:
		bool isEmpty() const;
		void insertFront(T* o);
		void insertBack(T* o);
		T* removeFront();
		T* removeBack();
		dequeue();
		dequeue(const dequeue& l);
		dequeue& operator=(const dequeue& l);
		~dequeue();
	private:
		struct Node
		{
			Node()
			{
				this->next = nullptr;
				this->prev = nullptr;
				this->o = nullptr;
			}
			Node* next;
			Node* prev;
			T* o;
		};

		Node* first;
		Node* last;
		void makeEmpty();
		void removeAll();
		void copyAll(const dequeue& l);
	};

	template<typename T>
	bool dequeue<T>::isEmpty()const
	{
		return first == nullptr;
	}

	template<typename T>
	void dequeue<T>::insertFront(T* o)
	{
		Node* new_node = new Node();
		
		new_node->o = o;
		if (first == nullptr)
		{
			first = last = new_node;
		}
		else
		{
			first->prev = new_node;
			new_node->next = first;
			first = new_node;
		}
	}

	template<typename T>
	void dequeue<T>::insertBack(T* o)
	{
		Node* new_node = new Node();

		new_node->o = o;
		if (first == nullptr)
		{
			first = last = new_node;
		}
		else
		{
			last->next = new_node;
			new_node->prev = last;
			last = new_node;
		}
	}

	template<typename T>
	T* dequeue<T>::removeFront()
	{
		Node* new_node = new Node();
		T* p = nullptr;

		if (nullptr == first)
		{
			return nullptr;
		}
		new_node = first;
		p = new_node->o;
		first = first->next;
		if (nullptr != first)
		{
			first->prev = nullptr;
		}
		else {
			first = nullptr;
		}
		delete new_node;
		return p;
	}

	template<typename T>
	T* dequeue<T>::removeBack()
	{
		Node* new_node = new Node();
		T* p = nullptr;
		if (nullptr == first)
		{
			return nullptr;
		}

		new_node - last;
		p = last->o;
		last = last->prev;
		if (last != nullptr)
		{
			last->next = nullptr;
		}
		else {
			last = nullptr;
		}
		delete new_node;
		return p;
	}

	template<typename T>
	void dequeue<T>::makeEmpty()
	{
		first = nullptr;
		last = nullptr;
	}

	template<typename T>
	void dequeue<T>::removeAll()
	{
		Node* p = nullptr;
		while (first != nullptr)
		{
			p = first;
			first = first->next;
			delete p;
		}
	}

	template<typename T>
	void dequeue<T>::copyAll(const dequeue& l)
	{
		Node* old_node = nullptr;
		old_node = l.first;
		while (old_node != nullptr)
		{
			insertBack(old_node->o);
			old_node = old_node->next;
		}
	}

	template<typename T>
	dequeue<T>& dequeue<T>::operator=(const dequeue& l)
	{
		dequeue new_copy(l);
		removeAll();
		first = new_copy.first;
		last = new_copy.last;

		new_copy.first = nullptr;
		new_copy.last = nullptr;
		return *this;
	}

	template<typename T>
	dequeue<T>::~dequeue()
	{
		if (!isEmpty())
		{
			removeAll();
		}
	}

	template<typename T>
	dequeue<T>::dequeue()
	{
		makeEmpty();
	}

	template<typename T>
	dequeue<T>::dequeue(const dequeue &l)
	{
		makeEmpty();
		copyAll(l);
	}


}

#endif
