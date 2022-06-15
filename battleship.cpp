#include "battleship.h"
#include "ui_battleship.h"
#include "tile.h"
#include <utility>
#include <QMouseEvent>

Battleship::Battleship(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Battleship)
{

    tile_pressed = NULL;
    attack = "";

    player1_setup = new Setup;
    player1_setup->setModal(true);
    player1_setup->addPlayerLabel("Player 1");
    player1_setup->exec();
    player1_ships_ = player1_setup->getPlayer()->getShips();
    player1 = player1_setup->getPlayer();

    player2_setup = new Setup;
    player2_setup->setModal(true);
    player2_setup->addPlayerLabel("Player 2");
    player2_setup->exec();
    player2_ships_ = player2_setup->getPlayer()->getShips();
    player2 = player2_setup->getPlayer();



    ui->setupUi(this);
    QGraphicsView *player1_view = ui->Board_graphicsView;
    player1_scene = new QGraphicsScene;
    player1_view->setScene(player1_scene);

    QGraphicsView *player2_view = ui->Board_graphicsView_2;
    player2_scene = new QGraphicsScene;
    player2_view->setScene(player2_scene);

    player1_board = new Board;
    player2_board = new Board;


    addShipsToBoard(player1_ships_, player1_board);
    addShipsToBoard(player2_ships_, player2_board);
    for(unsigned int i = 0; i < player1_board->get_tiles().size(); i++) {
        player1_scene->addItem(player1_board->get_tiles()[i]);
        connect(player1_board->get_tiles()[i], &Tile::TileSelected, this, &Battleship::TileSelectedSlot);
        connect(player2_board->get_tiles()[i], &Tile::TileSelected, this, &Battleship::TileSelectedSlot);
        player2_scene->addItem(player2_board->get_tiles()[i]);
    }



    // Set player name labels
    this->ui->player1_label->setText("Name: " + QString::fromStdString(player1->getName()));
    this->ui->player1_label->setAlignment(Qt::AlignCenter);

    this->ui->player2_label->setText("Name: " + QString::fromStdString(player2->getName()));
    this->ui->player2_label->setAlignment(Qt::AlignCenter);

    setTurn(player1);


}

//void Battleship::mousePressEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//    if(event->button() == Qt::RightButton) {
//        qDebug() << "Mouse pressed yay!";
//    }
//}

void Battleship::addShipsToBoard(std::vector<ship*> ships, Board *b)
{
    for(unsigned int i = 0; i < ships.size(); i++) {
         std::vector< std::pair<int, int> > coords = ships[i]->getCoords();
         for(unsigned int j = 0; j < coords.size(); j++) {
             int row = coords[j].first;
             int col = coords[j].second;
             for(unsigned int k = 0; k < b->get_tiles().size(); k++) {
                 if(b->get_tiles()[k]->get_row() == row && b->get_tiles()[k]->get_col() == col) {
                     b->get_tiles()[k]->setHasShip();
                     ships[i]->addTile(b->get_tiles()[k]);
                 }
             }
         }
    }
}

void Battleship::showShips(std::vector<ship*> ships)
{
    for(unsigned int ship = 0; ship < ships.size(); ship++) {
        for(unsigned int tile = 0; tile < ships[ship]->getTiles().size(); tile++) {
            ships[ship]->getTiles()[tile]->showShip();
            ships[ship]->getTiles()[tile]->update();
        }
    }
}

void Battleship::setTurn(Player *player)
{
    turn = player;
    this->ui->turn_label->setText("Turn: " + QString::fromStdString(player->getName()));
    this->ui->turn_label->setAlignment(Qt::AlignCenter);

    if(player == player1) {     //disable player 2's options
        this->ui->player2attack_comboBox->setDisabled(true);
        this->ui->player2confirm_pushButton->setDisabled(true);
        this->ui->Board_graphicsView->setDisabled(true);

        this->ui->player1attack_comboBox->setDisabled(false);
        this->ui->player1confirm_pushButton->setDisabled(false);
        this->ui->Board_graphicsView_2->setDisabled(false);

    }
    else {      //disable player 1's options
        this->ui->player2attack_comboBox->setDisabled(false);
        this->ui->player2confirm_pushButton->setDisabled(false);
        this->ui->Board_graphicsView_2->setDisabled(true);

        this->ui->player1attack_comboBox->setDisabled(true);
        this->ui->player1confirm_pushButton->setDisabled(true);
        this->ui->Board_graphicsView->setDisabled(false);
    }
}

void Battleship::takeTurn(Player* player)
{

    QComboBox * a;
    if(player == player1) {
        a = this->ui->player1attack_comboBox;
    }
    else {
        a = this->ui->player2attack_comboBox;
    }

    if(a->currentText() == "Single Shot") {
        qDebug() << "Single shot.";
        attack = "single";

    }
    else if(a->currentText() == "Scatter Shot") {
        qDebug() << "Scatter shot.";
        attack = "scatter";
        a->removeItem(1);

    }
    else if(a->currentText() == "Napalm Strike") {
        qDebug() << "Napalm Strike.";
        attack = "napalm";
        if(a->itemData(1, Qt::DisplayRole) == "Napalm Strike") {
            a->removeItem(1);
        }
        else {
            a->removeItem(2);
        }
    }


}





