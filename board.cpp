#include "board.h"
#include <QDebug>

Board::Board()  // Constructor
{
    for(int row = 0; row < 10; row++) {

        for(int col = 0; col < 10; col++) {

            Tile * t = new Tile();
            t->set_row(row + 1);
            t->set_col(col + 1);
            t->set_x(col*40);
            t->set_y(row*40);
            this->add_tile(t);


        }
    }
}
