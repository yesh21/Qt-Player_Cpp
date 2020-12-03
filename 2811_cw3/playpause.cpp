#include "playpause.h"
void PlayButton::setState(QMediaPlayer::State state){
    //if (state) {

            switch (state) {

            case QMediaPlayer::PlayingState:
                setEnabled(true);
                setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                break;
            case QMediaPlayer::PausedState:
                setEnabled(true);
                setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                break;
            }
      //  }
}
