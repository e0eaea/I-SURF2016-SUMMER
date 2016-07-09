#include <QGraphicsView>
  #include <QGraphicsScene>
  #include <QGraphicsEllipseItem>
  #include <QMouseEvent>

  class MyQGraphicsView : public QGraphicsView
  {
      Q_OBJECT
  public:
      explicit MyQGraphicsView(QWidget *parent = 0);

  signals:

  public slots:
      void mousePressEvent(QMouseEvent * e);

  private:
      QGraphicsScene * scene;
  };
