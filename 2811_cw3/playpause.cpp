#include "playpause.h"

void PlayButton::setState(QMediaPlayer::State state){
    if (state) {

            switch (state) {

            case QMediaPlayer::PlayingState:
                setEnabled(false);
                break;
            case QMediaPlayer::PausedState:
                setEnabled(true);
                break;
            }
        }
}

void PauseButton::setState(QMediaPlayer::State state){
    if (state) {

            switch (state) {
            case QMediaPlayer::StoppedState:
                setEnabled(true);
                break;
            case QMediaPlayer::PlayingState:
                setEnabled(true);
                break;
            case QMediaPlayer::PausedState:
                setEnabled(false);
                break;
            }
        }
}

