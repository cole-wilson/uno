#!/bin/bash

# https://stackoverflow.com/questions/1596945/building-osx-app-bundle

ls buildmac.sh && rm -rf build
mkdir build
mkdir build/Uno.app

mkdir build/Uno.app/Contents
cp ./Info.plist build/Uno.app/Contents

mkdir build/Uno.app/Contents/MacOS
cp /Users/cole/Library/Developer/Xcode/DerivedData/Uno-*/Build/Products/Debug/*.dylib build/Uno.app/Contents/MacOS
cp /Users/cole/Library/Developer/Xcode/DerivedData/Uno-*/Build/Products/Debug/Uno build/Uno.app/Contents/MacOS

echo "#!/bin/bash" > build/Uno.app/Contents/MacOS/launch
echo 'cd "${0%/*}"' >> build/Uno.app/Contents/MacOS/launch
echo './Uno' >> build/Uno.app/Contents/MacOS/launch
chmod +x build/Uno.app/Contents/MacOS/launch

cp /Users/cole/Library/Developer/Xcode/DerivedData/Uno-*/Build/Products/Debug/helvetica.ttf build/Uno.app/Contents/MacOS
cp /Users/cole/Library/Developer/Xcode/DerivedData/Uno-*/Build/Products/Debug/unologo.png build/Uno.app/Contents/MacOS

mkdir build/Uno.app/Contents/Resources
cp ./Icon.icns build/Uno.app/Contents/Resources

mkdir build/Uno.app/Contents/MacOS/sounds
cp /Users/cole/Library/Developer/Xcode/DerivedData/Uno-*/Build/Products/Debug/sounds/*.wav build/Uno.app/Contents/MacOS/sounds

mkdir build/Uno.app/Contents/MacOS/cards
cp /Users/cole/Library/Developer/Xcode/DerivedData/Uno-*/Build/Products/Debug/cards/*.png build/Uno.app/Contents/MacOS/cards

zip build/Uno_macos_arm64.zip build/Uno.app
