QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        player_layout.cpp \
        playpause.cpp \
        the_button.cpp \
        the_player.cpp \
        tomeo.cpp \
        video_slider.cpp \
        video_widget.cpp \
        videolength_label.cpp \
        videosearch.cpp \
        volume.cpp

HEADERS += \
    fullscreen_button.h \
    nextvideo_button.h \
    player_layout.h \
    playpause.h \
    the_button.h \
    the_player.h \
    video_slider.h \
    video_widget.h \
    videolength_label.h \
    videosearch.h \
    volume.h \
    skip_buttons.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

