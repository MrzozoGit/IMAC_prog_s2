#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChildIndex(int nodeIndex) {
    return nodeIndex*2+1;
}

int Heap::rightChildIndex(int nodeIndex) {
    return nodeIndex*2+2;
}

void Heap::insertHeapNode(int heapSize, int value) {
	// use (*this)[i] or this->get(i) to get a value at index i
	int i = heapSize;
    (*this)[i] = value;
    while((i>0) && (*this)[i]>(*this)[(i-1)/2]) {
        this->swap(i, (i-1)/2);
        i = (i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex) {
	// use (*this)[i] or this->get(i) to get a value at index i
    int i_max = nodeIndex;

    int leftChildIndex = this->leftChildIndex(nodeIndex);
    if(leftChildIndex<heapSize) {
        i_max = (*this)[i_max]>(*this)[leftChildIndex] ? i_max : leftChildIndex;
    }

    int rightChildIndex = this->rightChildIndex(nodeIndex);
    if(rightChildIndex<heapSize) {
        i_max = (*this)[i_max]>(*this)[rightChildIndex] ? i_max : rightChildIndex;
    }

    if(nodeIndex != i_max) {
        this->swap(nodeIndex, i_max);
        this->heapify(heapSize, i_max);
    }
}

// A REVOIR
void Heap::buildHeap(Array& numbers) {
    for(uint i=0; i<numbers.size(); i++) {
        insertHeapNode(numbers.size(), numbers[i]);
    }
}

// A REVOIR
void Heap::heapSort() {
    for(uint i=0; i<this->size(); i++) {
        swap(0,i);
        heapify(i, 0);
    }
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
