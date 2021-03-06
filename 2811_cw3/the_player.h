//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

using namespace std;

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    vector<TheButtonInfo>* infos;
    vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;

public:
    size_t videoindex = 0;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
        mTimer = new QTimer(NULL);
        mTimer->setInterval(1000); // 1000ms is one second between ...
        mTimer->start();
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton*>* b, vector<TheButtonInfo>* i);
    void setPlay(bool flipPlay);

private slots:

    void playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void SetPosition(int position); //slot used for our video slider
    void skipBack(bool skip);
    void skipForward(bool skip);
    void doPlayRate(int x);
    //slots used for our skip buttons
    void click(bool playValue); //slot for the play/pause button
    void nextVideo();
    void prevVideo();

private:
    bool playValue = false;
};

#endif //CW2_THE_PLAYER_H
