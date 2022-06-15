#include "tile.h"

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>
#include <QtWidgets>
#include <string>

Tile::Tile()
{
    ship_ = false;
    show_ship_ = false;
    hit_ = false;
    miss_ = false;
}

QRectF Tile::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

// define the actual shape of the object
QPainterPath Tile::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

// called by Qt to actually display the point
void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(QColor(220, 220, 220, 255)));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    if(show_ship_) {
        painter->setBrush(QBrush(QColor(44,53,57, 255)));
        painter->drawRect(QRect(this->x_ + 5, this->y_ + 5, this->width_ - 10, this->width_ - 10));
    }
    else if(hit_) {
        painter->setBrush(QBrush(QColor(253, 88, 0, 255)));
        painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    }
    else if(miss_){
        painter->setBrush(QBrush(QColor(0, 51, 102, 255)));
        painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    }

    QString row = QString::fromStdString(std::to_string(this->get_row()));
    QString col = QString::fromStdString(std::to_string(this->get_col()));
    QString s = col + row;
    painter->drawText(this->boundingRect(), s);
    painter->setBrush(b);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    Q_UNUSED(event);

     if(event->button() == Qt::RightButton) {

         if(this->hasShip()) {
             hit_ = true;
         }
         else if(!this->hasShip()) {
             miss_ = true;
         }
         emit TileSelected(this);

     }
     this->update();

}
