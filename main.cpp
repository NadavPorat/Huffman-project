/**************************************************************************************

Project by:Nadav Porat

**************************************************************************************/
#include "GeneralHeader.h"
using namespace huff;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main()
{
	int treeSize;				 //Used for saving the tree size after calculating it.
	string fName;				 //Used for saving the Input 'File Name'.
	BinSearchTree treeByFile;	 //Used for saving the Input File data in a Binary Tree structure.
	BinSearchTreeNode **arr;	 //Array of Tree Nodes, used to save the Nodes after Huffman Algorithm.
	BinSearchTree huffTree;		 //Tree which will update its' nodes after using The Huffman Algorithm.
	BinSearchTreeNode *huffRoot; //Used to save a pointer to the Huffman Tree root Node.
	int *huffCodeArr;			 //ints arr that represents the Huffman Code of a given char
	int fileSize = 0;			 //Update File's Data Size (printed at the end of the program).
	int heapSize;				 //Heap's log Size.

	//~~~~ Open The Correct File (The input File) by its name ~~~~//
	cout << "Please enter the file name: " << endl;
	cin >> fName;
	ifstream inFileStream;
	inFileStream.open(fName);
	if (!inFileStream) //Check if there are any "File Opening problems"
	{
		cout << "invalid input" << endl;
		exit(1);
	}

	//~~~~ Build Binary Search Tree According to The Input File ~~~~//
	treeByFile.buildTreeByFD(inFileStream);
	treeSize = treeByFile.calcTreeSize(treeByFile.getRoot());

	//~~~~ Use Huffman Coding Method on the Tree We Made ~~~~//
	arr = new BinSearchTreeNode *[treeSize];
	;
	for (int i = 0; i < treeSize; i++)
	{
		arr[i] = new BinSearchTreeNode;
	}
	treeByFile.binSearchTreeToArray(arr);
	Heap heap(arr, treeSize); //Build new heap according to input arr of BinSearchTreeNodes and a given size
	huffRoot = huffTree.buildHuffmanTree(heap);

	//~~~~ Print Huffman Code of the Chars in the Input File ~~~~//
	heapSize = heap.getHeapSize();
	cout << "Character encoding: " << endl;
	huffCodeArr = new int[heapSize];
	huffRoot->printHuffman(huffRoot, huffCodeArr, 0, &fileSize);
	delete[] huffCodeArr;

	//~~~~ Print The Total Size Of The File ~~~~//
	cout << "Encoded file weight: " << fileSize << " bits" << endl;
	inFileStream.close();
	return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End Of Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
