#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "board.h"
#include "setup.h"
#include <QColor>
#include <QObject>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Battleship; }
QT_END_NAMESPACE

class Battleship : public QMainWindow
{
    Q_OBJECT

public:
    Battleship(QWidget *parent = nullptr);

//    void mousePressEvent(QMouseEvent * event);

    void addShipsToBoard(std::vector<ship*> ships, Board *b);
    void showShips(std::vector<ship*> ships);
    void setTurn(Player* player);

    void takeTurn(Player* player);




    ~Battleship();



private slots:

    void TileSelectedSlot(Tile* t);


    void on_player1view_pushButton_pressed();

    void on_player2view_pushButton_pressed();


    void on_player1confirm_pushButton_clicked();
    void on_player2confirm_pushButton_clicked();

private:
    Ui::Battleship *ui;
    QGraphicsScene *player1_scene;
    QGraphicsScene *player2_scene;
    Board *player1_board;
    Board *player2_board;

    Tile * tile_pressed;
    std::string attack;


    Setup * player1_setup;
    Setup * player2_setup;

    Player * player1;
    Player * player2;

    Player * turn = player1;

    std::vector<ship*> player1_ships_;
    std::vector<ship*> player2_ships_;

};
#endif // BATTLESHIP_H
