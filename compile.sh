#!/bin/sh

FLAGS="-Wall -Wextra -O0 -g -ggdb"


# compile a console sqlite demo 

clang++ -o sqlitedemo $FLAGS -framework QtCore -framework QtSql -I /usr/local/Cellar/qt@5/5.15.3/include/QtCore -I /usr/local/Cellar/qt@5/5.15.3/include/QtSql sqlitedemo.cpp -F /usr/local/Cellar/qt@5/5.15.3/lib/



# compile a gui sqlite demo 

/usr/local/Cellar/qt@5/5.15.3/bin/moc sqlitedemo_guified.h > sqlitedemo_guified_moc.cpp

clang++ -o sqlitedemo_guified $FLAGS -framework QtCore -framework QtGui -framework QtWidgets -framework QtSql -I /usr/local/Cellar/qt@5/5.15.3/include/QtWidgets -I /usr/local/Cellar/qt@5/5.15.3/include/QtCore -I /usr/local/Cellar/qt@5/5.15.3/include/QtSql sqlitedemo_guified.cpp sqlitedemo_guified_moc.cpp -F /usr/local/Cellar/qt@5/5.15.3/lib/

