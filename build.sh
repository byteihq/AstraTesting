#! /bin/bash

sudo apt install g++ -y

g++ -I./Commons/ ./Commons/Logger.cpp ./Commons/Terminal.cpp ./demo/main.cpp -o AstraTesting
