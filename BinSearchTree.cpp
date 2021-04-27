#include "GeneralHeader.h"

namespace huff
{
	class BinSearchTree;
	class BinSearchTreeNode;
	//****************************************************BinSearchTreeNode Funcs****************************************************//
	BinSearchTreeNode::BinSearchTreeNode()
	{
		this->left = nullptr;
		this->right = nullptr;
		this->val.frequency = 0;
	}

	BinSearchTreeNode::BinSearchTreeNode(char ch, BinSearchTreeNode* left, BinSearchTreeNode* right)
	{
		chFreq newFreq;
		newFreq.ch = ch;
		newFreq.frequency = 1;
		this->val = newFreq;
		this->left = left;
		this->right = right;
	}

	BinSearchTreeNode::~BinSearchTreeNode()
	{
		if (left != nullptr)
		{
			left = nullptr;//delete (left);

		}
		if (right != nullptr)
		{
			right = nullptr;//delete (right);
		}
		this->val.frequency = 0;
		this->val.ch = NULL;
	}

	void BinSearchTreeNode::Postorder(BinSearchTreeNode* node)
	{
		if (node == nullptr)
			return;
		Postorder(node->left);
		Postorder(node->right);
	}

	void BinSearchTreeNode::Inorder(BinSearchTreeNode* node)
	{
		if (node == nullptr)
			return;
		Inorder(node->left);
		if (node->getCH() != '\0')
		{
			cout << "The Char is: " << node->getCH();
			cout << ", Frequency: " << node->getFrequency() << endl;
		}
		cout << "1";
		Inorder(node->right);
	}

