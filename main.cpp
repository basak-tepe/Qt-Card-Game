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
    QApplication app(argc, argv);
    QWidget *widget = new QWidget;

    QLabel *label = new QLabel("Matching Cards Game", widget);
    QFont font("Arial", 24);
    label->setFont(font);

    QLabel *scoreLabel = new QLabel("Score: 0", widget);
    QFont font2("Arial", 16);
    scoreLabel->setFont(font2);

    QLabel *triesLabel = new QLabel("Number of tries Remaining: 50", widget);
    QFont font3("Arial", 16);
    triesLabel->setFont(font3);

    QPushButton *newGameButton = new QPushButton("New Game", widget);
    QFont font4("Arial", 16);
    newGameButton->setFont(font4);
    newGameButton->setMinimumSize(QSize(100, 50));

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
    gridLayout->setSpacing(10);

    // Create a list to store the cards
    QList<QPushButton*> cards;

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 6; ++col) {
            QPushButton *card = new QPushButton(widget);
            card->setFixedSize(100, 100);

            // Set the front and back text for the card
            QString frontText = QString("Card (%1, %2)").arg(row).arg(col);
            QString backText = "Back";

            card->setText(backText); // Set the initial text to the back side

            // Connect the card clicked signal to the slot that flips the card
            QObject::connect(card, &QPushButton::clicked, [=]() {
                if (card->text() == backText) {
                    card->setText(frontText); // Flip to the front text
                } else {
                    card->setText(backText); // Flip to the back text
                }
            });

            gridLayout->addWidget(card, row, col);
            cards.append(card); // Add the card to the list
        }
    }

    vlayout->addLayout(gridLayout);
    widget->setLayout(vlayout);

    widget->resize(800, 600);
    widget->show();

    return app.exec();
}
