#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

#include <QObject>
#include <QWidget>

class Player
{
    //Q_OBJECT
public:
    Player(std::string name, std::vector<ship*> ships) { name_ = name;
                                                         ships_ = ships;
                             score_ = 0; }
    std::vector<ship*> getShips() { return ships_; }
    std::string getName() { return name_; }
    int getScore() { return score_; }
    void addOneToScore() { score_ = score_ + 1; }

private:
    std::string name_;
    int score_;
    std::vector<ship*> ships_;
};

#endif // PLAYER_H
