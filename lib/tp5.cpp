#include "tp5.h"
#include <set>

HashTable &HashWindow::newHashTable(int size)
{
    tables.push_back(HashTable(size));
    HashTable& array = tables.last();
	this->dirty = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(MainWindow::instruction_duration / 3));
    return array;
}

void HashWindow::updateHashItems(int itemWidth, int &originX, int &originY)
{
    originY += scene.height() * 0.2f;

    for (QVector<NodeGraphicsItem*> items : hashItems)
    {
        int startX = 0.05 * width();
        for (NodeGraphicsItem* item : items)
        {
            item->setRect(startX, originY, itemWidth*1.5, itemWidth* 1.5f);
            startX += itemWidth * 2.f;
            if (startX + itemWidth * 2 > scene.width())
            {
                originY += itemWidth * 2.f;
                startX = qMax((50 + scene.width() - itemWidth * 2.f * items.size()) * 0.5,
                                            0.05 * scene.width());
            }
        }
        if (startX > originX)
            originX = startX;
        originY += itemWidth * 2;
    }
}

void HashTableInsertThread::run()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	try {
		qsrand(time(nullptr));

        assertHashTable(&table, TP5::names);

		_message = QString("Hash insertion correctly finished !");
		success = true;
	}
	catch(std::exception& e)
	{
		_message = QString(e.what());
	}
}

int hash(HashTable& t, string s)
{
	return ((int)s[0]) % t.size();
}

void HashTableContainsThread::run()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	try {
		qsrand(time(nullptr));

        assertHashTable(&table, TP5::names);

		_message = QString("Hash contains method works !");
		success = true;
	}
	catch(std::exception& e)
	{
		_message = QString(e.what());
    }
}

void HashWindow::handleResult()
{
	Base::handleResult();    
	this->dirty = true;

    if (currentThread == threads.end())
    {
        currentThread = threads.begin();
    }
    else
    {
        if (!(*currentThread)->succeeded())
            return;
        currentThread++;
    }

	if (currentThread != threads.end())
	{
		workerThread = *currentThread;
		connect(workerThread, SIGNAL(finished()), this, SLOT(handleResult()));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        workerThread->start();
    }
}

void HashWindow::updateScene()
{
    while (hashItems.size() < tables.size())
    {
        HashTable& array = tables[hashItems.size()];
        hashItems.push_back(QVector<NodeGraphicsItem*>());
        for (uint i=0; i < array.size(); ++i)
        {
            NodeGraphicsItem* item = new NodeGraphicsItem(array.get(i));
            hashItems.last().push_back(item);
            toAdd.push_back(item);
        }
    }

    uint i=0;
    for (QVector<NodeGraphicsItem*>& numbers : hashItems)
    {
        HashTable& array = tables[i];
        for (uint j=0; j < array.size(); ++j)
        {
            if ((int)j >= numbers.size())
            {
                numbers.push_back(new NodeGraphicsItem(array.get(j)));
                // toAdd.push_back(numbers[j]);
                dirty = true;
            }
            NodeGraphicsItem* item = numbers[j];
            QVariant data(QString::number(j) + ": " +QString::fromStdString(array.get(j)));
            if (item->data() != data)
            {
                item->setData(data);
                dirty = true;
            }
            item->displayDefault();
        }
        ++i;
    }
    Base::updateScene();
}

void HashWindow::updateLayoutItems(int itemWidth, int& originX, int& originY)
{
    Base::updateLayoutItems(itemWidth, originX, originY);
    updateHashItems(itemWidth, originX, originY);
}


#ifdef EXO2
void HashTableInsertThread::assertHashTable(HashTable *table, std::vector<string>& content){}
void HashTableContainsThread::assertHashTable(HashTable *table, std::vector<std::string> &content){}
#else
/**
 * @brief Test function, do not modify
 */
void HashTableInsertThread::assertHashTable(HashTable *table, std::vector<string>& content)
{
    std::string* names = new std::string[table->size()];
    std::set<int> indexes;
    int inserted=0;

    for (size_t i=0; i<table->size(); ++i)
    {
        int value = qrand() % 20;
        if (indexes.count(value))
        {
            continue;
        }

        names[inserted] = content[value];
        inserted++;
    }

    buildHashTable(*table, names, inserted);

    for (size_t i=0; i<inserted; ++i)
    {
        string s = names[i];
        int index = table->hash(s);
        if (table->get(index) != s && table->hash(table->get(index)) != index)
        {
            QString message("%1 is not at %2, \"%3\" found instead !");
            throw std::runtime_error(message.arg(QString::fromStdString(s)).arg(index)
                                     .arg(QString::fromStdString(table->get(index))).toStdString());
        }
    }
}

/**
 * @brief Test function, do not modify
 */
void HashTableContainsThread::assertHashTable(HashTable *table, std::vector<std::string> &content)
{
    for (int i=0; i<5; i++)
    {
        int index = qrand() % 20;
        string s = TP5::names[index];
        bool contains = false;
        for (size_t i=0; i<table->size(); i++)
        {
            if (table->get(i) == s)
            {
                contains = true;
                break;
            }
        }

        if (table->contains(s) != contains)
        {
            QString message;
            if (contains)
                message = "%1 is in the table but you didn't find it";
            else
                message = "%1 is not in the table but you found it";
            throw std::runtime_error(message.arg(QString::fromStdString(s)).toStdString());
        }
    }
}
#endif


