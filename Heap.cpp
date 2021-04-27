#include "GeneralHeader.h"

namespace huff
{
	Heap::Heap(int max)
	{
		data = new BinSearchTreeNode * [max];
		for (int i = 0; i < max; i++)
		{
			data[i] = new BinSearchTreeNode;
		}
		this->maxSize = max;
		this->allocated = 0;
		this->heapSize = 0;
	}
	Heap::~Heap()
	{
		for (int i = heapSize; i > 0; i--)
		{
			this->DeleteMin();
		}
		data = NULL;
	}

	Heap::Heap(BinSearchTreeNode** arr, int n)//Make heap from given arr of BST nodes and number of nodes
	{
		heapSize = maxSize = n;
		data=arr;
		allocated = 1;
		for (int i = n / 2 - 1; i >= 0; i--) 
		{
			FixHeap(i);
		}
	}

	bool Heap:: isEmpty() 
	{
		if(this->heapSize ==0)
		{
		return true;
		}
		else
		{
		return false;
		}
	}

	int Heap:: getHeapSize() 
	 { 
		 return this->heapSize;
	 }

	void Heap:: heapSizeEnlarge() 
	{
	 this->heapSize += 1; 
	}

	void Heap::Swap(BinSearchTreeNode** child, BinSearchTreeNode** parent)
	{
		BinSearchTreeNode* temp = *child;
		*child = *parent;
		*parent = temp;
	}

	void Heap::FixHeap(int node)
	{
		int min = node;
		int left = Left(node);
		int right = Right(node);
		//Find the min between left and right.
		if ((left < heapSize) && (data[left]->getFrequency() <=data[node]->getFrequency()))
			min = left;

		if ((right < heapSize) && (data[right]->getFrequency() <=data[min]->getFrequency()))
			min = right;
		if (min != node)//Fix Heap reqursively
		{
			Swap(&data[node], &data[min]);
			FixHeap(min);
		}
	}

	BinSearchTreeNode* Heap::DeleteMin()
	{
		if (heapSize < 1)
			cout << "ERROR! The Heap is Empty." << endl;
		BinSearchTreeNode* min = data[0];
		heapSize--;
		data[0] = data[heapSize];//Update the heap root
		FixHeap(0);
		return (min);
	}

	void Heap::Insert(BinSearchTreeNode* item) 
	{
		if (this->heapSize == this->maxSize)
		{
			cout << "ERROR!";
		}
		int i = heapSize;
		heapSize++;
		while ((i > 0) && (data[Parent(i)]->getFrequency() > item->getFrequency()))
		{
			data[i] = data[Parent(i)];
			i = Parent(i);
		}
		data[i] = item;
	}

	int Heap::Parent(int node)
	{
		return ((node - 1) / 2);
	}

	int Heap::Left(int node)
	{
		return (2 * node + 1);
	}

	int Heap::Right(int node)
	{
		return (2 * node + 2);
	}

	bool Heap::makeEmpty()
	{
		while (this->heapSize > 1)
		{
			this->DeleteMin();
		}
		return true;
	}
}