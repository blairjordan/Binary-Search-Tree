/*! \class BSTType
 *  \brief Defines a binary search tree data structure.
 *
 *  Defines a binary search tree data structure.
 *
 *  \author Blair Jordan
 *  \version 5.0
 *  \date 16-MAY-2009
 *
 * <pre>
 *  Revision  Name        Date         Description
 *  1         B. Jordan   2-MAY-2009   Created.
 *  2         B. Jordan   8-MAY-2009   Added key to NodeType.
 *                                     Added protected navigation function.
 *                                     Created depth-first and key search functions.
 *  3         B. Jordan   16-MAY-2009  Created IsLeaf and ReplaceInfo functions.
 *  4         B. Jordan   20-MAY-2009  Added detailed doxygen comments.
 *  5         B. Jordan   20-MAY-2009  Incorporated scaling functionality from qatree
 *  6         B. Jordan   20-MAY-2009  Fixed return flags CreateQuestionAnswer and
 *                                     GetNextQA errors identified in test plan.
 * </pre>
*/

#ifndef _BSTTYPE_H
#define	_BSTTYPE_H

#include "binarytree.h"
#include <iostream>

using namespace std;

template <class elemType>
class BSTType : public BinaryTreeType<elemType>
{
public:

	/*! Default constructor for a binary search tree. */
	BSTType();

	/*! Destructor for a binary search tree. */
	virtual ~BSTType();

	/*! Copy constructor for a binary search tree.
	 *  \param tree A binary search tree object reference. 
	 */
	BSTType(const BSTType& tree);

	/*! Inserts a new item into the tree.
	 *  \param newItem The new data to be inserted into the tree.
	 *  \param key A unique identifier for the item .
	 */
	void Insert(const elemType newItem, int key);

	/*! Searches for an item in the tree depth-first.
	 *  \param searchItem The search item.
	 *  \retval key The key of the search item (if found).
	 *  \retval true If the search item is found.
	 *  \retval false If the search item is not found .
	 */
	bool Search(elemType &searchItem, int &key) const;

	/*! Searches for a node via key and, if found, replaces info.
	 *  \param key The uniquely identifying key for the search element.
	 *  \param newElement The item containing new info.
	 *  \retval true If the key is found, and info is replaced.
	 *  \retval false If the key was not found, and info was not replaced.
	 */
	bool ReplaceInfo(int key, elemType &newElement);

protected:
    
	/*! Stores the current scale of tree nodes */
    int nodeScale;
	
	/*! Returns true if tree nodes require scaling before adding additional
	 *  items.
	 *  \param parent The root node of the tree to check.
	 *  \retval true If scaling is required to avoid collision.
	 *  \retval false If scaling is not required.
	 */
	bool ScalingRequired(NodeType<elemType> *parent);

	/*! Returns true if tree nodes require scaling before adding additional
	 *  items.
	 *  \param parent The root node of the tree to scale.
	 *  \param newScale The new scale for the tree.
	 */
	void ScaleNodes(NodeType<elemType> *p, int newScale);

	/*! Returns true if an item is a leaf node, otherwise false is returned.
	 *  \retval true If an item is found and has no children.
	 *  \retval false If an item is not found or has children. 
	 */
	bool IsLeaf(const int key);

	/*! Attempts returning a sibling of a designated parent node
	 * \param key The uniquely identifying key of the parent node
	 * \param direction The direction of the link (LEFT_LINK or RIGHT_LINK)
	 * \retval elemFound The sibling element, if found
	 * \retval keyFound The sibling key, if found
	 * \retval true If sibling is successfully navigated
	 * \retval false If sibling navigation is unsuccessful
	 */
	bool Navigate(int key, elemType &elemFound, int &keyFound, int direction) const;
	
	/*! Recursively searches for a node and returns the item, if found
	 * \param currentNode The parent node to search from
	 * \param searchItem The item being searched
	 * \retval true If the node is found
	 * \retval false If the node is not found
	 */
	bool SearchNode(NodeType<elemType>* currentNode, NodeType<elemType>* &searchItem) const;
	
	/*! Inserts a new node into the binary search tree
	 * \param newNode The node item to insert into the 
	 * \param parentNode The parent node of the current new node
	 */
	void Insert(NodeType<elemType>* &newNode, NodeType<elemType>* &parentNode);
};

template <class elemType>
bool BSTType<elemType>::IsLeaf(const int key)
{
    elemType elemInfo;
    int keyFound;

    if ( !Navigate(key, elemInfo, keyFound, LEFT_LINK)
     && (!Navigate(key, elemInfo, keyFound, RIGHT_LINK)))
        return true;
    else
        return false;
}

