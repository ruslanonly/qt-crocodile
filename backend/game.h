
#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRandomGenerator>
#include "server.h"
#include <QThread>



class Game : public QObject
{
    Q_OBJECT
private:
    enum MessageCodes {
        Guess = 1,
        UpdateImage,
        GameStarted,
        GameEnded,
        Drawer,
        Guesser,
        WrongAnswer,
        SetNickname,
        GameEndedDrawer,
        GameEndedGuesser
    };

public:
    Game(Server *server);

    void updateImage(QByteArray &newImage);
    void startGame();
    void waitGame(QTcpSocket* socket);
    void parseMessage(QTcpSocket* socket, int code, QByteArray message);
    void removePlayer(QTcpSocket* socket);
    void checkAnswer(QTcpSocket* socket, QString guess);
    void endGame(QString gameResult);
    void restartGame(QString lastGameStatus);
private:
    Server *server;

    QList<QString> *wordList = new QList<QString>({"подпись", "вырез", "гранит", "кругозор", "блузка", "фараон", "клапан", "ёж", "вымя", "турист", "колготки", "стоп-кран", "питание", "свёрток", "дочерь", "шампунь", "броня", "зайчатина", "гимназист", "стелька", "подделка", "виза", "затычка", "решение", "алкоголь", "шуруп", "воровка", "колодец", "кабан", "команда", "бордель", "ловушка", "буква", "опера", "сектор", "математика", "пароварка", "невезение", "глубина", "штука", "справочник", "вождь", "хобот", "ширинка", "усталость", "служитель", "жар", "спальная", "видео", "рот", "просьба", "фишка", "рукопись", "ракетчик", "каблук", "шрифт", "палец", "ножка", "халва", "черника", "незнайка", "компания", "работница", "мышь", "исследование", "кружка", "мороженое", "сиденье", "пулемёт", "печь", "солист", "свёкла", "стая", "зелье", "дума", "посылка", "коготь", "семафор", "брат", "различие", "плоскостопие", "двигатель", "сфера", "тюльпан", "затвор", "внедорожник", "самурай", "стан", "алгоритм", "параграф", "глаз", "медалист", "пульт", "поводок", "подлежащее", "ор", "бунт", "удочка", "лес", "диспетчер", "монитор", "вдова", "пиратство", "астролог", "сосед", "пуп", "изобретатель", "чума", "танец", "затишье", "пластелин", "йог", "маска", "блоха", "судьба", "сияние", "рукавица", "филе", "заплыв", "сёмга", "гиппопотам", "мастер", "походка", "ландыш", "яблоня", "кляча", "лиса", "свёртываемость", "раствор", "соты", "солод", "спорт", "шифер", "прощение", "стопка", "побег", "простота", "запах", "беседа", "варенье", "пароль", "актёр", "вырубка", "гвоздь", "шкаф", "скальпель", "гонг", "профессор", "казан", "скорбь", "извоз", "добавка", "тропа", "шеф", "космонавт", "грифель", "лауреат", "ромб", "борец", "звон", "канистра", "олимпиада", "оплата", "спирт", "баян", "перекрёсток", "влажность", "лотерея", "насморк", "оправдание", "мушкетёр", "мороз", "утюг", "санитария", "опрятность"});

    bool isGameRunning;
    int playerCount;

    QTcpSocket *currentDrawer;
    QByteArray currentImage;
    QString currentWord;

    QMap<QTcpSocket*, QString> socketToPlayer;
};

#endif // GAME_H
