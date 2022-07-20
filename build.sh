#! /bin/bash

echo "Installing g++"
sudo apt install g++ -y
echo "Installing libcurl"
sudo apt install libcurl4-gnutls-dev -y

echo "Building AstraTesting"
mkdir _build
g++ -I./Commons/ -I./Tests/ -I./third-party/json/include/ ./Commons/Logger.cpp ./Commons/Terminal.cpp ./Commons/Config.cpp ./Tests/BaseTest.cpp ./Tests/InternetTest.cpp ./demo/main.cpp -lcurl -o ./_build/AstraTesting
cp ./misc/config.json ./_build/config.json
mkdir ./_build/output
