#!/bin/bash
mkdir attachments
cd attachments
for (( i=01; i<21; i++ ))
do
    curl https://loremflickr.com/800/400 -L > photo_$i.png
    sleep 0.2
done