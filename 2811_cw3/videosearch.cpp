#include "videosearch.h"
#include <QFileInfo>

void videoSearch::search(QString text) {
    _filteredVideos.clear();

    for (int i = 0; i < (int)_allVideos.size(); i++) {
        QString path = _allVideos[i].url->toString(); //get the file path as a string
        QFileInfo file(path);
        QString name = file.baseName(); //get the base name of the file, eg: "name.mp4" would give "name"
        if (text == name) {
            _filteredVideos.push_back(_allVideos[i]);
        }
    }
}

void label::searchlabel(QString text){
    if (text == "") {
        setVisible(true);
    }
    else{
        setVisible(false);
    }
}
