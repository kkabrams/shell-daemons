#!/bin/sh
export PATH=/bin:/usr/bin:/usr/local/bin
cd /service/gemini
exec sudo -E -u gemini ./geminid "$1"
