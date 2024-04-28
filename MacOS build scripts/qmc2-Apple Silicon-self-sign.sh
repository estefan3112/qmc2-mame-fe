## this script is set up to build qmc2 from the original source on Apple Silicon
## download this script and make it executable with chmod 755 in the terminal
## launch the script from the desired directory
## please note that the built and installed qmc2 binary will be in /Applications/qmc2; you may move it from there into the main Applications directory

#! /bin/zsh
git clone --recursive https://github.com/qmc2/qmc2-mame-fe
cd qmc2-mame-fe
echo 'export PATH="/opt/homebrew/opt/qt@5/bin:$PATH"' >> ~/.zshrc
export LDFLAGS="-L/opt/homebrew/opt/qt@5/lib"
export CPPFLAGS="-I/opt/homebrew/opt/qt@5/include"
export PKG_CONFIG_PATH="/usr/local/opt/qt@5/lib/pkgconfig"
qmake -makefile -o Makefile.qmake -spec macx-clang VERSION=0.244 QMC2_MINGW=0 SDL=2 TARGET=qmc2-sdlmame CONFIG+=warn_off CONFIG+=release 'DEFINES+=QMC2_SDLMAME QMC2_VERSION=0.244 BUILD_OS_NAME=Darwin BUILD_OS_RELEASE=23.3.0 BUILD_MACHINE=arm64 PREFIX=/usr/local QMC2DATADIR="/Library/Application:Support" SYSCONFDIR="/Library/Application:Support" QMC2_JOYSTICK=1 QMC2_PHONON=0 QMC2_MULTIMEDIA=1 QMC2_FADER_SPEED=500 QMC2_GIT_REV=beaf02d QMC2_MAC_UNIVERSAL=0 QMC2_BROWSER_EXTRAS_ENABLED QMC2_BROWSER_PLUGINS_ENABLED QMC2_BROWSER_JAVA_ENABLED QMC2_BROWSER_JAVASCRIPT_ENABLED QMC2_YOUTUBE_ENABLED QMC2_BUNDLED_MINIZIP QMC2_BUNDLED_ZLIB' qmc2.pro
make IMGSET=cubes -j8
sudo make install
xattr -cr /Applications/qmc2/qmc2-sdlmame.app
sudo chmod -R 775 /Applications/qmc2/qmc2-sdlmame.app

## next: self-signing all components and the app bundle with a self-signed certificate called QMC2 (which you first need to create)
## for instructions how to create a self-signed certificate, please see https://support.apple.com/guide/keychain-access/create-self-signed-certificates-kyca8916/mac
## you need to self-sign qmc2 and all components in order to have it run on Silicon Macs

codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/MacOS/qmc2-sdlmame
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Frameworks/QtWebEngineCore.framework/Versions/5/Helpers/QtWebEngineProcess.app
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Frameworks/*.*
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/audio/*.*  
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/bearer/*.*  
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/iconengines/*.*
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/imageformats/*.*    
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/mediaservice/*.*
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/platforms/*.*  
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/position/*.*   
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/printsupport/*.*
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/sqldrivers/*.*
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app/Contents/Plugins/styles/*.*
codesign --force --timestamp --verify --verbose --sign "QMC2" /Applications/qmc2/qmc2-sdlmame.app
