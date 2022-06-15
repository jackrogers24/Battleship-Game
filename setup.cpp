#include <utility>
#include "setup.h"
#include "ui_setup.h"

Setup::Setup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setup)
{
    ui->setupUi(this);
}

Setup::~Setup()
{
    delete ui;
}

void Setup::createPlayer(std::string name, std::vector<ship*> ships)
{
    p = new Player(name, ships);
}

Player *Setup::getPlayer()
{
    return p;
}




void Setup::on_submit_pushButton_clicked()
{
    occupied_.clear();
    if(addShips()) {
        createPlayer(this->ui->playername_textEdit->toPlainText().toStdString(), ships_);
        this->close();
    }

}



bool Setup::addShips() {
    // *****check carrier (length 5)*****
    if(ui->carrier_comboBox->currentText() == "Horizontal") {
        if(ui->carrier_spinBox_2->value() > 6) {    // out of bounds
            qDebug() << "Carrier placed out of bounds. Please try again.";
            return false;
        }
        else {      // valid placement, add coords to occupied coords (add ships after all are deemed valid)
            for(int i = 0; i < 5; i++) {
                addCoords(std::make_pair(ui->carrier_spinBox->value(), ui->carrier_spinBox_2->value() + i));
            }
        }
    }
    else {  // ship is vertical
        if(ui->carrier_spinBox->value() > 6) {      // out of bounds
            qDebug() << "Carrier placed out of bounds. Please try again.";
            return false;
        }
        else {      // valid placement
            for(int i = 0; i < 5; i++) {
                addCoords(std::make_pair(ui->carrier_spinBox->value() + i, ui->carrier_spinBox_2->value()));
            }
        }

    }

    // *****check battleship (length 4)*****
    if(ui->battleship_comboBox->currentText() == "Horizontal") {
        if(ui->battleship_spinBox_2->value() > 7) {    // out of bounds
            qDebug() << "Battleship placed out of bounds. Please try again.";
            return false;
        }
        else {      // in bounds, check/add coords to occupied coords (add ships after all are deemed valid)
            for(int i = 0; i < 4; i++) {
                std::pair<int, int> pair = std::make_pair(ui->battleship_spinBox->value(), ui->battleship_spinBox_2->value() + i);
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Battleship is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }
    }
    else {  // ship is vertical
        if(ui->battleship_spinBox->value() > 7) {      // out of bounds
            qDebug() << "Battleship placed out of bounds. Please try again.";
            return false;
        }
        else {      // valid placement
            for(int i = 0; i < 4; i++) {
                std::pair<int, int> pair = std::make_pair(ui->battleship_spinBox->value() + i, ui->battleship_spinBox_2->value());
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Battleship is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }

    }

    // *****check Destroyer (length 3)*****
    if(ui->destroyer_comboBox->currentText() == "Horizontal") {
        if(ui->destroyer_spinBox_2->value() > 8) {    // out of bounds
            qDebug() << "Destroyer placed out of bounds. Please try again.";
            return false;
        }
        else {      // in bounds, check/add coords to occupied coords (add ships after all are deemed valid)
            for(int i = 0; i < 3; i++) {
                std::pair<int, int> pair = std::make_pair(ui->destroyer_spinBox->value(), ui->destroyer_spinBox_2->value() + i);
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Destroyer is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }
    }
    else {  // ship is vertical
        if(ui->destroyer_spinBox->value() > 8) {      // out of bounds
            qDebug() << "Destroyer placed out of bounds. Please try again.";
            return false;
        }
        else {      // valid placement
            for(int i = 0; i < 3; i++) {
                std::pair<int, int> pair = std::make_pair(ui->destroyer_spinBox->value() + i, ui->destroyer_spinBox_2->value());
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Destroyer is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }

    }

    // *****check Submarine (length 3)*****
    if(ui->submarine_comboBox->currentText() == "Horizontal") {
        if(ui->submarine_spinBox_2->value() > 8) {    // out of bounds
            qDebug() << "Submarine placed out of bounds. Please try again.";
            return false;
        }
        else {      // in bounds, check/add coords to occupied coords (add ships after all are deemed valid)
            for(int i = 0; i < 3; i++) {
                std::pair<int, int> pair = std::make_pair(ui->submarine_spinBox->value(), ui->submarine_spinBox_2->value() + i);
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Submarine is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }
    }
    else {  // ship is vertical
        if(ui->submarine_spinBox->value() > 8) {      // out of bounds
            qDebug() << "Submarine placed out of bounds. Please try again.";
            return false;
        }
        else {      // valid placement
            for(int i = 0; i < 3; i++) {
                std::pair<int, int> pair = std::make_pair(ui->submarine_spinBox->value() + i, ui->submarine_spinBox_2->value());
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Submarine is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }

    }

    // *****check Patrol Boat (length 2)*****
    if(ui->patrolboat_comboBox->currentText() == "Horizontal") {
        if(ui->patrolboat_spinBox_2->value() > 9) {    // out of bounds
            qDebug() << "Patrol Boat placed out of bounds. Please try again.";
            return false;
        }
        else {      // in bounds, check/add coords to occupied coords (add ships after all are deemed valid)
            for(int i = 0; i < 2; i++) {
                std::pair<int, int> pair = std::make_pair(ui->patrolboat_spinBox->value(), ui->patrolboat_spinBox_2->value() + i);
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Patrol Boat is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }
    }
    else {  // ship is vertical
        if(ui->patrolboat_spinBox->value() > 9) {      // out of bounds
            qDebug() << "Patrol Boat placed out of bounds. Please try again.";
            return false;
        }
        else {      // valid placement
            for(int i = 0; i < 2; i++) {
                std::pair<int, int> pair = std::make_pair(ui->patrolboat_spinBox->value() + i, ui->patrolboat_spinBox_2->value());
                for(unsigned int j = 0; j < occupied_.size(); j++) {
                    if(pair == occupied_[j] ) {     // check if tile is already occupied
                        //boats are crossing, not allowed
                        qDebug() << "Patrol Boat is intersecting another ship. Please try again.";
                        return false;
                    }
                }
                addCoords(pair);
            }
        }
    }

    // *****All selections are valid, so let's create and place the ships*****
    qDebug() << "All ships are valid!!!";
    carrier *c = new carrier(std::make_pair(ui->carrier_spinBox->value(), ui->carrier_spinBox_2->value()),
                                   5,
                             ui->carrier_comboBox->currentText().toStdString());

    battleship *b = new battleship(std::make_pair(ui->battleship_spinBox->value(), ui->battleship_spinBox_2->value()),
                                   4,
                             ui->battleship_comboBox->currentText().toStdString());

    destroyer *d = new destroyer(std::make_pair(ui->destroyer_spinBox->value(), ui->destroyer_spinBox_2->value()),
                                   3,
                             ui->destroyer_comboBox->currentText().toStdString());

    submarine *s = new submarine(std::make_pair(ui->submarine_spinBox->value(), ui->submarine_spinBox_2->value()),
                                   3,
                             ui->submarine_comboBox->currentText().toStdString());

    patrolboat *p = new patrolboat(std::make_pair(ui->patrolboat_spinBox->value(), ui->patrolboat_spinBox_2->value()),
                                   2,
                             ui->patrolboat_comboBox->currentText().toStdString());

    ships_.insert(ships_.end(), {c, b, d, s, p});   // add ships to the vector
    qDebug() << ships_[4]->getLength();
    return true;

}

void Setup::addPlayerLabel(std::string player)
{
    this->ui->header_label->setText(QString::fromStdString(player) + ": Place Battleships and Enter Name.");
    this->ui->header_label->setAlignment(Qt::AlignCenter);
}
