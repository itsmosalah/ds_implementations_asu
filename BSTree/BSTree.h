#pragma once
enum Order
{
	INORDER = 0,
	PREORDER = 1,
	POSTORDER = 2,
	XOrder = 3
};

template <class T>
class Node
{
public:
	T value;
	Node<T>* left, * right;
	Node();
	Node(T val);
};

template <class T>
class BSTree
{
	Node<T>* root;

public:
	BSTree(void);
	~BSTree(void);

	bool contains(T val);
	Node<T>* findNode(T val);
	void insert(T val);
	
	void traverse(Order order);

	void inOrder(Node<T>* node);
	void preOrder(Node<T>* node);
	void postOrder(Node<T>* node);
	void deleteBST(Node<T>* node);
	void displayTreeType();

};
