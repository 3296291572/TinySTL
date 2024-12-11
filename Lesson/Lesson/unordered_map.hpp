#ifndef TING_UNORDERED_MAP
#define TING_UNORDERED_MAP
#include<iostream>
#include <cassert>

namespace tinystl
{
	template<typename K, typename V, typename H = std::hash<K>>
	class unordered_map {
	private:
		typedef K key_t;
		typedef V val_t;
		typedef H hash_t;
	public:
		struct node {
			key_t key;
			val_t val;
			node* next;

			node():key(0), val(0), next(nullptr){}

			node(key_t key, val_t val):key(key), val(val), next(nullptr){}

			node(const node& other) :key(other.key), val(other.val), next(nullptr)
			{
				if (other.next != nullptr)
				{
					next = new node(*other.next);
				}
			}
		};

		const float factor = 0.75f;
		size_t cnt;
		size_t capacity;
		node **map;

		unordered_map() :cnt(0), capacity(64), map(nullptr)
		{
			map = new node * [capacity];
			for (int i = 0; i < capacity; i++)
			{
				map[i] = nullptr;
			}
		}

		unordered_map(unordered_map &src) :cnt(src.cnt), capacity(src.capacity), map(nullptr)
		{
			assert(capacity > 0);
			map = new node * [capacity];
			copy_map(map, src.map);
		}

		unordered_map(unordered_map&& src) :cnt(src.cnt), capacity(src.capacity), map(src.map)
		{
			assert(src.capacity > 0 && src.map != nullptr);

			src.map = nullptr;
		}

		~unordered_map()
		{
			destroy();
		}

		size_t getIndex(key_t key)
		{
			hash_t to_hash;
			size_t code = to_hash(key);
			code = code ^ (code >> 16);
			return code & (capacity - 1);
		}

		void put(key_t key, val_t val)
		{
			if (cnt >= factor * capacity)resize();
			putVal(key, val);
		}

		void resize()
		{
			capacity <<= 1;
			node** tmp = map;
			map = new node * [capacity];
			std::fill(map, map + capacity, nullptr);
			rehash(tmp);
			delete[]tmp;
		}

		void rehash(node** preTable)
		{
			cnt = 0;
			assert(preTable != nullptr);
			size_t preSize = capacity >> 1;
			for (size_t i = 0; i < preSize; i++)
			{
				if (preTable[i] != nullptr)
				{
					node* preNode;
					node* curNode = preTable[i];
					while (curNode != nullptr)
					{
						preNode = curNode;
						curNode = curNode->next;
						insert(preNode);
					}
				}
			}
		}

		val_t& get(key_t key)
		{
			val_t* ret = getVal(key);
			assert(ret != nullptr);
			return *ret;
		}

		bool count(key_t key)
		{
			return getVal(key) != nullptr;
		}

		val_t& operator[](key_t key)
		{
			val_t* val = getVal(key);
			if (val == nullptr)
			{
				put(key, val_t(0));
			}
			else
			{
				return *val;
			}
			return get(key);
		}

		void insert(node *newNode)
		{
			size_t index = getIndex(newNode->key);
			
			node* bucket = map[index];
			if (bucket == nullptr)
			{
				map[index] = newNode;
			}
			else
			{
				node* curNode = bucket;
				while (curNode->next != nullptr)
				{
					curNode = curNode->next;
				}
				curNode->next = newNode;
			}
			newNode->next = nullptr;
		}
	private:
		val_t *getVal(key_t key)
		{
			size_t index = getIndex(key);
			node* p = map[index];
			while (p != nullptr)
			{
				if (p->key == key)
				{
					return &(p->val);
				}
				p = p->next;
			}
			return nullptr;
		}

		void copy_map(node**& map, node** srcmap)
		{
			for (size_t i = 0; i < capacity; i++)
			{
				if (srcmap[i] != nullptr)
				{
					map[i] = new node(*srcmap[i]);
				}
			}
		}
        
		void putVal(key_t key, val_t val)
		{
			size_t index = getIndex(key);
			node* tmp = map[index];
			if (tmp == nullptr)
			{
				map[index] = new node(key, val);
				cnt++;
				return;
			}
			while (tmp != nullptr)
			{
				if (tmp->key == key)
				{
					tmp->val = val;
					return;
				}
				tmp = tmp->next;
			}
			node* p = new node(key, val);
			p->next = map[index];
			map[index] = p;
			cnt++;
		}

		void destroy()
		{
			if (map != nullptr)
			{
				for (size_t i = 0; i < capacity; i++)
				{
					delete map[i];
					map[i] = nullptr;
				}
			}
			delete[] map;
			map = nullptr;
			cnt = 0;
			capacity = 0;
		}
	};
}

#endif