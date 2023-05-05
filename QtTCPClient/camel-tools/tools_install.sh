#!/bin/bash

# MSCL
cd ~/Downloads
MSCL_FILE="c++-mscl_65.0.0_amd64.deb"
if [ -e "$MSCL_FILE" ]; then
  echo "c++-mscl_65.0.0_amd64.deb is already exist"
else
  wget https://github.com/LORD-MicroStrain/MSCL/releases/latest/download/c++-mscl_65.0.0_amd64.deb
fi
echo "Install c++-mscl_65.0.0_amd64.deb"
sudo dpkg -i c++-mscl_65.0.0_amd64.deb
sudo apt install -f

echo "Write mscl rules"
touch 100-microstrain.rules
echo "SUBSYSTEM==\"tty\", ATTRS{idVendor}==\"199b\", ATTRS{idProduct}==\"3065\", PROGRAM=\"/bin/sh -c 'echo %s{serial} | sed s/^0000__.*/rtk/g | sed s/^0000.*/main/g | sed s/^2-00.*/aux/g'\", SYMLINK+=\"microstrain_%c\", MODE=\"0666\"" >> 100-microstrain.rules
echo "SUBSYSTEM==\"tty\", ATTRS{idVendor}==\"0483\", ATTRS{idProduct}==\"5740\", PROGRAM=\"/bin/sh -c 'echo %s{serial} | sed s/^0000__.*/rtk/g | sed s/^0000.*/main/g | sed s/^2-00.*/aux/g'\", SYMLINK+=\"microstrain_%c\", MODE=\"0666\"" >> 100-microstrain.rules
echo "SUBSYSTEM==\"tty\", ATTRS{idVendor}==\"199b\", ATTRS{idProduct}==\"3065\", PROGRAM=\"/bin/sh -c 'echo %s{serial} | sed s/^0000__/rtk/g | sed s/^0000/main/g | sed s/^2-00/aux/g'\", SYMLINK+=\"microstrain_%c\", MODE=\"0666\"" >> 100-microstrain.rules
echo "SUBSYSTEM==\"tty\", ATTRS{idVendor}==\"0483\", ATTRS{idProduct}==\"5740\", PROGRAM=\"/bin/sh -c 'echo %s{serial} | sed s/^0000__/rtk/g | sed s/^0000/main/g | sed s/^2-00/aux/g'\", SYMLINK+=\"microstrain_%c\", MODE=\"0666\"" >> 100-microstrain.rules
sudo cp 100-microstrain.rules /etc/udev/rules.d/

cd
sudo udevadm control --reload-rules && sudo systemctl restart systemd-udevd && sud

# T265
sudo apt-get install git libssl-dev libusb-1.0-0-dev pkg-config libgtk-3-dev -y
sudo apt-get install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev -y
RS_FILE="librealsense.git"
if [ -e "$RS_FILE" ]; then
  echo "librealsense.git is already exist"
else
  git clone https://github.com/IntelRealSense/librealsense.git
fi
cd librealsense
sudo cp config/99-realsense-libusb.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && udevadm trigger
./scripts/patch-realsense-ubuntu-lts.sh

BUILD_FOLDER="build"
if [ ! -d "$BUILD_FOLDER" ]; then
  mkdir build
fi
cd build
cmake ..
sudo make uninstall && make clean && make && sudo make install

# install
cd ~/raisimLib/camel-raisim-projects/camel-tools
if [ ! -d "$BUILD_FOLDER" ]; then
  mkdir build
fi
cd build
cmake ..
make
sudo make install