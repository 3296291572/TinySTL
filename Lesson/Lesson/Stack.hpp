#ifndef TINY_STACK
#define TINY_STACK
#include "Vector.hpp"
#include<iostream>

namespace tinystl
{
	template<typename T,typename Container=vector<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		const T& top()
		{
			return _con.back();
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}
		
		void pop()
		{
			_con.pop_back();
		}
	private:
		Container _con;
	};

}
#endif