#include "qatree.h"

bool QATree::IsAnswer(string qaText)
{
    int key = 0;
    bool isAnswer = false;

    if (Search(qaText, key))
    {
        if (IsLeaf(key))
        {
            isAnswer = true;
        }
    }

    return isAnswer;
}

bool QATree::CreateQuestionAnswer(string newQuestion, string newAnswer,
                                  string alternativeQA)
{
    int key = 0;
    bool created = false;

    if (root == NULL)
    {
        Insert(newQuestion, 0);
        Insert(newAnswer, 1);
        Insert(alternativeQA, -1);

		created = true;
    }
    else
    {
        if (ScalingRequired(root))
        {
            nodeScale++;
            ScaleNodes(root, nodeScale);
        }

        /* Search for the alternate answer. Store off the key if it is found */
        if (Search(alternativeQA, key))
        {
            if (IsLeaf(key))
            {
                /* Replace the existing alternate answer with a new question*/
                ReplaceInfo(key, newQuestion);
             
                /* Insert the presumably correct answer to the right of the answer */
                Insert(newAnswer, key + 1);

                /* Insert the existing, alternative answer to the left of the answer */
                Insert(alternativeQA, key - 1);

                created = true;
            }
            else
                cout << "Error: \"" << alternativeQA << "\" is a question." << endl;
        }
        else
            cout << "Error: Unable to find answer: \"" << alternativeQA << "\"." << endl;
    }

    return created;
}

bool QATree::GetNextQA(string question, string &answer, int qaPath){

    int parentKey;
    int siblingKey;

    if (Search(question, parentKey))
    {
        if (!IsLeaf(parentKey)){
            if (qaPath == CORRECT_PATH)
                Navigate(parentKey, answer, siblingKey, RIGHT_LINK);
            else if (qaPath == INCORRECT_PATH)
                Navigate(parentKey, answer, siblingKey, LEFT_LINK);
            else
            {
                cout << "Error: Incorrect question/ answer path defined";
                return false;
            }

            return true;
        }
    }

    return false;
}

bool QATree::GetFirstQA(string &question){

    bool found = false;

    if (root != NULL)
    {
        question = root->info;
        found = true;
    }

    return found;
}

QATree::QATree()
{
    nodeScale = DEFAULT_SCALE;
}

QATree::~QATree()
{
}

istream & operator >>( istream & input, QATree & QA)
{
    int key;
    string line;

    input >> key;
    getline(input, line);

    size_t p2 = line.find_last_not_of(' ');
    
    if (p2 != std::string::npos)
    {
        size_t p1 = line.find_first_not_of(' ');

        if (p1 == std::string::npos)
            p1 = 0;
        
        line = line.substr(p1, (p2-p1)+1);
    }

    QA.Insert(line, key);

    return input;
}

ostream & operator <<(ostream & output, QATree & QA)
{
    StringNode* currentNode = QA.root;
    queue< StringNode* > q;

    q.push(currentNode);

    while (!q.empty()) {

        currentNode = q.front();
        q.pop();

        if (currentNode->lLink != NULL)
            q.push(currentNode->lLink);

        if (currentNode->rLink != NULL)
            q.push(currentNode->rLink);


        output << currentNode->key << " " << currentNode->info << endl;
    }
    
    return output;
}