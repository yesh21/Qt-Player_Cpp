//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
}

void ThePlayer::SetPosition(int position){
    setPosition(position);
}

void ThePlayer::skipBack(bool skip){
    if(!skip)
    setPosition(position()-5000);
}

void ThePlayer::skipForward(bool skip){
    if(!skip)
    setPosition(position()+5000);
}

void ThePlayer::setPlay(bool flipPlay)
{
    playValue = !flipPlay;
}

void ThePlayer::click(bool click){
    if(playValue){
     play();
    }
   else{
        pause();
    }
    setPlay(playValue);
}
