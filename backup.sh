#!/bin/bash

VOL="/media/evg/Evg"
DATE=`date +%d-%m-%y.%H-%M`
FNAME=backup-$DATE.tar.gz
SRC="*"
DEST="$VOL/backup/project"
echo $DEST/$FNAME
if mount | grep $VOL;
then

tar -cpzf $DEST/$FNAME $SRC

else

echo "No flash drive";

exit 0;

fi
