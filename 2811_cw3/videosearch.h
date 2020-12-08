#ifndef VIDEOSEARCH_H
#define VIDEOSEARCH_H

#include <QPushButton>
#include <QStyle>
#include <QWidget>
#include <QLineEdit>
#include <vector>
#include "the_button.h"
#include <QLabel>

using namespace std;

class videoSearch : public QLineEdit {
    Q_OBJECT
public:
    videoSearch(vector<TheButtonInfo> videos, QWidget *parent) : QLineEdit(parent) {
        _allVideos = videos;
        _filteredVideos = videos;
        setPlaceholderText("search Video");
    }
public:
    vector<TheButtonInfo> _filteredVideos;
    vector<TheButtonInfo> _allVideos;
private slots:
    void search(QString text);
};

class label : public QLabel {
    Q_OBJECT
public:
    label() : QLabel() {
    }
private slots:
    void searchlabel(QString text);
};

#endif // VIDEOSEARCH_H