Battleship::~Battleship()
{
    delete ui;
}

void Battleship::TileSelectedSlot(Tile *t)
{
    tile_pressed = t;
    if(attack == "single") {
        if(tile_pressed->hasShip()) {
            tile_pressed->setHit();
            turn->addOneToScore();
        }
        else {
            tile_pressed->setMiss();
        }
        tile_pressed->update();

    }
    else if(attack == "scatter") {
        if(turn == player1) {
            for(unsigned int i = 0; i < player2_board->get_tiles().size(); i++) {
                Tile * tile = player2_board->get_tiles()[i];
                if( (tile->get_row() == t->get_row() && tile->get_col() == t->get_col() ) ||
                        (tile->get_row() == t->get_row() + 1 && tile->get_col() == t->get_col() ) ||
                        (tile->get_row() == t->get_row() - 1 && tile->get_col() == t->get_col() ) ||
                        (tile->get_row() == t->get_row() && tile->get_col() == t->get_col() + 1 ) ||
                        (tile->get_row() == t->get_row() && tile->get_col() == t->get_col() - 1 )
                        ) {
                    if(tile->hasShip()) {
                        tile->setHit();
                        turn->addOneToScore();
                    }
                    else {
                        tile->setMiss();
                    }
                }
            }
        }
        else {
                for(unsigned int i = 0; i < player1_board->get_tiles().size(); i++) {
                    Tile * tile = player1_board->get_tiles()[i];
                    if((tile->get_row() == t->get_row() && tile->get_col() == t->get_col() ) ||
                            (tile->get_row() == t->get_row() + 1 && tile->get_col() == t->get_col() ) ||
                            (tile->get_row() == t->get_row() - 1 && tile->get_col() == t->get_col() ) ||
                            (tile->get_row() == t->get_row() && tile->get_col() == t->get_col() + 1 ) ||
                            (tile->get_row() == t->get_row() && tile->get_col() == t->get_col() - 1 )
                            ) {
                        if(tile->hasShip()) {
                            tile->setHit();
                            turn->addOneToScore();
                        }
                        else {
                            tile->setMiss();
                        }
                    }
            }

        }
        t->update();

    }
    else if(attack == "napalm") {
        if(turn == player1) {
            for(unsigned int i = 0; i < player2_board->get_tiles().size(); i++) {
                Tile * tile = player2_board->get_tiles()[i];
                if(tile->get_row() == t->get_row()) {
                    if(tile->hasShip()) {
                        tile->setHit();
                        turn->addOneToScore();
                    }
                    else {
                        tile->setMiss();
                    }
                }
            }
        }
        else {
                for(unsigned int i = 0; i < player1_board->get_tiles().size(); i++) {
                    Tile * tile = player1_board->get_tiles()[i];
                    if(tile->get_row() == t->get_row()) {
                        if(tile->hasShip()) {
                            tile->setHit();
                            turn->addOneToScore();
                        }
                        else {
                            tile->setMiss();
                        }
                    }
            }

        }
        t->update();
    }

    if(player1->getScore() == 17 || player2->getScore() == 17) {
        if(turn == player1) {
            this->ui->player1score_label->setText("Score: " + QString::number(player1->getScore()));
            this->ui->player1score_label->setAlignment(Qt::AlignCenter);

        }
        else {
            this->ui->player2_score_label->setText("Score: " + QString::number(player2->getScore()));
            this->ui->player1score_label->setAlignment(Qt::AlignCenter);

        }
        this->ui->Board_graphicsView->setDisabled(true);
        this->ui->Board_graphicsView_2->setDisabled(true);
        QLabel *label = new QLabel(this);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setText("Congrats, " + QString::fromStdString(turn->getName()) + ". You win!!!");
        label->setAlignment(Qt::AlignTop);
        label->setGeometry(10,10,30,80);
        label->setAlignment(Qt::AlignCenter);
        this->ui->verticalLayout->addWidget(label);

    }
    else {
        if(turn == player1) {
            this->ui->player1score_label->setText("Score: " + QString::number(player1->getScore()));
            this->ui->player1score_label->setAlignment(Qt::AlignCenter);
            setTurn(player2);
        }
        else {
            this->ui->player2_score_label->setText("Score: " + QString::number(player2->getScore()));
            this->ui->player1score_label->setAlignment(Qt::AlignCenter);
            setTurn(player1);
        }

    }



}








void Battleship::on_player1view_pushButton_pressed()
{
    if(this->ui->player1view_pushButton->text() == "View your ships") {
        this->ui->player1view_pushButton->setText("Hide your ships");
    }
    else {
        this->ui->player1view_pushButton->setText("View your ships");
    }
    showShips(player1_ships_);
}


void Battleship::on_player2view_pushButton_pressed()
{
    if(this->ui->player2view_pushButton->text() == "View your ships") {
        this->ui->player2view_pushButton->setText("Hide your ships");
    }
    else {
        this->ui->player2view_pushButton->setText("View your ships");
    }
    showShips(player2_ships_);
}




void Battleship::on_player1confirm_pushButton_clicked()
{
    takeTurn(player1);

}

void Battleship::on_player2confirm_pushButton_clicked()
{
    takeTurn(player2);

}




