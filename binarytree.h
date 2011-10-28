/*! \class BinaryTreeType
 *  \brief Defines a binary tree data structure.
 *
 *  Defines a binary tree data structure.
 *
 *  \author Blair Jordan
 *  \version 1.0
 *  \date 20-MAY-2009
 *
 * <pre>
 *  Revision  Name        Date         Description
 *  1         B. Jordan   20-MAY-2009  Created
 * </pre>
*/

#ifndef _BINARYTREE_H
#define	_BINARYTREE_H

#include <iostream>

using namespace std;

const int LEFT_LINK = 0;			        // A constant to represent left links.
const int RIGHT_LINK = 1;			        // A constant to represent right links.

/*! \struct NodeType
 *  \brief A binary tree node.
 */
template <class elemType>
struct NodeType
{
    int key;                                // A unique key for the node
	elemType info;                          // The data stored by the node
	NodeType<elemType> *lLink;		        // A pointer to the left child node
	NodeType<elemType> *rLink;              // A pointer to the right child node
};

template <class elemType>
class BinaryTreeType
{
public:
    /*! Default constructor for a binary tree. */
	BinaryTreeType();

	/*! Destructor for a binary tree. */
	virtual ~BinaryTreeType();
	
	/*! Inserts a new item into the tree.
	 *  \param newItem The new data to be inserted into the tree.
	 *  \param key A unique identifier for the item .
	 */
	virtual void Insert(const elemType newItem, int key) = 0;

	/*! Searches for an item in the tree depth-first.
	 *  \param searchItem The search item.
	 *  \retval key The key of the search item (if found).
	 *  \retval true If the search item is found.
	 *  \retval false If the search item is not found .
	 */
	virtual bool Search(elemType &searchItem, int &key) const = 0;

	/*! Returns true if an item is a leaf node, otherwise false is returned.
	 *  \retval true If an item is found and has no children.
	 *  \retval false If an item is not found or has children. 
	 */
	bool IsLeaf(const int key);

	/*! Returns true if the the tree is completely empty, otherwise it returns true.
	 * \retval true If the root node is null (the tree is empty).
	 * \retval false If the root node has been set. 
	 */
	bool IsEmpty();

        /*! Performs inorder traversal of tree, printing each node. */
	void InorderTraverse();

	/*! Performs preorder traversal of tree, printing each node. */
	void PreorderTraverse();

	/*! Performs postorder traversal of tree, printing each node. */
	void PostorderTraverse();

	/* Copies tree contents to another tree */
	void CopyTree(NodeType<elemType>* &destRoot,
				  NodeType<elemType>* sourceRoot);

	/*! Overloaded assignment operator.
	 *  \param  tree A reference to the assigning binary tree.
	 *  \retval tree A reference to the assigned binary tree. 
	 */
	const BinaryTreeType& operator= (const BinaryTreeType<elemType>& tree);

protected:

        /*! Performs inorder traversal of tree, printing each node.
	 * \param node The root node of the tree being traversed.
	 */
	void Inorder(NodeType<elemType> *node) const;

	/*! Performs preorder traversal of tree, printing each node.
	 * \param node The root node of the tree being traversed.
	 */
	void Preorder(NodeType<elemType> *node) const;

	/*! Performs postorder traversal of tree, printing each node.
	 * \param node The root node of the tree being traversed.
	 */
	void Postorder(NodeType<elemType> *node) const;

	/*! Destroys a tree, starting from the parent node.
	 * \param node A pointer to the parent node.
	 */
	void Destroy(NodeType<elemType> *node);
        
	/*! A pointer to the root node of the binary search tree. */
	NodeType<elemType> *root;
};

template <class elemType>
void BinaryTreeType<elemType>::InorderTraverse()
{
    Inorder(root);
}

template <class elemType>
void BinaryTreeType<elemType>::PreorderTraverse()
{
    Preorder(root);
}

template <class elemType>
void BinaryTreeType<elemType>::PostorderTraverse()
{
    Postorder(root);
}

template <class elemType>
void BinaryTreeType<elemType>::Inorder(NodeType<elemType> *node) const
{
    if (node != NULL)
    {
        Inorder(node->lLink);
        cout << node->info << endl;
        Inorder(node->rLink);
    }
}

template <class elemType>
void BinaryTreeType<elemType>::Preorder(NodeType<elemType> *node) const
{
    if (node != NULL)
    {
        cout << node->info << endl;
        Inorder(node->lLink);
        Inorder(node->rLink);
    }
}

template <class elemType>
void BinaryTreeType<elemType>::Postorder(NodeType<elemType> *node) const
{
    if (node != NULL)
    {
        Inorder(node->lLink);
        Inorder(node->rLink);
        cout << node->info << endl;;
    }
}


template <class elemType>
bool BinaryTreeType<elemType>::IsEmpty()
{
    return (this->root == NULL) ? true : false;
}

template <class elemType>
void BinaryTreeType<elemType>::Destroy(NodeType<elemType> *node)
{
	if (node != NULL)
	{
		Destroy(node->lLink);
		Destroy(node->rLink);
		delete node;
		node = NULL;
	}
}

template <class elemType>
void BinaryTreeType<elemType>::CopyTree(NodeType<elemType>* &destRoot,
										NodeType<elemType>* sourceRoot)
{
	if (sourceRoot == NULL)
		destRoot = NULL;
	else
	{
		destRoot = new NodeType<elemType>;
		destRoot->info = sourceRoot->info;
		CopyTree(destRoot->lLink, sourceRoot->lLink);
		CopyTree(destRoot->rLink, sourceRoot->rLink);
	}
}


template <class elemType>
BinaryTreeType<elemType>::BinaryTreeType()
{
	root = NULL;
}


template <class elemType>
BinaryTreeType<elemType>::~BinaryTreeType()
{
	Destroy(root);
}

template <class elemType>
const BinaryTreeType<elemType>& BinaryTreeType<elemType>::
	  operator= (const BinaryTreeType<elemType>& tree)
{
	if (this != &tree)
	{
		if (root != NULL)
			Destroy(root);

		if (tree.root == NULL)
			root = NULL;
		else
			CopyTree(root, tree.root);
	}

	return *this;
}

#endif