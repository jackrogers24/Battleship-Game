#ifndef SETUP_H
#define SETUP_H
#include "ship.h"
#include "player.h"

#include <QDialog>

namespace Ui {
class Setup;
}

class Setup : public QDialog
{
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = nullptr);
    ~Setup();


    void createPlayer(std::string name, std::vector<ship*> ships);
    Player* getPlayer();
    bool addShips();
    void addCoords(std::pair<int, int> coords) { occupied_.push_back(coords); }
    void addPlayerLabel(std::string player);



private slots:

    void on_submit_pushButton_clicked();

private:
    Ui::Setup *ui;
    std::vector<ship*> ships_;
    std::vector< std::pair<int, int> > occupied_;
    Player* p;

};

#endif // SETUP_H
