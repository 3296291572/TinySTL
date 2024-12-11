#ifndef TING_STRING
#define TING_STRING

#include<iostream>
#include <cassert>

namespace tinystl {

class string
{
private:
	size_t _size;
	size_t _capacity;
	char* _str;
	const static size_t npos = -1;
public:
	typedef char* iterator;

	string(const char* str = "")
	{
		_size = strlen(str);
		_capacity = _size;
		
		_str = new char[_capacity+1];
		strcpy_s(_str, _capacity+1, str);
	}

	string(const string& s):_str(nullptr),_size(0),_capacity(0)
	{
		string tmp(s._str);
		this->swap(tmp);
	}

	void swap(string& s)
	{
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

	string& operator=(string s)
	{
		swap(s);
		return *this;
	}

	~string()
	{
		delete[] _str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	iterator begin()const
	{
		return _str;
	}

	iterator end()const
	{
		return _str + _size;
	}

	size_t size()const
	{
		return _size;
	}

	size_t capacity()const
	{
		return _capacity;
	}

	void reserver(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy_s(tmp, n+1, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}

	void resize(size_t n, char ch = '\n')
	{
		if (n > _size)
		{
			reserver(n);
			for (size_t i = _size; i < n; i++)
			{
				_str[i] = ch;
			}
			_size = n;
			_str[_size] = '\n';
		}
		else {
			_str[n] = '\n';
			_size = n;
		}
	}

	void clear()
	{
		_size = 0;
		_str[0] = '\n';
	}

	char& operator[](size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}

	char& operator[](size_t pos)const
	{
		assert(pos < _size);
		return _str[pos];
	}

	void push_back(char ch)
	{
		if (_size == _capacity)
		{
			size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
			reserver(newCapacity);
		}
		_str[_size] = ch;
		_size++;
		_str[_size] = '\n';
	}

	void append(const char* str)
	{
		size_t len = strlen(str);

		if (_size + len > _capacity)
		{
			reserver(_size + len);
		}

		strcpy_s(_str + _size,_capacity-_size+1, str);
		_size += len;
	}

	string& operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}

	string& operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	string& insert(size_t pos, char ch)
	{
		assert(pos <= _size);

		if (_size == _capacity)
		{
			size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
			reserver(newCapacity);
		}
		size_t end = _size;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		_str[pos] = ch;
		_size++;
		return *this;
	}

	string& insert(size_t pos,const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserver(_size + len);
		}

		size_t end = _size;
		while (end > pos)
		{
			_str[end + len-1] = _str[end-1];
			end--;
		}

		for (size_t i = end; i < end + len; i++)
		{
			_str[i] = str[i - end];
		}
		//strcpy_s(_str + end, len ,str);
		_size += len;
		return *this;
	}

	string& insert(size_t pos, char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserver(_size + len);
		}

		size_t end = _size;
		while (end > pos)
		{
			_str[end + len - 1] = _str[end - 1];
			end--;
		}

		for (size_t i = end; i < end + len; i++)
		{
			_str[i] = str[i - end];
		}
		//strcpy_s(_str + end, len ,str);
		_size += len;
		return *this;
	}

	string& erase(size_t pos, size_t len = npos)
	{
		assert(pos <= _size);
		if (len == npos || len + pos >= _size)
		{
			_str[pos] = '\n';
			_size = pos;
		}
		else
		{
			strcpy_s(_str + pos, _size - pos - len, _str + pos + len);
			_size -= len;
		}
		return *this;
	}

	size_t find(const char ch, size_t pos = 0)const
	{
		assert(pos < _size);
		while (pos < _size)
		{
			if (_str[pos] == ch)
			{
				return pos;
			}
			pos++;
		}
		return npos;
	}

	size_t find(const char* str, size_t pos = 0)const
	{
		assert(pos < _size);
		const char* findp = std::strstr(_str+pos,str);
		if (findp == nullptr)
		{
			return npos;
		}
		return findp - _str;
	}

	const char* c_str()
	{
		return _str;
	}

	istream& getline(istream& in, string& s)
	{
		char ch = in.get();
		while (ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}
	
	friend std::ostream& operator<<(std::ostream& out, const string& s);
	friend std::istream& operator>>(std::istream& in, string& s);
};

	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		/*for (size_t i = 0; i < s._size; i++)
		{
			out << s._str[i];
		}*/
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, string& s)
	{
		s.clear();
		char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}
}
#endif