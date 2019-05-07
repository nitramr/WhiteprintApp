﻿#ifndef PROPERTYSTROKE_H
#define PROPERTYSTROKE_H

#include <QWidget>
#include <QPixmap>
#include "src/widgets/buttongroup.h"
#include "src/item/stroke.h"

namespace Ui {
class propertyStroke;
}

class PropertyStroke : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyStroke(QWidget *parent = nullptr);
    explicit PropertyStroke(Stroke stroke, QWidget *parent = nullptr);
    ~PropertyStroke();

    void setStroke(Stroke stroke);
    Stroke stroke() const;

private:
    Ui::propertyStroke *ui;

    Stroke m_stroke;
    QPixmap m_colorPreview;
    ButtonGroup *m_position;
    ButtonGroupButton * btn_center;
    ButtonGroupButton * btn_outer;
    ButtonGroupButton * btn_inner;

    void drawStroke(Stroke stroke);
    void connectSlots();
    void disconnectSlots();

private slots:
    void updateStroke();

signals:
    void hasChanged(bool);
};

#endif // PROPERTYSTROKE_H