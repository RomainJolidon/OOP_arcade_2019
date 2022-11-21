#!/bin/sh
##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## allegro_install
##


git clone https://github.com/liballeg/allegro5.git /tmp/allegro5
cd /tmp/allegro5
cmake /tmp/allegro5
sudo make install -C /tmp/allegro5
sudo ldconfig
cd -
echo "Installation Done with Success !"