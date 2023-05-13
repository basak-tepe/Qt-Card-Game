#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QFont>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QImage>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QRandomGenerator>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // create a QApplication object
    QWidget *widget = new QWidget; // create a QWidget object

    // create a QLabel widget and set its text
    QLabel *label = new QLabel("Matching Cards Game", widget); // create a QLabel widget
    QFont font("Arial", 24);
    label->setFont(font); // set the font on the label widget

    QLabel *scoreLabel = new QLabel("Score: 0", widget); // create a score display QLabel widget
    QFont font2("Arial", 16);
    scoreLabel->setFont(font2);

    QLabel *triesLabel = new QLabel("Number of tries Remaining: 50", widget); // create a try count display QLabel widget
    QFont font3("Arial", 16);
    triesLabel->setFont(font3);


    QPushButton *newGameButton = new QPushButton("New Game", widget); // create a new game QPushButton widget
    QFont font4("Arial", 16);
    newGameButton->setFont(font4);
    newGameButton->setMinimumSize(QSize(100, 50)); // sets the minimum size to be 100 x 50 pixels




    //responsive design
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout(widget);

    hlayout1->addWidget(label);
    vlayout->addLayout(hlayout1);

    hlayout2->addWidget(scoreLabel);
    hlayout2->addWidget(triesLabel);
    hlayout2->addWidget(newGameButton);
    vlayout->addLayout(hlayout2);





    QGridLayout *gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(10); // set the spacing between cards

    // create 6 x 5 cards
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 6; ++col) {
            QPushButton *card = new QPushButton(widget);
            card->setFixedSize(100, 100); // set the fixed size of the card

            // set the front and back image for the card


            int checkedCount = 0;
            // connect the card clicked signal to the slot that flips the card
            QObject::connect(card, &QPushButton::clicked, [=](){
                qDebug() << "Card clicked!";
                    card->setStyleSheet("background-color: blue;");
                    card->setChecked(true);

            });


            gridLayout->addWidget(card, row, col); // add the card to the grid layout


        }

    }
    vlayout->addLayout(gridLayout);


    widget->setLayout(vlayout);

    widget->resize(800, 600); // set the size of the widget
    widget->show(); // show the widget




    return app.exec(); // start the application event loop
}
