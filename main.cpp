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
#include <QList>
#include <QStringList>
#include <algorithm>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *widget = new QWidget;

    QLabel *label = new QLabel("Matching Cards Game", widget);
    QFont font("Arial", 24);
    label->setFont(font);
    int score = 0;
    int triesRemaining = 50;

    QLabel *scoreLabel = new QLabel(QString("Score: %1").arg(score), widget);
    QFont font2("Arial", 16);
    scoreLabel->setFont(font2);

    QLabel *triesLabel = new QLabel(QString("Number of tries Remaining: %1").arg(triesRemaining), widget);
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

    // Create a list of animal names
    QStringList animalNames;
    animalNames << "Cat" << "Dog" << "Elephant" << "Lion" << "Giraffe"
                << "Monkey" << "Tiger" << "Bear" << "Kangaroo" << "Penguin"
                << "Snake" << "Zebra" << "Hippo" << "Owl" << "Koala";

    // Double the list of animal names
    animalNames += animalNames;

    // Shuffle the animal names
    std::random_shuffle(animalNames.begin(), animalNames.end());
    QPushButton *firstCard = nullptr; // Store the first opened card
    QPushButton *secondCard = nullptr; // Store the second opened card

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 6; ++col) {
            QPushButton *card = new QPushButton(widget);
            card->setFixedSize(100, 100);

            QString text = animalNames.at(row * 6 + col);
            QString backText = "?";
            card->setText(backText);
            QObject::connect(card, &QPushButton::clicked, [card,&firstCard,&secondCard,text,&cards,&score,&triesRemaining,backText, &scoreLabel, &card, &triesLabel]() mutable {
                if (card->text() == backText) {
                    if (firstCard == nullptr) {
                        firstCard = card;
                        firstCard->setText(text);
                    } else if (secondCard == nullptr) {
                        secondCard = card;
                        secondCard->setText(text);

                        // Check if the cards match
                        if (firstCard->text() == secondCard->text()) {
                            // Cards match
                            score += 1;
                            scoreLabel->setText(QString("Score: %1").arg(score));

                            firstCard->setEnabled(false);
                            secondCard->setEnabled(false);

                            firstCard = nullptr;
                            secondCard = nullptr;

                            // Disable the matched cards


                            // Check if the game is over (all cards matched)
                            if (score == 15) {
                                // Game over
                                // Display a message or perform any necessary actions
                            }
                        } else {
                            // Cards do not match
                            triesRemaining -= 1;
                            triesLabel->setText(QString("Number of tries Remaining: %1").arg(triesRemaining));
                            QTimer::singleShot(1000, [backText,&firstCard,&secondCard, &cards]()mutable  {
                                // Flip the cards back to the back text
                                firstCard->setText(backText);
                                secondCard->setText(backText);
                                firstCard = nullptr;
                                secondCard = nullptr;

                                // Enable all other cards
                                for (QPushButton *c : cards) {
                                    c->setEnabled(true);
                                }
                            });
                        }
                    }
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




