#ifndef TING_PRIORITY_QUEUE
#define TING_PRIORITY_QUEUE
#include"Vector.hpp"
#include<algorithm>

namespace tinystl
{
	template<typename T>
	struct less {
		bool operator()(const T& a, const T& b)
		{
			return a < b;
		}
	};

	template<typename T>
	struct greater
	{
		bool operator()(const T& a, const T& b)
		{
			return a > b;
		}
	};
	
	template<typename T, typename Container = tinystl::vector<T>, typename Compare = less<T>>
	class priority_queue
	{
	public:
		priority_queue()
		{}

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last) :c(first, last)
		{
			for (int i = (c.size() - 2) / 2; i >= 0; i++)
			{
				adjust_down(i);
			}
		}

		bool empty()
		{
			return c.empty();
		}

		size_t size()
		{
			return c.size();
		}

		const T& top() const
		{
			return c[0];
		}

		void adjust_down(int father)
		{
			int child = father * 2 + 1;
			while (child < c.size())
			{
				if (child + 1 < c.size() && comp(c[child], c[child + 1]))
				{
					child++;
				}

				if (comp(c[father], c[child]))
				{
					std::swap(c[father],c[child]);
					father = child;
					child = 2 * father + 1;
				}
				else
				{
					break;
				}
			}
		}

		void adjust_up(int child)
		{
			int father = (child - 1) / 2;
			while (child > 0)
			{
				if (comp(c[father], c[child]))
				{
					std::swap(c[child], c[father]);
					child = father;
					father = (child - 1) / 2;
				}
				else {
					break;
				}
			}
		}

		void push(const T& x)
		{
			c.push_back(x);
			adjust_up(c.size() - 1);
		}

		void pop()
		{
			swap(c[0], c[c.size() - 1]);
			c.pop_back();
			adjust_down(0);
		}
	private:
		Container c;
		Compare comp;
	};

}
#endif