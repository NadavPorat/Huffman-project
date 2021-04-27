#pragma once

namespace huff
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap Structure ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	class Heap;
	typedef struct
	{
		char ch;
		int frequency;
	}chFreq;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BinSearchTreeNode Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	class BinSearchTreeNode
	{
	private:
		chFreq val;
		BinSearchTreeNode* left;
		BinSearchTreeNode* right;
	public:
		BinSearchTreeNode();
		BinSearchTreeNode(char ch, BinSearchTreeNode* left, BinSearchTreeNode* right);
		~BinSearchTreeNode();
		void Inorder(BinSearchTreeNode* node);
		void Preorder(BinSearchTreeNode* node);
		void Postorder(BinSearchTreeNode* node);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Set Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		void setVal(chFreq set);
		char setCH(char ch);
		void setLeft(BinSearchTreeNode* set);
		void setRight(BinSearchTreeNode* set);
		void setFrequency(int frequency);
		bool EnlargeFrequencyBy1();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Get Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		BinSearchTreeNode* getLeft()  const;
		BinSearchTreeNode* getRight() const;
		chFreq getVal();
		char getCH() const;
		int getFrequency() const;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Print Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		void printHuffman(BinSearchTreeNode* root, int arr[], int idx, int* FileSize);//also calculating the file data size
		void PrintArr(int* arr, int idx);
	};

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BinSearchTree Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	class BinSearchTree
	{
	private:
		BinSearchTreeNode* root;
	public:
		BinSearchTree() :root(nullptr) {};
		~BinSearchTree();
		BinSearchTreeNode* Find(char ch);
		void Insert(char ch);
		int calcTreeSize(BinSearchTreeNode* node);//Reqursive func that calculates the Size of a given tree (By input: pointer to root)
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Build Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		BinSearchTreeNode* buildHuffmanTree(Heap heap);
		void buildTreeByFD(ifstream& inFile);
		void binSearchTreeToArray(BinSearchTreeNode** array);
		void binSearchTreeToArrayHelper(BinSearchTreeNode* root, BinSearchTreeNode** arr,int * val);//Export the BinaryTree vals to array
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Get Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		BinSearchTreeNode* getRoot();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Delete Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		void Delete(char ch);
		BinSearchTreeNode* deleteNode(BinSearchTreeNode* root, char ch);
	};
}
