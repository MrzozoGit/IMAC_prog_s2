#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin) {
    // stop statement = condition + return (return stop the function even if it does not return anything)
    if(origin.size() <= 1) {
        return;
    }

    // initialisation
    Array& first = w->newArray(origin.size()/2);
    Array& second = w->newArray(origin.size()-first.size());

    // split
    for (size_t i = 0; i < first.size(); i++)
        first[i] = origin[i];
    for (size_t i = 0; i < second.size(); i++)
        second[i] = origin[i + first.size()];

	// recursiv splitAndMerge of lowerArray and greaterArray
    splitAndMerge(first);
    splitAndMerge(second);

	// merge
    merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result) {
    uint index = 0, cFirst = 0, cSecond = 0;

    while (cFirst < first.size() && cSecond < second.size()) {
        if (first[cFirst] < second[cSecond])
            result[index++] = first[cFirst++];
        else
            result[index++] = second[cSecond++];
    }

    if (cFirst < first.size()) {
        for (uint i = cFirst; i < first.size(); i++)
            result[index++] = first[i];
    } else if (cSecond < second.size()) {
        for (uint i = cSecond; i < second.size(); i++)
            result[index++] = second[i];
    }
}

void mergeSort(Array& toSort) {
    splitAndMerge(toSort);
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
	w->show();

	return a.exec();
}
