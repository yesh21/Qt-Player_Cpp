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
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>
#include "player_layout.h"
#include "volume.h"
#include "video_slider.h"
#include "skip_buttons.h"
#include "playpause.h"
#include "videolength_label.h"
#include "video_widget.h"
#include "fullscreen_button.h"
#include "videosearch.h"
#include "nextvideo_button.h"

using namespace std;

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);
     int index = 0;
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
                    out . push_back(TheButtonInfo( url , ico ,index ) ); // add to the output list
                } else {
                    QString thumb = f.left( f .length() - 5) +"def.png";
                    if (QFile(thumb).exists()) { // if a png thumbnail exists
                        QImageReader *imageReader = new QImageReader(thumb);
                        QImage sprite = imageReader->read(); // read the thumbnail
                        if (!sprite.isNull()) {
                            QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                            QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                            out . push_back(TheButtonInfo( url , ico ,index  ) ); // add to the output list
                        }
                    }
                }
            } else {
                QString thumb = f.left( f .length() - 5) +"def.png";
                if (QFile(thumb).exists()) { // if a png thumbnail exists
                    QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico ,index  ) ); // add to the output list
                    }
                }
            }index++;
            }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << Qt::endl;

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
    VideoScreen *videoWidget = new VideoScreen();

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QGridLayout *layout = new QGridLayout();
    buttonWidget->setLayout(layout);


    QScrollArea *videoScroller = new QScrollArea();
    videoScroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    videoScroller->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QFrame *inner = new QFrame(videoScroller);

    QLineEdit *searchBoxParent = new QLineEdit();
    videoSearch *searchBox = new videoSearch(videos, searchBoxParent);
    //need to connect here and update the videos vector to _videos from the searchBox object
    searchBox->connect(searchBox,SIGNAL(textChanged(QString) ),searchBox,SLOT(search(QString)));

    for ( int i = 0; i < static_cast<int>(searchBox->_filteredVideos.size()); i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        label *buttonLabel = new label();
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        searchBox->connect(searchBox,SIGNAL(textChanged(QString) ),button, SLOT(searchBtn(QString)));
        searchBox->connect(searchBox,SIGNAL(textChanged(QString) ),buttonLabel, SLOT(searchlabel(QString)));
        buttons.push_back(button);

        //as it shows filtered videos according to search
        QString Qstr = searchBox->_filteredVideos.at(i).url->toString();
        string label = Qstr.toStdString();
        size_t found = label.find_last_of("/");
        label = label.substr(found+1);
        QString qstr = QString::fromStdString(label);
        buttonLabel->setText(qstr); //adds a label with the filename underneath each thumbnail
        layout->addWidget(button,0,i);
        layout->addWidget(buttonLabel,1,i);
        button->init(&videos.at(i));
    }
    inner->setLayout(layout);
    videoScroller->setWidget(inner);
    videoScroller->setWidgetResizable(true);

    VolumeButton *muteButton = new VolumeButton(buttonWidget);
    VolumeSlider *volumeSlider = new VolumeSlider(buttonWidget);

    volumeSlider->connect(volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    volumeSlider->connect(volumeSlider, SIGNAL(valueChanged(int)), muteButton, SLOT (changeIcon(int)));
    //volume slider changing is connected to the player and the mute button
    muteButton->connect(muteButton, SIGNAL(mute(bool)), player, SLOT(setMuted(bool)));
    muteButton->connect(muteButton, SIGNAL(moveSlider(int)), volumeSlider, SLOT (moveSlider(int)));
    //mute button is connected to the player and slider
    VideoSlider *videoSlider = new VideoSlider(buttonWidget);

    player->connect(player, SIGNAL(durationChanged(qint64)), videoSlider, SLOT (SetRange(qint64)));
    player->connect(player, SIGNAL(positionChanged(qint64)), videoSlider, SLOT (SetValue(qint64)));
    videoSlider->connect(videoSlider, SIGNAL(valueChanged(int)), player, SLOT (SetPosition(int)));
    //player and video slider are mutually connected

    ForwardButton *forwardSkipBtn = new ForwardButton(buttonWidget);
    BackwardButton *backwardSkipBtn = new BackwardButton(buttonWidget);
    PlayButton *playBtn = new PlayButton(buttonWidget);

    forwardSkipBtn->connect(forwardSkipBtn, SIGNAL(clicked(bool)), player, SLOT(skipBack(bool)));
    backwardSkipBtn->connect(backwardSkipBtn, SIGNAL(clicked(bool)), player, SLOT(skipForward(bool)));
    //skip buttons connected to the player

    playBtn->connect(playBtn, SIGNAL(clicked(bool)), player, SLOT (click(bool)));
    player->connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), playBtn, SLOT (setState(QMediaPlayer::State)));

    NextButton *nextBtn = new NextButton(buttonWidget);
    PrevButton *backBtn = new PrevButton(buttonWidget);

    nextBtn->connect(nextBtn, SIGNAL(clicked()), player, SLOT(nextVideo()));
    backBtn->connect(backBtn, SIGNAL(clicked()), player, SLOT(prevVideo()));
    //this buttons connected to the player so it goes to next button while clicked

    LengthLabel *length_label = new LengthLabel(buttonWidget);
    LengthLabel *duration_label = new LengthLabel(buttonWidget);
    duration_label->setWhatsThis("duration_label");
    length_label->setWhatsThis("length_label");

    player->connect(player, SIGNAL(positionChanged(qint64)), length_label, SLOT (setLength(qint64)));
    player->connect(player, SIGNAL(durationChanged(qint64)), duration_label, SLOT (setLength(qint64)));
    //as video changes, length and duration labels will change

    videoWidget->setFullScreen(false); //starts off not in fullscreen

    FullScreenButton *fullScreen = new FullScreenButton(buttonWidget);
    muteButton->click();

    fullScreen->connect(fullScreen, SIGNAL(clicked(bool)), videoWidget, SLOT (setFullScr(bool)));
    //button connected to the video, to set it to fullscreen

    QComboBox *playrate = new QComboBox(buttonWidget);
    // for selecting playrate

    playrate->addItem("0.5x speed",QVariant(0.5));
    playrate->addItem("1x speed",QVariant(1));
    playrate->addItem("2x speed",QVariant(2));
    playrate->addItem("4x speed",QVariant(4));
    playrate->setCurrentIndex(1);

    QFrame *frame = new QFrame();
    QHBoxLayout *buttonsBox = new QHBoxLayout();
    buttonsBox->addWidget(backBtn);
    buttonsBox->addWidget(forwardSkipBtn);
    buttonsBox->addWidget(playBtn);
    buttonsBox->addWidget(backwardSkipBtn);
    buttonsBox->addWidget(nextBtn);
    buttonsBox->addWidget(muteButton);
    frame->setLayout(buttonsBox);
    //added a frame to set all buttons in hboxlayout
    frame->setWhatsThis("buttons");

    //connected combobox with playrate settting slot
    playrate->connect(playrate,SIGNAL(activated(int)),player, SLOT(doPlayRate(int)));
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
    top->addWidget(volumeSlider);
    top->addWidget(videoSlider);
    top->addWidget(length_label);
    top->addWidget(duration_label);
    top->addWidget(fullScreen);
    top->addWidget(searchBox);
    top->addWidget(playrate);
    top->addWidget(frame);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
