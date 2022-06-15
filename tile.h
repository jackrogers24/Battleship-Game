#ifndef TILE_H
#define TILE_H


#include <QColor>
#include <QGraphicsItem>
#include <QObject>
#include <QWidget>


class Tile : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Tile();
    void set_row(int row) { row_ = row; }
    void set_col(int col) { col_ = col; }
    void set_x(int x) { x_ = x; }
    void set_y(int y) { y_ = y; }
    void setHit() { hit_ = true;}
    void setMiss() { miss_ = true;}

    int get_row() { return row_; }
    int get_col() { return col_; }
    int get_x() { return x_; }
    int get_y() { return y_; }
    void showShip() { show_ship_ = !show_ship_;}

    bool hasShip() { return ship_; }
    void setHasShip() { ship_ = true; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
signals:
    void TileSelected(Tile* t);
private:
    int row_;
    int col_;
    int x_;
    int y_;
    bool ship_; // if tile is occupied by a ship
    bool show_ship_;
    bool hit_;  // if tile is hit
    bool miss_;
    static const int width_ = 36;
};

#endif // TILE_H
