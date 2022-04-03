#!/bin/sh
extra_c_file="cmdLineParser.c"
gcc ../lib/$extra_c_file $1 -lpthread -I../include -I../lib -o $1.exe
