#!/bin/bash

VOL="/media/evg/Evg"
DATE=`date +%d-%m-%y.%H-%M`
FNAME=backup-$DATE.tar.gz
SRC="/home/evg/Games/k3"
DEST="$VOL/backup/project"
echo $DEST/$FNAME
if mount | grep $VOL;
then

tar -cvpzf $DEST/$FNAME $SRC

#cd $DEST && ls -t | sed -e '1,30d' | xargs -d '\n' rm -f

else

echo "No flash drive";

exit 0;

fi
