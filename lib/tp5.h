#ifndef TP5_H
#define TP5_H

#include "array.h"
#include "hashtable.h"
#include "mainwindow.h"
#include "thread.h"
#include "tp3.h"
#include <QStack>

namespace TP5
{
    extern std::vector<string> names;
}

class HashTableThread : public Thread
{

public:
	HashTableThread(MainWindow* mainWindow, HashTable& table, QObject *parent = nullptr)
		: Thread(parent), mainWindow(mainWindow), success(false), table(table) {}

	virtual bool succeeded() const {return success;}
	virtual const QString& message() const {return _message;}
	~HashTableThread() override{}

protected:
	MainWindow* mainWindow;
	QString _message;
	bool success;

	HashTable& table;
};

class HashTableInsertThread : public HashTableThread
{

public:
	HashTableInsertThread(MainWindow* mainWindow, HashTable& table, QObject *parent = nullptr)
		: HashTableThread(mainWindow, table, parent) {}
	void run() override;
    void assertHashTable(HashTable* table, std::vector<std::string> &content);

	~HashTableInsertThread() override{}
};

class HashTableContainsThread : public HashTableThread
{

public:
	HashTableContainsThread(MainWindow* mainWindow, HashTable& table, QObject *parent = nullptr)
		: HashTableThread(mainWindow, table, parent) {}
	void run() override;
    void assertHashTable(HashTable* table, std::vector<std::string> &content);

	~HashTableContainsThread() override{}
};


class HashWindow : public MainWindow
{
public:
	typedef MainWindow Base;

	HashWindow(QWidget *parent=nullptr)
		: MainWindow(parent)
	{
        int n = qrand() % 20 + 8;
		table = &this->newHashTable(n);

		threads.push_back(new HashTableInsertThread(this, *table, this));
		threads.push_back(new HashTableContainsThread(this, *table, this));

		currentThread = threads.begin();
		workerThread = *currentThread;
		connect(workerThread, SIGNAL(finished()), this, SLOT(handleResult()));
	}

	HashTable& newHashTable(int size);
    void updateHashItems(int itemWidth, int& originX, int& originY);

	void handleResult() override;
    void updateScene() override;
    void updateLayoutItems(int itemWidth, int& originX, int& originY) override;

private:
	QVector<HashTable> tables;
    QVector<QVector<NodeGraphicsItem*> > hashItems;
	HashTable* table;
	QLinkedList<Thread*> threads;
	QLinkedList<Thread*>::iterator currentThread;
};

class MapWindow : public _TestMainWindow
{
public:
    typedef MainWindow Base;

    MapWindow(BinaryTree& tree, QWidget *parent=nullptr)
        : _TestMainWindow(parent) {
        QStack<Node*> nodes;
        nodes.push(&tree);
        while(!nodes.empty())
        {
            Node* node = nodes.pop();
            if (!node)
                break;
            this->nodes.push_back(node);
            if (node->get_left_child())
                nodes.push(node->get_left_child());
            if (node->get_right_child())
                nodes.push(node->get_right_child());
        }
        addBinaryNode(&tree);
        this->dirty = true;
    }
    virtual ~MapWindow() {}

private:
    QLinkedList<Thread*> threads;
    QLinkedList<Thread*>::iterator currentThread;
};


void buildHashTable(HashTable& table, std::string* names, int namesCount);

#endif // TP5_H
