 #!/usr/bin/env bash

 # Execute this file to install the miracle cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Miracle-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Miracle-Qt.app/Contents/MacOS/miracled /usr/local/bin/miracled
 sudo ln -s ${LOCATION}/Miracle-Qt.app/Contents/MacOS/miracle-cli /usr/local/bin/miracle-cli
