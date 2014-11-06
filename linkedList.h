#pragma once
#include <ostream>

template <class T>
class LinkedLinearList{
	private:
		class Node
		{
		public:
			Node()
			{
			}
			
			Node(T newData,Node *Prev,Node *Next)
		      : mData(newData)
			{
				mPrev = Prev;
				mNext = Next;
			}
				T		mData;
				Node*	mPrev;
				Node*	mNext;
				friend class Iterator;
		};

	public:
/////////////////////////////////// START OF ITERATOR ///////////////////////////////////////
	class Iterator
	{
	public:
		Iterator ()
		{
		}
		
		Iterator (Node *ptr)
		{
			mPtr = ptr;
		}

		virtual Iterator& operator++() // preincrement
		{
			mPtr=mPtr->mNext;
			return *this;
		} 

		virtual Iterator operator++(int dummy) // postincrement
		{
			Iterator r(mPtr);
			mPtr = mPtr->mNext;
			
			return r;
		}

		virtual Iterator& operator--() // predecrement
		{
			mPtr = mPtr->mPrev;
			return *this;
		}

		virtual Iterator operator--(int dummy) // postdecrement
		{
			Iterator r(mPtr);
			mPtr = mPtr->mPrev;
			return r;
		}

		bool operator!=( const Iterator& right)const
		{
			return (mPtr != right.mPtr);
		}

		bool operator==( const Iterator& right)const
		{
			return (mPtr == right.mPtr);
		}

		T* operator->() const
		{
			return &(mPtr->mData);
		}

		T& operator*() const
		{
			return (mPtr->mData);
		}

		friend class LinkedLinearList;//dflt

	private://public
		Node *mPtr;
	};
///////////////////////////////// END OF ITERATOR ///////////////////////////////////////////
	LinkedLinearList(void)
	{
		mSize = 0;
		mHeaderNode = new Node();
		mHeaderNode->mNext = mHeaderNode;
		mHeaderNode->mPrev = mHeaderNode;
	}

	virtual ~LinkedLinearList(void)
	{
		Node *n, *nn; 
		for (n = mHeaderNode->mNext; n != mHeaderNode;)
		{
			nn = n->mNext;
			delete n;
			n = nn;
		}
		delete mHeaderNode;
	}

public:

	virtual void pushBack(const T& data)
	{
		
		insert(mHeaderNode,data);
	
		
	}

	virtual void pushFront(const T& data)
	{
		
		insert(mHeaderNode->mNext,data);
		
	}

	virtual T popBack()
	{
		Iterator it(mHeaderNode->mPrev);
		T returnValue = mHeaderNode->mPrev->mData;
		remove(it);
		
	    return returnValue;
		
	}

	virtual T popFront()
	{
		
		Iterator it(mHeaderNode->mNext);
		T returnValue = mHeaderNode->mNext->mData;
		remove(it);
		
	    return returnValue;
	}

	virtual Iterator begin() const
	{
		Iterator r(mHeaderNode->mNext);
		
		return r;
	}

	virtual Iterator end() const
	{
		Iterator r(mHeaderNode);
		return r;
	}

	virtual Iterator rbegin() const
	{
		Iterator r(mHeaderNode->mPrev);
		return r;
	}

	virtual Iterator rend() const
	{
		Iterator r(mHeaderNode);
		return r;
	}

	// The returned iterator would point to the inserted element.
	virtual Iterator insert (Iterator it, const T& data)
	{
		
		Node *newNode,
			 *p = it.mPtr->mPrev;
		newNode = new Node();
		newNode->mData = data;
		Iterator r(newNode);


		newNode->mPrev = p;
		newNode->mNext = it.mPtr;
		p->mNext = newNode;
		it.mPtr->mPrev = newNode;
		
		
		mSize++;
		return r;
		// Write your code here
	}

	// The returned iterator would point to the element after the removed one.
	virtual Iterator remove (Iterator it)
	{
		
	

		Iterator rtrn_it(it.mPtr->mNext);  
		it.mPtr->mNext->mPrev = it.mPtr->mPrev;
		it.mPtr->mPrev->mNext = it.mPtr->mNext;
		mSize--;
		
		return rtrn_it;
		// Write your code here
	}

	virtual int size() const {
		return mSize;
	};
	friend class Iterator;
	void print1(){
	Iterator it;
	for (it=begin();it != end() ;it++){
	cout <<*it<<"\n";
		}
	}
	void print2(){
		current=mHeaderNode->mNext;
		while (current != mHeaderNode)
		{
			cout<<"["<<current->mData<<"]  ";
			current = current->mNext;
		}
	}
private:
	Node *mHeaderNode,*current;
	int mSize;
};


template <class T>
std::ostream& operator<<(std::ostream& os, const LinkedLinearList<T>& ll)
{
	LinkedLinearList<T>::Iterator itr;
	
	for (itr = ll.begin(); itr != ll.end(); itr++)

	{
		os << *itr <<"\n";
	}
	return os;
}

