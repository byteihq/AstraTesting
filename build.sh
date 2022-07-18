#! /bin/bash

echo "Installing g++"
sudo apt install g++ -y

echo "Building AstraTesting"
mkdir _build
g++ -I./Commons/ -I./Tests/ -I./third-party/json/include/ ./Commons/Logger.cpp ./Commons/Terminal.cpp ./Commons/Config.cpp ./Tests/BaseTest.cpp ./demo/main.cpp -o ./_build/AstraTesting
cp ./misc/config.json ./_build/config.json
mkdir ./_build/output
