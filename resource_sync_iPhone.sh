#!/bin/sh

#  resource_sync.sh
#
#  Created by Luke on 11/6/11.
#  Copyright 2011 __MyCompanyName__. All rights reserved.

echo "forcing refresh of javascript files..."
echo "target:${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}/src"

if [ -d "${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}/src" ]; then
	rm -r /${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}/src
fi
if [ -d "${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}/hd" ]; then
	rm -r /${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}/hd
fi

cp -R ../Resources/src/ ${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}/src
cp -R ../Resources/hd/ ${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}/hd

find ../scripting -type f -name '*.js' -exec cp {} ${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH} \;
find ../Resources -maxdepth 1 -type f -name '*.js' -exec cp {} ${BUILT_PRODUCTS_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH} \;
