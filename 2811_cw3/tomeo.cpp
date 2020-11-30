/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for sports enthusiasts...
 *
 *  2811 cw3 : twak
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include <QScrollArea>
#include <QFrame>
#include "player_layout.h"
#include "volume.h"
#include "video_slider.h"
#include "skip_buttons.h"

using namespace std;

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                QImage sprite = imageReader->read(); // read the thumbnail
                if (!sprite.isNull()) {
                    QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                    QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                    out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                }
                else{
                    QString thumb = f.left( f .length() - 5) +"def.png";
                    if (QFile(thumb).exists()) { // if a png thumbnail exists
                        QImageReader *imageReader = new QImageReader(thumb);
                        QImage sprite = imageReader->read(); // read the thumbnail
                        if (!sprite.isNull()) {
                            QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                            QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                            out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                        }
                    }                    }
            }
            else{
                QString thumb = f.left( f .length() - 5) +"def.png";
                if (QFile(thumb).exists()) { // if a png thumbnail exists
                    QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                }
            }
            }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn( string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }

    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(layout);


    QScrollArea *videoScroller = new QScrollArea();
    QFrame *inner = new QFrame(videoScroller);

    for ( int i = 0; i < static_cast<int>(videos.size()); i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i));
    }
    inner->setLayout(layout);
    videoScroller->setWidget(inner);
    videoScroller->setWidgetResizable(true);

    VolumeButton *muteButton = new VolumeButton(buttonWidget);
    VolumeSlider *volumeSlider = new VolumeSlider(buttonWidget);

    volumeSlider->connect(volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    volumeSlider->connect(volumeSlider, SIGNAL(valueChanged(int)), muteButton, SLOT (changeIcon(int)));

    muteButton->connect(muteButton, SIGNAL(mute(bool)), player, SLOT(setMuted(bool)));
    muteButton->connect(muteButton, SIGNAL(moveSlider(int)), volumeSlider, SLOT (moveSlider(int)));

    VideoSlider *videoSlider = new VideoSlider(buttonWidget);

    player->connect(player, SIGNAL(durationChanged(qint64)), videoSlider, SLOT (SetRange(qint64)));
    player->connect(player, SIGNAL(positionChanged(qint64)), videoSlider, SLOT (SetValue(qint64)));
    videoSlider->connect(videoSlider, SIGNAL(valueChanged(int)), player, SLOT (SetPosition(int)));

    ForwardButton *forwardSkipBtn = new ForwardButton(buttonWidget);
    BackwardButton *backwardSkipBtn = new BackwardButton(buttonWidget);

    forwardSkipBtn->connect(forwardSkipBtn, SIGNAL(clicked(bool)), player, SLOT(skipBack(bool)));
    backwardSkipBtn->connect(backwardSkipBtn, SIGNAL(clicked(bool)), player, SLOT(skipForward(bool)));

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    // create the main window and layout
    QWidget window;
    ResponsiveLayout *top = new ResponsiveLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    // add the video and the buttons to the top level widget
    top->addWidget(videoWidget);
    top->addWidget(videoScroller);
    top->addWidget(muteButton);
    top->addWidget(volumeSlider);
    top->addWidget(videoSlider);
    top->addWidget(forwardSkipBtn);
    top->addWidget(backwardSkipBtn);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