template <class elemType>
void BSTType<elemType>::Insert(const elemType newItem, int key)
{
	NodeType<elemType> *newNode;
	newNode = new NodeType<elemType>;

	newNode->info = newItem;
    newNode->key = key;

	newNode->lLink = NULL;
	newNode->rLink = NULL;

	if (this->root == NULL)
	{
		this->root = newNode;
	}
	else
	{
		Insert(newNode, this->root);
	}
}

template <class elemType>
void BSTType<elemType>::Insert(NodeType<elemType>* &newNode, NodeType<elemType>* &parentNode)
{
	if (parentNode == NULL)
		cout << "Error: Unable to insert node. Parent not found." << endl;
        else
        {

		if (newNode->key < parentNode->key)
		{
			if (parentNode->lLink == NULL)
				parentNode->lLink = newNode;
			else
				Insert(newNode, parentNode->lLink);
		}
		else if (newNode->key > parentNode->key)
		{
			if (parentNode->rLink == NULL)
				parentNode->rLink = newNode;
			else
				Insert(newNode, parentNode->rLink);
		}
		else
		{
			cout << "Error: Unable to insert duplicate node." << endl;
		}
	}
}

template <class elemType>
bool BSTType<elemType>::Search(elemType &searchItem, int &key) const
{
    bool found = false;

    NodeType<elemType> *searchNode = new NodeType<elemType>;
    searchNode->info = searchItem;

    if (SearchNode(this->root, searchNode))
    {
        key = searchNode->key;
        found = true;
    }
    else
        found = false;
    
    return found;
}

template <class elemType>
bool BSTType<elemType>::SearchNode(NodeType<elemType>* currentNode, NodeType<elemType>* &searchItem) const
{
    bool found = false;

    if ((!found) && currentNode != NULL)
    {
        if (currentNode->info == searchItem->info)
        {
            searchItem->key = currentNode->key;
            found = true;
        }
        else
        {
            found = SearchNode(currentNode->lLink, searchItem);

            if (!found)
            {
                found = SearchNode(currentNode->rLink, searchItem);
            }
        }
    }
    
    return found;
}

template <class elemType>
bool BSTType<elemType>::Navigate(int key, elemType &elemFound, int &keyFound, int direction) const
{
    NodeType<elemType> *current;
    bool found = false;

    if (this->root == NULL)
        cout << "Error: Cannot search an empty tree." << endl;
    else
    {
        current = this->root;

        while (current != NULL && !found)
        {
            if (current->key == key)
            {
                found = true;
            }
            else if (current->key > key)
                current = current->lLink;
            else
                current = current->rLink;
        }
    }

    if (found && (direction == LEFT_LINK) && (current->lLink != NULL)){
        elemFound = current->lLink->info;
        keyFound = current->lLink->key;
    } 
    else if (found && (direction == RIGHT_LINK) && (current->rLink != NULL))
    {
        elemFound = current->rLink->info;
        keyFound = current->rLink->key;
    }
    else
        found = false;

    return found;
}

template <class elemType>
bool BSTType<elemType>::ReplaceInfo(int key, elemType &newElement)
{
    NodeType<elemType> *current;
    bool found = false;

    if (this->root == NULL)
        cout << "Error: Cannot search an empty tree." << endl;
    else
    {
        current = this->root;

        while (current != NULL && !found)
        {
            if (current->key == key)
            {
                found = true;
                current->info = newElement;
            }
            else if (current->key > key)
                current = current->lLink;
            else
                current = current->rLink;
        }
    }

    return found;
}

template <class elemType>
bool BSTType<elemType>::ScalingRequired(NodeType<elemType> *parent) {

    bool required = false;

    if (parent != NULL && !required) {
        required = ScalingRequired(parent->lLink);

        if (parent->lLink != NULL) {
            if ((parent->key - parent->lLink->key) == 1)
                required = true;
        }

        if (!required) {

            required = ScalingRequired(parent->rLink);

            if (parent->rLink != NULL) {
                if ((parent->key - parent->rLink->key) == -1)
                    required = true;
            }
        }
    }

    return required;
}

template <class elemType>
void BSTType<elemType>::ScaleNodes(NodeType<elemType> *p, int newScale) {

    if (p != NULL) {

        ScaleNodes(p->lLink, newScale);

        if (nodeScale != DEFAULT_SCALE)
            p->key = (p->key * newScale);
        else
            p->key = ((p->key / nodeScale - 1) * newScale);

        ScaleNodes(p->rLink, newScale);
    }
}

template <class elemType>
BSTType<elemType>::BSTType()
{
}


template <class elemType>
BSTType<elemType>::~BSTType()
{
}

#endif
