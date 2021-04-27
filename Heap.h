#pragma once

namespace huff 
{
	class BinSearchTree;
	class BinSearchTreeNode;
	class Heap 
	{
	private:
		BinSearchTreeNode** data;  //Points to the data array.
		int maxSize;               //Max size of heap (Phys size)
		int heapSize;              //Current size of heap (Log size)
		int allocated;             //1 if heap allocated memory.
		static int Left(int node);
		static int Right(int node);
		static int Parent(int node);
		void FixHeap(int node);
	public:
		Heap(int max);
		Heap(BinSearchTreeNode** arr, int n);
		~Heap();
		bool isEmpty() ;
		bool makeEmpty();
		int getHeapSize();
		void heapSizeEnlarge() ;
		void Insert(BinSearchTreeNode* node);
		void Swap(BinSearchTreeNode** child, BinSearchTreeNode** parent);
		BinSearchTreeNode* DeleteMin();
	};
}
