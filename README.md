# qshot

## Description

Simple program to print screen i3 FreeBSD

## Dependencies

giblib libX11

## Install

complile with ./build.sh

add qshot to /usr/local/bin

%sudo cp qshot /usr/local/bin

add to i3 conifg

bindsym Print exec qshot qshot.png | xargs gimp


