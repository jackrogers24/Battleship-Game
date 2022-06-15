#ifndef SHIP_H
#define SHIP_H

#include "tile.h"

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QGraphicsItem>


class ship
{
//    Q_OBJECT
//    Q_INTERFACES(QGraphicsItem)
    int length_;
public:
    ship(std::pair<int, int> start, int length, std::string orientation);
    void addCoords(std::pair<int, int> p) { coords_.push_back(p); }
    virtual int getLength() const { return length_; }
    std::vector< std::pair<int, int> > getCoords() { return coords_; }
    void addTile(Tile* tile) { tiles_.push_back(tile); }
    std::vector<Tile*> getTiles() { return tiles_; }


protected:
    std::vector< std::pair<int, int> > coords_;
    std::vector<Tile*> tiles_;
    bool destroyed_;
};

class carrier : public ship {
public:
    carrier(std::pair<int, int> start, int length, std::string orientation) : ship(start, length, orientation) {}
    virtual int getLength() const { return length_; }

private:
    static const int length_ = 5;
};

class battleship : public ship {
public:
    battleship(std::pair<int, int> start, int length, std::string orientation) : ship(start, length, orientation) {}
    virtual int getLength() const { return length_; }

private:
    static const int length_ = 4;
};

class destroyer : public ship {
public:
    destroyer(std::pair<int, int> start, int length, std::string orientation) : ship(start, length, orientation) {}
    virtual int getLength() const { return length_; }

private:
    static const int length_ = 3;
};

class submarine : public ship {
public:
    submarine(std::pair<int, int> start, int length, std::string orientation) : ship(start, length, orientation) {}
    virtual int getLength() const { return length_; }

private:
    static const int length_ = 3;
};

class patrolboat : public ship {
public:
    patrolboat(std::pair<int, int> start, int length, std::string orientation) : ship(start, length, orientation) {}
    virtual int getLength() const { return length_; }

private:
    static const int length_ = 2;
};
#endif // SHIP_H
