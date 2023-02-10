#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w = nullptr;

void slow_sort(Array& toSort){
    for (uint i=0; i<toSort.size(); i++)
    {
        for (uint j=0; j<toSort.size(); j++)
        {
            if (toSort[j] > toSort[i])
                toSort.swap(i, j);
        }
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(slow_sort); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
