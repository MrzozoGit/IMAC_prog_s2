#ifndef TP6_H
#define TP6_H

#include <QGraphicsLineItem>

#include "array.h"
#include "graph.h"
#include "mainwindow.h"
#include "thread.h"

class GraphWindow;

class GraphThread : public Thread
{

public:
    GraphThread(GraphWindow* mainWindow, QObject *parent = nullptr)
        : Thread(parent), mainWindow(mainWindow), success(false) {}

	virtual bool succeeded() const {return success;}
	virtual const QString& message() const {return _message;}
	virtual ~GraphThread() {}

protected:
    GraphWindow* mainWindow;
	QString _message;
	bool success;

    Graph* graph;
};

class GraphBuildThread : public GraphThread
{

public:
    GraphBuildThread(GraphWindow* GraphWindow, QObject *parent = nullptr)
        : GraphThread(GraphWindow, parent) {}
	void run() override;

	~GraphBuildThread() {}
};

class GraphDeepTravelThread : public GraphThread
{

public:
    GraphDeepTravelThread(GraphWindow* mainWindow, QObject *parent = nullptr)
        : GraphThread(mainWindow, parent) {}
	void run() override;

	~GraphDeepTravelThread() {}
};

class GraphWideTravelThread : public GraphThread
{

public:
    GraphWideTravelThread(GraphWindow* mainWindow, QObject *parent = nullptr)
        : GraphThread(mainWindow, parent) {}
	void run() override;

	~GraphWideTravelThread() {}
};

class GraphCycleDetectionThread : public GraphThread
{

public:
    GraphCycleDetectionThread(GraphWindow* mainWindow, QObject *parent = nullptr)
        : GraphThread(mainWindow, parent) {}
	void run() override;

	~GraphCycleDetectionThread() {}
};

class EdgeGraphicsItem : public QGraphicsLineItem
{
public:
	typedef QGraphicsLineItem Base;

    explicit EdgeGraphicsItem(const QGraphicsEllipseItem* source,
                              const QGraphicsEllipseItem* destination,
							  int distance, QGraphicsItem* parent=nullptr);
	void setDistance(int distance);
	void setPath(const QGraphicsEllipseItem *source, const QGraphicsEllipseItem *destination);
	const QGraphicsEllipseItem* sourceItem();
	const QGraphicsEllipseItem* destinationItem();

	void updateLayout();

	QPainterPath painterPath() const;
	QRectF boundingRect() const;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
			   QWidget *widget=nullptr) override;
	int distance() const;

	static QColor baseColor;

private:
	QString text;
	int _distance;
	const QGraphicsEllipseItem* source;
	const QGraphicsEllipseItem* destination;
};

class GraphGraphicsItem : public QGraphicsEllipseItem
{
public:
	typedef QGraphicsEllipseItem Base;

	explicit GraphGraphicsItem(const GraphNode* node, QGraphicsItem* parent=nullptr);
	explicit GraphGraphicsItem(const GraphNode* node, QGraphicsScene* scene);
	void setNode(const GraphNode* node);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
			   QWidget *widget=nullptr) override;
	const GraphNode *node() const;

	static QColor baseColor;

private:
	QString text;
	const GraphNode* _node;
	std::list<EdgeGraphicsItem*> edges;
};

class GraphWindow : public MainWindow
{
    Q_OBJECT

public:
	typedef MainWindow Base;

    GraphWindow(QWidget *parent=nullptr);
    virtual ~GraphWindow() {};

	Graph& newGraph(int size);
    Graph* getGraph();

    void clearGraph();

	int updateGraphItems(int itemWidth, int &maxY, int &maxX);

	void updateLayout() override;
	void handleResult() override;
	void updateScene() override;

public slots:
    void runThread()
    {
        QObject* source = sender();
        if (workerThread)
        {
            disconnect(workerThread, SIGNAL(finished()), this, SLOT(handleResult()));
            workerThread->quit();
            workerThread = nullptr;
        }

        QPushButton* button = dynamic_cast<QPushButton*>(source);
        if (button)
        {
            workerThread = this->threads[button];
            connect(workerThread, SIGNAL(finished()), this, SLOT(handleResult()));
            workerThread->start();
        }
    }

private:
	QVector<GraphGraphicsItem *> graphItems;
	QVector<QVector<EdgeGraphicsItem *> > edgeItems;
	Graph* graph;

    QMap<QObject*, Thread*> threads;


    QPushButton buildButton;
    QPushButton deepTravelButton;
    QPushButton wideTravelButton;
    QPushButton cycleButton;
};

#endif // TP6_H
