/*! \class QATree
 *  \brief Defines a question and answer decision tree.
 *
 *  \author  B. Jordan
 *  \version 6.0
 *  \date 19-MAY-2009
 *
 * <pre>
 *  Revision  Name        Date         Description
 *  1         B. Jordan   3-MAY-2009   Created
 *  2         B. Jordan   10-MAY-2009  Added scaling functions
 *                                     Implemented CreateQuestionAnswer
 *  3         B. Jordan   14-MAY-2009  Added IsAnswer function
 *  4         B. Jordan   14-MAY-2009  Added input
 *  5         B. Jordan   14-MAY-2009  Overloaded input operator
 *  6         B. Jordan   19-MAY-2009  Added GetFirstQA function
 * </pre>
 */

#ifndef _QATREE_H
#define	_QATREE_H
#pragma warning (disable:4786)

#include "bsttype.h"
#include <string>
#include <queue>

const int DEFAULT_SCALE = 1;            // Defines the default node scale
const int CORRECT_PATH = 1;             // Defines the correct (right) path
const int INCORRECT_PATH = 0;           // Defines incorrect (left) path

typedef NodeType<string> StringNode;	
typedef BSTType<string> StringBST;

class QATree : public StringBST
{
public:
    
	/*! Default constructor for QATree */
    QATree();

	/*! Default destructor for QATree */
    virtual ~QATree();

    /*! Create a question or answer in the decision tree
	 *  \retval true If the previous answer is found and a new answer is created.
     *  \retval false If the previous answer is not found and a new answer is not created.
     *  \param newQuestion The new question to be created.
     *  \param newAnswer The answer to the question being created.
     *  \param alternateQA The alternate answer or new question.
     */
    bool CreateQuestionAnswer(string newQuestion, string newAnswer,
                              string alternateQA);

    /*! Get the next question or answer in the tree
	 *  \param question A string representing a question.
     *  \param qaPath Determines which questioning path to follow.
     *  \retval true If a correct answer is defined.
     *  \retval false If no correct answer is defined.
     *  \retval answer The predicted answer to a question
     */
    bool GetNextQA(string question, string &answer, int qaPath);
    
	/*! Get the first question in the tree
     *  \retval question The question string, if found.
     *  \retval false If root node has not been defined.
     *  \retval true If root node has been returned successfully.
     */
    bool GetFirstQA(string &question);

	/*! Return true if the text is found in the tree, and is an answer
	 *  \param qaText The question or answer text to search for in the tree
	 *	\retval true If the text is found, and is an answer
	 *	\retval false If the text is not found or is not an answer 
	 */
    bool IsAnswer(string qaText);

    /*! Overriden input operator for a QATree object */
    friend istream & operator >>( istream & input, QATree & QA);
	
    /*! Overriden output operator for a QATree object */
    friend ostream & operator <<( ostream & output, QATree & QA);
};


#endif

