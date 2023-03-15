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

/**
 * @brief define indexMin and indexMax as the first and the last index of toSearch
 * @param array array of int to process
 * @param toSearch value to find
 * @param indexMin first index of the value to find
 * @param indexMax last index of the value to find
 */
void binarySearchAll(Array& array, int toSearch, int& indexMin, int& indexMax) {
    int start = 0;
    int end = array.size();
    int mid = (start+end)/2;
    indexMin = indexMax = binarySearch(array, toSearch);

    while(indexMin > start && array[indexMin-1]==toSearch) {
        indexMin--;
    }

    while(indexMax < end && array[indexMax+1]==toSearch) {
        indexMax++;
    }
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchAllWindow(binarySearchAll);
	w->show();

	return a.exec();
}
