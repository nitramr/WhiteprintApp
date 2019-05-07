#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

#include "workspace/tool_itemproperties.h"
#include "workspace/tool_outliner.h"
//#include "designer/canvas.h"
//#include "designer/canvasframe.h"
#include "item/itembase.h"
#include "item/artboard.h"
#include "designer/canvasscene.h"
#include "designer/canvasview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Outliner * m_outliner;
    ItemProperties * m_properties;
    CanvasView * m_canvas;
    CanvasScene * m_scene;

    QDockWidget * m_outlinerDock;
    QDockWidget * m_propertiesDock;


public slots:
    void setActiveItem(AbstractItemBase *item);

};

#endif // MAINWINDOW_H