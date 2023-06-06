mkdir build
mkdir build/ui
mkdir -p build/ui/ressources
mkdir build/modules/
cp ./src/mainprocess/ui/ressources/* ./build/ui/ressources
cp ./src/mainprocess/database/db.sql  ./build/db.sql
g++ -std=c++11 ./src/mainprocess/extensions/javascriptextensions.cpp -shared -fPIC -o ./build/modules/javascriptextensions.so `pkg-config webkit2gtk-web-extension-4.0 --libs --cflags` -lsqlite3
g++ -std=c++17 ./src/mainprocess/main.cpp ./src/mainprocess/ui/view.cpp `pkg-config gtkmm-3.0 --libs --cflags` `pkg-config webkit2gtk-4.0 --libs --cflags` -o build/quizy.ng
npm run rbuild


