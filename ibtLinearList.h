#pragma once
#include <ostream>

template <class T>
class IbtLinearList : public LinearList
{
public:

	class Iterator
	{
	public:
		virtual void operator++() = 0; // preincrement
		virtual void operator--() = 0; // predecrement
		virtual bool operator!=( const typename LinearList<T>::Iterator& right)const = 0;
		bool operator==( const Iterator<T> right)const = 0;
		T* operator->() const = 0;
		virtual T& operator*() const = 0;
	};

public:

	virtual T& operator[] (int i) const = 0;
	virtual void insert (int i, const T& data) = 0;
	virtual T remove (int i) = 0;

	virtual Iterator* begin() const = 0;
	virtual Iterator* end() const = 0;
	virtual Iterator<T> rbegin() const = 0;
	virtual Iterator<T> rend() const = 0;

	virtual void insert (Iterator<T> it, const T& data) = 0;

	virtual T& remove (Iterator<T> it) = 0;

	virtual int size() const = 0;

	template <class S>
	friend std::ostream& operator<<(std::ostream& os, const LinearList<S>& ll);

private:
	IndexedBinartTree<T> mIbt;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const LinearList<T>& ll)
{
	int i;
	for (i = 0; i < ll.size(); i++)
	{
		os << ll[i] << "\t";
	}
	return os;
}

