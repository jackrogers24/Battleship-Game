#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QWidget>
#include "tile.h"

class Board
{
    //Q_OBJECT
public:
    Board();
    std::vector<Tile*> get_tiles() { return tiles_; }
    void add_tile(Tile* tile) { tiles_.push_back(tile); }


private:
    std::vector<Tile*> tiles_;
};

#endif // BOARD_H
