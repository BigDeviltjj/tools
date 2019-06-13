cd ~/Downloads/opencv-4.1.0/
mkdir -p build
cd build
cmake -DPYTHON3_EXECUTABLE=`which python` ..
make -j4
sudo make install
