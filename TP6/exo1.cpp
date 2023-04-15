#include "tp6.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;

void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount) {
	/**
	  * Make a graph from a matrix
	  * first create all nodes, add it to the graph then connect them
	  * this->appendNewNode
	  * this->nodes[i]->appendNewEdge
	  */
    for(int i=0; i<nodeCount; i++) {
        GraphNode* newNode = new GraphNode(i);
        this->appendNewNode(newNode);
    }

    for(int i=0; i<nodeCount; i++) {
        for(int j=0; j<nodeCount; j++) {
            if(adjacencies[i][j] != 0)
                this->nodes[i]->appendNewEdge(this->nodes[j], adjacencies[i][j]);
        }
    }
}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[]) {
	/**
	  * Fill nodes array by travelling graph starting from first and using recursivity
	  */
    GraphNode* currentNode = first;
    Edge* currentEdge = first->edges;
    visited[first->value]=true;
    nodes[nodesSize] = first;
    nodesSize++;

    while(currentEdge != nullptr) {
        if(!visited[currentEdge->destination->value])
            deepTravel(currentEdge->destination, nodes, nodesSize, visited);
        currentEdge = currentEdge->next;
    }
}

void Graph::wideTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[]) {
	/**
	 * Fill nodes array by travelling graph starting from first and using queue
	 * nodeQueue.push(a_node)
	 * nodeQueue.front() -> first node of the queue
	 * nodeQueue.pop() -> remove first node of the queue
	 * nodeQueue.size() -> size of the queue
	 */
	std::queue<GraphNode*> nodeQueue;
	nodeQueue.push(first);

    Edge* currentEdge = first->edges;
    while(!nodeQueue.empty()) {
        GraphNode* firstNode = nodeQueue.front();
        nodeQueue.pop();
        visited[first->value] = true;
        nodes[nodesSize] = firstNode;
        nodesSize++;

        while(currentEdge != nullptr) {
            if(!visited[currentEdge->destination->value])
                nodeQueue.push(currentEdge->destination);
            currentEdge = currentEdge->next;
        }
    }
}

bool Graph::detectCycle(GraphNode *first, bool visited[]) {
	/**
	  Detect if there is cycle when starting from first
	  (the first may not be in the cycle)
	  Think about what's happen when you get an already visited node
	**/

    Edge* currentEdge = first->edges;
    visited[first->value]=true;

    while(currentEdge != nullptr) {
        if(!visited[currentEdge->destination->value]){
            if(detectCycle(currentEdge->destination, visited))
                return true;
        }else return true;
        currentEdge = currentEdge->next;
    }

    return false;
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 150;
	w = new GraphWindow();
	w->show();

	return a.exec();
}
