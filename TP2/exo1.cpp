#include <QApplication>
#include <time.h>
#include <algorithm>

#include "tp2.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort) {
    for(uint i=0; i<toSort.size(); i++) {
        int minId = i;

        for (uint j=i; j<toSort.size(); j++) {
            if (toSort[j] < toSort[minId])
                minId = j;
        }

        toSort.swap(minId, i);
    }
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
