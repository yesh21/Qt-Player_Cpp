//
// Created by twak on 11/11/2019.
//

#include "the_button.h"
#include <QFileInfo>


void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
}


void TheButton::clicked() {
    emit jumpTo(info);
}

void TheButton::searchBtn(QString hey) {

    QString path = info->url->toString(); //get the file path as a string
    QFileInfo file(path);
    QString name = file.baseName();

    if(hey == ""){
        setVisible(true);
    }
    else{
    if(hey != name){
        setHidden(true);
    }
    else{
        setVisible(true);
    }
    }
}
