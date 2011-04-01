## Dependencies ##
### Firebreath ###

**Version 1.3** : git clone git://github.com/epitech-labfree/FireBreath.git
*Installation for Unix* :

<pre>
mkdir projects && cd projects
ln -s [somewhere]/encrev2_plugin
cd ../
./prepmakesh -D WITH_SYSTEM_BOOST=1
cd build && make && make install
</pre>

### VLC ###

**Version 1.1 custom** with patched smem  : git clone git://github.com/epitech-labfree/vlc-1.1-encre.git

VLC has a huge set of dependencies, so if you are on a Debian based operating system do :
<pre>sudo apt-get build-dep vlc</pre>
Or follow this list :

* ttf-freefont
* vlc-nox
* libaa1
* libavcodec52
* libavcodec-extra-52
* libavutil50
* libavutil-extra-50
* libc6
* libfreetype6
* libfribidi0
* libgcc1
* libgl1-mesa-glx
* libgl1
* libgl1-mesa-glx
* libgl1-mesa-swx11
* libqtcore4
* libqtgui4
* libsdl-image1.2
* libsdl1.2debian
* libstdc++6
* libtar
* libva-x11-1
* libva1
* libvlccore4
* libx11-6
* libx11-xcb1
* libxcb-keysyms1
* libxcb-randr0
* libxcb-shm0
* libxcb-xv0
* libxcb1
* libxext6
* zlib1g

Installation for Unix :
<pre>
./bootstrap
./configure --prefix=/usr/local
./compile
sudo make install
</pre>

### Boost ###
**Version 1.42 or more**

* libboost-thread
* libboost-spirit
* libboost-asio
* libboost-system

### Debugging ###
*With Chrome/Chromium* : http://code.google.com/p/chromium/wiki/LinuxDebugging

*With Firefox* : firefox -g test.html test.html

