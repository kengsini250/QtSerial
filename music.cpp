#include "music.h"

Music::Music(QString _dir)
{
    dir=_dir;
    setMedia(QUrl::fromLocalFile(dir));
    setVolume(100);
}

void Music::getInt(int _i)
{
   i=_i;
}
