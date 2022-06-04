/*
Made by:
Mohamed Salah Ahmed Mansour Abdelrahman

ID:
20201700696

Date:
13th April 2022

Mainstream
*/



#include "BSTree.h"
#include <iostream>
#include <assert.h>
#include <queue>

using namespace std;

template <class T>
Node<T>::Node()
{
	left = right = NULL;
}

template <class T>
Node<T>::Node(T val)
{
	value = val;
	left = right = NULL;
}

template <class T>
BSTree<T>::BSTree(void)
{
	root = NULL;
}

template <class T>
bool BSTree<T>::contains(T val)
{
	Node<T>* tmp = findNode(val);
	return (tmp != NULL);
}

template <class T>
Node<T>* BSTree<T>::findNode(T val)
{
	Node<T>* temp = root;
	while (temp != NULL)
	{
		if (temp->value == val)
		{
			return temp;
		}
		else if (temp->value < val)
		{
			//right
			temp = temp->right;
		}
		else
		{
			//left
			temp = temp->left;
		}
	}

	return temp;
}

template <class T>
void BSTree<T>::insert(T val)
{
	assert(contains(val) == false);

	Node<T>* nodeToBeAdded = new Node<T>(val);
	if (root == NULL)
	{
		root = nodeToBeAdded;
	}
	else
	{
		Node<T>* temp = root;
		while (true)
		{
			if (temp->value < val)
			{
				// right
				if (temp->right == NULL)
				{
					temp->right = nodeToBeAdded;
					break;
				}
				else
				{
					temp = temp->right;
				}
			}
			else
			{
				// left
				if (temp->left == NULL)
				{
					temp->left = nodeToBeAdded;
					break;
				}
				else
				{
					temp = temp->left;
				}
			}
		}
	}
}

template <class T>
void BSTree<T>::traverse(Order order)
{
	if (order == INORDER)
		inOrder(root);
	else if (order == PREORDER)
		preOrder(root);
	else
		postOrder(root);
}

template <class T>
void BSTree<T>::inOrder(Node<T>* node)
{
	if (node != NULL)
	{
		//left
		inOrder(node->left);
		//node
		cout << node->value << endl;
		//right
		inOrder(node->right);
	}
}

template <class T>
void BSTree<T>::preOrder(Node<T>* node)
{
	if (node != NULL)
	{
		cout << node->value << endl;
		inOrder(node->left);
		inOrder(node->right);
	}
}

template <class T>
void BSTree<T>::postOrder(Node<T>* node)
{
	if (node != NULL)
	{
		inOrder(node->left);
		inOrder(node->right);
		cout << node->value << endl;
	}
}

template <class T>
void BSTree<T>::deleteBST(Node<T>* node)
{
	if (!node)
		return;

	Node<T>* currentTreeNode = node;
	Node<T>* leftTreeNode = node->left;
	Node<T>* rightTreeNode = node->right;
	delete(currentTreeNode);
	deleteBST(leftTreeNode);
	deleteBST(rightTreeNode);
}

template <class T>
BSTree<T>::~BSTree(void)
{
	deleteBST(root);
}

//dfs to check if a tree is Full Tree
template <class T>
bool dfs(Node<T>* node) {

	//applying depth-first search on tree

	//if both have children. recurse on both and return the AND-ing
	if (node->left != NULL && node->right != NULL)
	{
		return dfs(node->left) && dfs(node->right);
	}

	// if both don't have children, return true
	if (node->left == NULL && node->right == NULL)
	{
		return true;
	}


	//if one has a child and one does not, it is a false case
	return false;

}

template <class T>
bool fullTree(Node<T>* root) {


	//empty tree is a full tree
	if (root)
		return true;

	//applying depth-first search starting from root
	return dfs(root);
}


//function for complete tree

template <class T>
bool completeTree(Node<T>* root)
{

	//empty tree is complete tree
	if (root == NULL)
		return true;



	/*
	Traversing level by level (breadth-first search)

	assuming the level before the last was full, and the last was not
	then at least one of the nodes in the level before last had <2 children

	when we meet such node, we raise the emptyNode flag

	we check left node then right node

	if we find a non-empty node after finding an empty one, this means it's not a complete tree
		as non-empty ones should be leftmost
	*/


	bool emptyNode = false;

	queue<Node<T>*>q;
	q.push(root);

	while (!q.empty()) {

		auto cur = q.front();
		q.pop();

		if (cur->left) {
			//non empty node

			if (emptyNode)
				return false;

			q.push(cur->left);
		}
		else emptyNode = true;

		if (cur->right) {
			//non empty node

			if (emptyNode)
				return false;

			q.push(cur->right);
		}
		else emptyNode = true;

	}

	return true;
}





/*
	functions for perfect tree

	applying depth-first search to traverse all nodes
	when a leaf is found, decision is made whether it matches the max depth reached or not
*/
template <class T>
bool dfs(Node<T>* node, int depth, int& treeDepth) {

	//base case when finding a leaf
	if (node->left == NULL && node->right == NULL) {

		//if this is the first depth recorded
		if (treeDepth == 0) {
			treeDepth = depth;
			return true;
		} 

		//if we reached a leaf with depth different to the one recorded
		if (depth != treeDepth) {
			return false;
		}
	}

	//in case that just one child is NULL
	else if (node->left == NULL || node->right == NULL) {
		return false;
	}

	//both not NULL
	else return dfs(node->left, depth + 1, treeDepth) && dfs(node->right, depth + 1, treeDepth);
}

template <class T>
bool perfectTree(Node<T>* root) {
	if (root == NULL) {
		//empty tree is not a perfect tree
		return false;
	}

	int treeDepth = 0;
	return dfs(root, 0, treeDepth);

}
// functions for balanced tree

template <class T>
int _dfs(Node<T>* node) {

	int leftDepth = 0, rightDepth = 0;

	//at each node, we recursively obtain the depth of both children
	if (node->left != NULL)
		leftDepth = dfs(node->left);

	if (node->right != NULL)
		rightDepth = dfs(node->right);

	//if imbalance was found down the tree, return the -1 as a flag
	if (leftDepth == -1 || rightDepth == -1)
		return -1;

	//if the absolute difference was > 1, we return -1 to indicate imbalance
	if (abs(leftDepth - rightDepth) > 1)
		return -1;

	//we return current node (1) + max of two depths for further comparisons up the tree
	return 1 + max(leftDepth, rightDepth);
}

template <class T>
bool balancedTree(Node<T>* root) {

	//empty tree is balanced tree
	if (root == NULL)
		return true;

	return _dfs(root) != -1;
}






template <class T>
void BSTree<T>::displayTreeType()
{
	if (fullTree(root)) cout << "Full tree" << endl;
	if (completeTree(root)) cout << "Complete Tree" << endl;
	if (perfectTree(root)) cout << "Perfect Tree" << endl;
	if (balancedTree(root)) cout << "Balanced Tree" << endl;
}



int main() {

	//test scenario
	BSTree<int>mytree;

	cout << "inserted 5,4,6:\n";

	cout << "    5\n   / \\ \n  4   6\n";

	mytree.insert(5);
	mytree.insert(4);
	mytree.insert(6);


	mytree.displayTreeType();

	cout << "\n\nAfter inserting 3:\n";
	mytree.insert(3);
	cout << "    5\n   / \\ \n  4   6\n /\n3\n";


	mytree.displayTreeType();

	cout << "\n\nAfter inserting 7:\n";
	mytree.insert(7);
	cout << "    5\n   / \\ \n  4   6\n /     \\\n3       7\n";

	mytree.displayTreeType();



}
