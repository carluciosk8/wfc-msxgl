#!/bin/bash
# ____________________________
# ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │   ▄▄▄                ▄▄
# ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
# █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
# ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘                 ▀▀
#  by Guillaume 'Aoineko' Blanchard under CC BY-SA license
#────────────────────────────────────────────────────────────────────
clear

MSXGL_DIR=/home/carlucio/MSXgl

if type -P node; then
	node $MSXGL_DIR/engine/script/js/build.js $1 $2 $3 $4 $5 $6 $7 $8 $9
else
	$MSXGL_DIR/tools/build/Node/node $MSXGL_DIR/engine/script/js/build.js $1 $2 $3 $4 $5 $6 $7 $8 $9
fi