	void BinSearchTreeNode::Preorder(BinSearchTreeNode* node)
	{
		if (node == nullptr)
			return;
		cout << node->getFrequency() << " ";
		Preorder(node->left);
		Preorder(node->right);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BinSearchTreeNode Set Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	void BinSearchTreeNode::setVal(chFreq set)
	{
		this->val.ch = set.ch;
		this->val.frequency = set.frequency;
	}

	char BinSearchTreeNode::setCH(char ch)
	{
		return this->val.ch = ch;
	}

	void BinSearchTreeNode::setLeft(BinSearchTreeNode* set)
	{

		this->left = set;
	}

	void BinSearchTreeNode::setRight(BinSearchTreeNode* set)
	{
		this->right = set;
	}

	void BinSearchTreeNode::setFrequency(int frequency)
	{
		this->val.frequency = frequency;
	}

	bool BinSearchTreeNode::EnlargeFrequencyBy1()
	{
		return this->val.frequency += 1;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Get Funcs BinSearchTreeNode ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	BinSearchTreeNode* BinSearchTreeNode::getLeft()  const
	{
		return this->left;
	}

	BinSearchTreeNode* BinSearchTreeNode::getRight()  const
	{
		return this->right;
	}
	chFreq BinSearchTreeNode::getVal()
	{
		return this->val;
	}

	char BinSearchTreeNode::getCH() const
	{
		return this->val.ch;
	}

	int BinSearchTreeNode::getFrequency() const
	{
		return this->val.frequency;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BinSearchTreeNode Print Funcs BinSearchTreeNode~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	void BinSearchTreeNode::printHuffman(BinSearchTreeNode* root, int arr[], int idx, int* fileSize)
	{
		if (root->right)//in case right root isn't null, insert 1 to the array
		{
			arr[idx] = 1;
			printHuffman(root->right, arr, idx + 1, fileSize);
		}

		if (root->left)//in case left root isn't null, insert 0 to the array
		{
			arr[idx] = 0;
			printHuffman(root->left, arr, idx + 1, fileSize);
		}

		//calculate the size by multiplying every leaf frequency with the number of bits used to represent its' value
		if (root->right == nullptr && root->left == nullptr)
		{
			*fileSize += (root->getFrequency()) * idx;
			if (idx == 0)//in case the we are dealing with an array that has the same value in all of its' cells
			{
				arr[idx] = 1;
				//*fileSize += (root->getFrequency());
				*fileSize = root->getFrequency();
				idx++;
			}

			if(root->getCH()!= '\n' && root->getCH()!= '\t')
			{
				cout << "'" << root->getCH() << "'";
			}
			else
			{
				root->getCH()=='\n'? (cout << "'" << ENDL << "'"): (cout << "'" << TAB << "'");
			}
			PrintArr(arr, idx);//Print the values in the array which representing the Huffman Code for the specific value.
		}
	}

	void BinSearchTreeNode::PrintArr(int* arr, int idx)
	{
		cout << " - ";
		for (int i = 0; i < idx; i++)
		{
			cout << arr[i];
		}
		cout << endl;
	}

	//****************************************************BinSearchTree Funcs****************************************************//		
	BinSearchTree::~BinSearchTree()
	{
		if (root != nullptr)
		{
			delete (this->root);
			root = nullptr;
		}
	}

	BinSearchTreeNode* BinSearchTree::Find(char ch)
	{
		BinSearchTreeNode* temp = root;
		while (temp != nullptr)
		{
			if (ch == (temp->getCH()))
			{
				return temp;
			}
			else if (ch < temp->getCH())
			{
				temp = temp->getLeft();
			}
			else
			{
				temp = temp->getRight();
			}
		}
		return nullptr;
	}

	void BinSearchTree::Insert(char ch)
	{
		BinSearchTreeNode* res;
		res = Find(ch);
		if (res)
		{
			res->EnlargeFrequencyBy1();
			return;
		}
		BinSearchTreeNode* temp = root;
		BinSearchTreeNode* parent = nullptr;
		BinSearchTreeNode* newNode;
		while (temp != nullptr)
		{
			parent = temp;
			if (ch < (temp->getCH()))
			{
				temp = temp->getLeft();
			}
			else
			{
				temp = temp->getRight();
			}
		}
		newNode = new BinSearchTreeNode(ch, nullptr, nullptr);
		if (parent == nullptr)
		{
			root = newNode;
		}
		else if (ch < parent->getCH())
		{
			parent->setLeft(newNode);
		}
		else {
			parent->setRight(newNode);
		}
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Calc Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	int BinSearchTree::calcTreeSize(BinSearchTreeNode* root)
	{
		if (root == NULL)
			return 0;
		else
			return(calcTreeSize(root->getLeft()) + 1 + calcTreeSize(root->getRight()));
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Build Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	BinSearchTreeNode* BinSearchTree::buildHuffmanTree(Heap heap) //Build Huffman Tree by a given input Heap
	{
		BinSearchTreeNode* node;
		int heapSize = heap.getHeapSize();
		for (int i = 1; i < heapSize; i++)//Build a subtree in every iteration
		{
			node = new BinSearchTreeNode;
			node->setLeft(heap.DeleteMin());
			node->setRight(heap.DeleteMin());
			node->setFrequency(node->getLeft()->getFrequency() + node->getRight()->getFrequency());//Sum the freqs of the min heaps for the root we build
			heap.Insert(node);
		}
		return heap.DeleteMin();//Return the updated heap
	}

	void BinSearchTree::buildTreeByFD(ifstream& inFileStream)//Builds tree according to the data in a given file input
	{
		BinSearchTreeNode* temp;
		char ch = NULL;
		do
		{
			if (!inFileStream.good())
			{
				cout << "invalid input" << endl;
				exit(1);
			}
			inFileStream.get(ch);
			Insert(ch);

		} while (!inFileStream.eof());
		temp = Find(ch);
		temp->setFrequency(temp->getVal().frequency - 1); //ignore the multiply calculation of the last charachter in the input file
	}

	 void BinSearchTree::binSearchTreeToArray(BinSearchTreeNode** array)//Export the BinaryTree vals to array
	{
		 int val = 0;
		binSearchTreeToArrayHelper(this->root, array,&val);
	}

	
	void BinSearchTree::binSearchTreeToArrayHelper (BinSearchTreeNode* node, BinSearchTreeNode** arr,int* val)//Req func Helper
	{
		if (node == NULL)
			return;
			binSearchTreeToArrayHelper(node->getLeft(), arr, val);
			arr[*val]->setVal(node->getVal());
			*val += 1;
			binSearchTreeToArrayHelper(node->getRight(), arr, val);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BinSearchTreeNode Get Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	BinSearchTreeNode* BinSearchTree::getRoot()
	{
		return this->root;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BinSearchTreeNode Delete Funcs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	void BinSearchTree::Delete(char ch)
	{
		BinSearchTreeNode* toDel;
		toDel = Find(ch);
		if (toDel)
		{
			deleteNode(toDel, ch);
		}
		else
		{
			cout << "Error! The Char Not Found";
		}
	}

	BinSearchTreeNode* BinSearchTree::deleteNode(BinSearchTreeNode* root, char ch)
	{
		if (root == NULL)
			return root;

		if (root->getCH() > ch)
		{
			root->setLeft(deleteNode(root->getLeft(), ch));
			return root;
		}
		else if (root->getCH() < ch)
		{
			root->setRight(deleteNode(root->getRight(), ch));
			return root;
		}
		if (root->getLeft() == NULL)
		{
			BinSearchTreeNode* temp = root->getRight();
			delete root;
			return temp;
		}
		else if (root->getRight() == NULL)
		{
			BinSearchTreeNode* temp = root->getLeft();
			delete root;
			return temp;
		}
		else
		{
			BinSearchTreeNode* currParent = root;
			BinSearchTreeNode* curr = root->getRight();
			while (curr->getLeft() != NULL)
			{
				currParent = curr;
				curr->setLeft(curr->getLeft());
			}
			if (currParent != root)
			{
				currParent->setLeft(curr->getRight());
			}
			else
			{
				currParent->setRight(curr->getRight());
			}
			root->setCH(curr->getCH());
			delete curr;
			return root;
		}
	}
}