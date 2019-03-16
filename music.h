#ifndef MUSIC_H
#define MUSIC_H

#include <QMediaPlayer>
#include <QString>

class Music : public QMediaPlayer
{
public:
    Music(QString _dir);
    void getInt(int _i);
private:
    int i;
    QString dir;
};

#endif // MUSIC_H
