#include "ship.h"


#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>
#include <QtWidgets>
#include <string>


ship::ship(std::pair<int, int> start, int length, std::string orientation)
{
    if(orientation == "Horizontal") {   // ship is horizontal
        for(int i = 0; i < length; i++) {
            std::pair<int, int> pair = std::make_pair(start.first, start.second + i);
            addCoords(pair);
        }
    }
    else {  // ship is vertical
        for(int i = 0; i < length; i++) {
            std::pair<int, int> pair = std::make_pair(start.first + i, start.second);
            addCoords(pair);
        }
    }
    destroyed_ = false;
}


