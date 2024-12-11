#include "List.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "AVLtree.hpp"
#include <vector>
#include "unordered_map.hpp"
#include "priority_queue.hpp"
#include "dequeue.hpp"
void Test3()
{
	tinystl::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	tinystl::vector<int>::iterator it = find(v.begin(), v.end(), 3);
	if (it != v.end())
	{
		v.insert(it, 30);
	}
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_queue()
{
	tinystl::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;

}
void test1()
{
	tinystl::stack<int> sk1;

	sk1.push(1);
	sk1.push(2);
	sk1.push(3);
	sk1.push(4);

	sk1.pop();
	cout << sk1.top() << " " << sk1.size() << " " << sk1.empty() << " " << endl;
}
void test2()
{
	const int N = 1000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));

	for (int i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}

	DS::AVLTree<int, int> t;
	for (auto i : v)
	{
		t.insert(make_pair(i, 1));
	}
	t.InOrder();
	if (t.IsBalance())
		cout << "ÊÇAVLÊ÷" << endl;
	else
		cout << "²»ÊÇAVLÊ÷" << endl;
}

void test4()
{
	tinystl::priority_queue<int> pq;
	pq.push(7);
	pq.push(10);
	pq.push(5);
	pq.push(6);
	pq.push(2);
	cout << pq.top() << endl;
	pq.pop();
	cout << pq.top() << endl;
}

void dequeue_test()
{
	tinystl::dequeue<int> ilist;
	tinystl::dequeue<int> one;
	int* ip = new int(3);
	int* j = new int(5);
	int* i = new int(7);
	int* p = new int();
	ilist.insertFront(ip);  
	ilist.insertFront(j);   
	ilist.insertBack(i);   
	one = ilist; 
	p = one.removeFront(); 
	if(p!=nullptr)
	cout << "one first number is:" << *p << endl; 
	tinystl::dequeue<int> two(ilist);
	p = two.removeFront(); 
	if (p != nullptr)
	cout << "two first number is:" << *p << endl; 
	if (ip != nullptr)
	ip = ilist.removeFront(); 
	if (ip != nullptr)
	cout << "ilist first number is:" << *ip << endl; 
	j = ilist.removeBack(); 
	if (j != nullptr)
	cout << "ilist last number is:" << *j << endl; 
}
int main()
{
	dequeue_test();
	
	return 0;
}