#ifndef TINY_VECTOR
#define TINY_VECTOR

#include<iostream>

namespace tinystl
{
	template<typename T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
	public:
		void resize(size_t n, const T& val = T())
		{
			if (n > capacity)
			{
				reserve(n);
			}
			if (n > size())
			{
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* tmp = new T[n];
				size_t sz = size();
				if (_start)
				{
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}
		vector() :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{

		}

		vector(size_t n, const T& val = T()):_start(nullptr),_finish(nullptr),_end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		vector(iterator first, iterator last) :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		vector(const vector<T>& v):_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);
		}

		void swap(vector<T>& v) 
		{
			std::swap(v._start, _start);
			std::swap(v._finish, _finish);
			std::swap(v._end_of_storage, _end_of_storage);
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		bool empty()const
		{
			return _finish == _start;
		}

		void clear()
		{
			_finish = _start;
		}

		size_t size()const
		{
			return _finish - _start;
		}

		size_t capacity()const
		{
			return _end_of_storage - _start;
		}

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}

		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin()const
		{
			return _start;
		}

		const_iterator end()const
		{
			return _finish;
		}

		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2; \
					reserve(newCapacity);
			}
			*_finish = x;
			++_finish;
		}

		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
		}

		void pop_front()
		{
			assert(_finish > _start);
			_start++;
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				size_t  newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = val;
			++_finish;
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;
			return pos;
		}

		T back()
		{
			return *(_finish-1);
		}
		
		T front()
		{
			return *_start;
		}
	private:
		T* _start;
		T* _finish;
		T* _end_of_storage;
	};

}

#endif TINY_VECTOR