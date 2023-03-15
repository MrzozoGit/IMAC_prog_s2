#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

int binarySearch(Array& array, int toSearch) {
    int start = 0;
    int end = array.size();

    while (start < end) {
        int mid = (start+end)/2;
        int midValue = array[mid];
        if(toSearch>midValue) {
            start = mid+1;
        } else if (toSearch<midValue) {
            end = mid;
        } else {
            int foundIndex = mid;
            return foundIndex;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchWindow(binarySearch);
	w->show();

	return a.exec();
}
