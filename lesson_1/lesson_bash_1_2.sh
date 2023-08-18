#!/bin/bash
DIRECTORY="attachments"
if [ -d "$DIRECTORY" ]; then
    rm -rf $DIRECTORY
    echo "$DIRECTORY deleted"
else
    echo "$DIRECTORY doesn\`t exist."
fi