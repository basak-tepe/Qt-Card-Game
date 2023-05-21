#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
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
    QApplication app(argc, argv); //our single app

    QMainWindow *mw = new QMainWindow;

    QWidget *widget = new QWidget; //all of the application is contained inside this widget.


    //game title
    QLabel *label = new QLabel("Matching Cards Game", widget);
    QFont font("Helvetica", 32, QFont::Bold);
    label->setFont(font);
    label->setStyleSheet("color: black;");
    label->setAlignment(Qt::AlignCenter);

    int score = 0;
    int triesRemaining = 50;

    //score display
    QLabel *scoreLabel = new QLabel(QString("Score: %1").arg(score), widget);
    QFont font2("Arial", 16, QFont::Bold);
    scoreLabel->setFont(font2);
    scoreLabel->setStyleSheet("color: #10A19D;");

    //attempts display
    QLabel *triesLabel = new QLabel(QString("Number of tries Remaining: %1").arg(triesRemaining), widget);
    QFont font3("Arial", 16, QFont::Bold);
    triesLabel->setFont(font3);
    triesLabel->setStyleSheet("color: #10A19D;");

    //new game button
    QPushButton *newGameButton = new QPushButton("New Game", widget);
    QFont font4("Arial", 14);
    newGameButton->setStyleSheet("QPushButton {"
                                 "background-color: #FFF6BD;"
                                 "border: 5px dashed #86C8BC;" // Add border style
                                 "border-radius: 30px;" // Add border radius for rounded corners
                                 "color: black;"
                                 "}");


    newGameButton->setFont(font4);
    newGameButton->setMinimumSize(QSize(100, 50));

    //grid
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

    // Create a list to store the cards.
    // each card is of type qPushButton
    QList<QPushButton*> cards;

    // A list of animal names as card backs.
    QStringList animalNames;
    animalNames << "Cat" << "Dog" << "Elephant" << "Lion" << "Giraffe"
                << "Monkey" << "Tiger" << "Bear" << "Kangaroo" << "Penguin"
                << "Snake" << "Zebra" << "Hippo" << "Owl" << "Koala";

    // Double the list of animal names to form pairs.
    animalNames += animalNames;

    // Shuffle the animal names
    std::random_shuffle(animalNames.begin(), animalNames.end());
    QPushButton *firstCard = nullptr; // Store the first opened card
    QPushButton *secondCard = nullptr; // Store the second opened card


    // Create a function to reset the game state
    auto resetGame = [&]() {
        // Reset game variables
        score = 0;
        triesRemaining = 50;
        scoreLabel->setText(QString("Score: %1").arg(score));
        triesLabel->setText(QString("Number of tries Remaining: %1").arg(triesRemaining));

        // Reset card states
        for (QPushButton* card : cards) {
            card->setEnabled(true);
            card->setChecked(false);
            card->setText("?");
        }
    };

    //connect reset button to above.
    //clicked event (signal) calls the reset slot.
    QObject::connect(newGameButton, &QPushButton::clicked, resetGame);
    //QObject::connect(newGameButton, SIGNAL(clicked()), &app, SLOT(resetGame()));


    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 6; ++col) {
            QPushButton *card = new QPushButton(widget);
            card->setFixedSize(100, 100);

            card->setStyleSheet("QPushButton {"
                                "background-color: #FFF6BD;"
                                "border-radius: 40%;"
                                "border: 6px solid #86C8BC;"
                                "box-shadow: 0 2px 4px rgba(0, 0, 0, 0.3);"
                                "}");

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
                            triesRemaining -= 1;
                            triesLabel->setText(QString("Number of tries Remaining: %1").arg(triesRemaining));



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


                            //we wait a little to show the user that the cards do not match
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

    //grid
    vlayout->addLayout(gridLayout);
    widget->setLayout(vlayout);

    widget->setStyleSheet("background-color: white;");

    widget->resize(800, 600);


    //adding the widget to main window
    mw ->setCentralWidget(widget);
    mw -> setWindowTitle("Pairs Game");
    mw->show();

    return app.exec(); //running the app
}


