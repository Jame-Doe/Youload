# Youload

requirements:
    ffmpeg
    yt-dlp
    asio
    crow

# install ffmpeg on linux
--Ubuntu/Debian

sudo apt update
sudo apt install ffmpeg

--Arch

sudo pacman -Syu
sudo pacman -S ffmpeg

# install yt-dlp

sudo curl -L https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp -o /usr/local/bin/yt-dlp
sudo chmod a+rx /usr/local/bin/yt-dlp

# install Asio
--Ubuntu/Debian

sudo apt update
sudo apt install build-essential cmake libasio-dev git

--Arch

sudo pacman -Syu
sudo pacman -S base-devel cmake asio git


# install  Crow

git clone https://github.com/CrowCpp/Crow.git
cd Crow
mkdir build && cd build
cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF
sudo make install
