#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <algorithm>

template<class T>
class knot    
{
private:
	T data_;
	int priority_;
public:
	bool operator<(knot<T>& k) 
	{
		return priority_ < k.getpr();
	}
	knot<T>& operator=(knot<T>& k) 
	{
		data_ = k.getdata();
		priority_ = k.getpr();
		return *this;
	}
	int& getpr() 
	{
		return priority_;
	}
	T& getdata() 
	{
		return data_;
	}
	knot(int priority = 0, T data = T())
	{
		priority_ = priority;
		data_ = data;
	}
};
template<class T>
class Priority_queue 
{

private:
	knot<T>* heap_;
	int size_;
	int Msize_;
public:
	Priority_queue() 
	{
		int i = 6;
		Msize_ = i - 1;
		size_ = 0;
		heap_ = new knot<T>[i];
	}
	Priority_queue(std::vector<int> v1, std::vector<T> v2)
	{
		if (v1.size() != v2.size())
		{
			std::exception ex("Неверные входные данные");
			throw ex;
		}
		knot<T> k;
		size_ = v1.size();
		Msize_ = size_ / 2 * 3;
		heap_ = new knot<T>[Msize_ + 1];
		for (int i = 0; i < v1.size(); i++)
		{
			k.getpr() = v1[i];
			k.getdata() = v2[i];
			heap_[i + 1] = k;
		}
		for (int j = size_ / 2; j > 0; j--)
		{
			heapify(j);
		}
	}
	Priority_queue(const Priority_queue& q)
	{
		size_ = q.size_;
		Msize_ = q.Msize_;
		heap_ = new knot<T>[Msize_ + 1];
		for (int i = 0; i < size_ + 1; i++)
		{
			heap_[i] = q.heap_[i];
		}
	}
	~Priority_queue()
	{
		delete[] heap_;
	}
	int getsize_()
	{
		return size_;
	}
	void insert(int priority, T data) 
	{
		if (size_ == Msize_)
		{
			Msize_ = size_ / 2 * 3;
			knot<T>* heap_1 = new knot<T>[Msize_ + 1];
			for (int i = 0; i < size_ + 1; i++)
			{
				heap_1[i] = heap_[i];
			}
			delete[] heap_;
			heap_ = heap_1;
		}
		knot<T> k(priority, data);
		size_++;
		heap_[size_] = k;
		int j = size_;
		while (j != 1) 
		{
			if (heap_[j] < heap_[j / 2]) 
			{
				std::swap(heap_[j], heap_[j / 2]);
				j = j / 2;
			}
			else 
			{
				j = 1;
			}
		}
	}
	T& get_Min_Priority() 
	{
		if (size_ == 0) 
		{
			std::exception ex("Пустая куча");
			throw ex;
		}
		return heap_[1].getdata();
	}
	void heapify(int i) 
	{
		int j;
		while (i <= size_ / 2)
		{
			j = 2 * i;
			if ((2 * i + 1) <= size_)
			{
				if (heap_[2 * i + 1] < heap_[2 * i])
				{
					j = 2 * i + 1;
				}
			}
			if (heap_[j] < heap_[i])
			{
				std::swap(heap_[j], heap_[i]);
				i = j;
			}
			else
			{
				i = size_;
			}
		}
	}
	void remove() 
	{
		if (size_ == 0)
		{
			std::exception ex("Пустая куча");
			throw ex;
		}
		std::swap(heap_[1], heap_[size_]);
		size_--;
		heapify(1);
		if (size_ == Msize_ / 2 && Msize_ > 5)
		{
			Msize_ = size_ / 2 * 3;
			knot<T>* heap_1 = new knot<T>[Msize_ + 1];
			for (int i = 0; i < size_ + 1; i++)
			{
				heap_1[i] = heap_[i];
			}
			delete[] heap_;
			heap_ = heap_1;
		}
	}
	void change_of_priority(int new_pr) 
	{
		if (size_ == 0)
		{
			std::exception ex("Пустая куча");
			throw ex;
		}
		heap_[1].getpr() = new_pr;
		heapify(1);
	}
	Priority_queue<T> operator+(Priority_queue<T>& q)
	{
		std::vector<int> v1;
		std::vector<T> v2;
		for (int i = 1; i < getsize_() + 1; i++)
		{
			v1.push_back(heap_[i].getpr());
			v2.push_back(heap_[i].getdata());
		}
		for (int j = 1; j < q.getsize_() + 1; j++)
		{
			v1.push_back(q.heap_[j].getpr());
			v2.push_back(q.heap_[j].getdata());
		}
		Priority_queue<T> res(v1, v2);
		return res;
	}
};
