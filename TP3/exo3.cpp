#include "mainwindow.h"
#include "tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

struct SearchTreeNode : public Node {
    SearchTreeNode* left;
    SearchTreeNode* right;
    int value;

    void initNode(int value) {
        // init initial node without children
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

	void insertNumber(int value) {
        // create a new node and insert it in right or left child
        SearchTreeNode* newNode = new SearchTreeNode(value);
        SearchTreeNode* leftNode = this->left,* rightNode = this->right;

        if(value <= this->value) {
            if(leftNode == nullptr)
                leftNode = newNode;
            else
                leftNode->insertNumber(value);
        } else {
            if(rightNode == nullptr)
                rightNode = newNode;
            else
                rightNode->insertNumber(value);
        }
    }

	uint height() const	{
        // should return the maximum height between left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        SearchTreeNode* leftNode = this->left,* rightNode = this->right;
        int leftHeight = 1, rightHeight = 1, height = 1;

        if(leftNode) {
            leftHeight += leftNode->height();
        }

        if(rightNode) {
            rightHeight += rightNode->height();
        }

        return (leftHeight>rightHeight) ? leftHeight : rightHeight;
    }

	uint nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        SearchTreeNode* leftNode = this->left,* rightNode = this->right;
        int sum = 1;

        if(leftNode) {
            sum += leftNode->nodesCount();
        }

        if(rightNode) {
            sum += rightNode->nodesCount();
        }

        return sum;
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        if(this->left==nullptr && this->right==nullptr)
            return true;
        return false;
	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        // fill leaves array with all leaves of this tree
        if(this->isLeaf()) {
            leaves[leavesCount] = this;
            leavesCount++;
        } else {
            SearchTreeNode* leftNode = this->left,* rightNode = this->right;

            if(leftNode) {
                leftNode->allLeaves(leaves, leavesCount);
            }

            if(rightNode) {
                rightNode->allLeaves(leaves, leavesCount);
            }
        }
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with inorder travel
        SearchTreeNode* leftNode = this->left,* rightNode = this->right;

        if(leftNode) {
            leftNode->inorderTravel(nodes, nodesCount);
        }

        nodes[nodesCount] = this;
        nodesCount++;

        if(rightNode) {
            rightNode->inorderTravel(nodes, nodesCount);
        }
	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with preorder travel
        SearchTreeNode* leftNode = this->left,* rightNode = this->right;
        nodes[nodesCount] = this;
        nodesCount++;

        if(leftNode) {
            leftNode->preorderTravel(nodes, nodesCount);
        }

        if(rightNode) {
            rightNode->preorderTravel(nodes, nodesCount);
        }
	}

	void postorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with postorder travel
        SearchTreeNode* leftNode = this->left,* rightNode = this->right;

        if(leftNode) {
            leftNode->postorderTravel(nodes, nodesCount);
        }

        if(rightNode) {
            rightNode->postorderTravel(nodes, nodesCount);
        }

        nodes[nodesCount] = this;
        nodesCount++;
	}

	Node* find(int value) {
        // find the node containing value
        SearchTreeNode* leftNode = this->left,* rightNode = this->right;
        Node* result = nullptr;

        if(this->value == value) {
            result = this;
        } else if(leftNode && this->value > value) {
            result = leftNode->find(value);
        } else if(rightNode && this->value < value) {
            result = rightNode->find(value);
        }

        return result;
	}

    void reset() {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
        left = right = NULL;
    }

    SearchTreeNode(int value) : Node(value) {initNode(value);}
    ~SearchTreeNode() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

Node* createNode(int value) {
    return new SearchTreeNode(value);
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow<SearchTreeNode>();
	w->show();

	return a.exec();
}
