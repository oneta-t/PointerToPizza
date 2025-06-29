QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fooditeam.cpp \
    main.cpp \
    mainwindow.cpp \
    menuf.cpp \
    restaurantf.cpp \
    restaurantmanager.cpp \
    customer.cpp \
    restaurantregistration.cpp \
    signin.cpp \
    signup.cpp \
    user.cpp

HEADERS += \
    fooditeam.h \
    mainwindow.h \
    menuf.h \
    restaurantf.h \
    restaurantmanager.h \
    customer.h \
    restaurantregistration.h \
    signin.h \
    signup.h \
    user.h

FORMS += \
    fooditeam.ui \
    mainwindow.ui \
    customer.ui \
    menuf.ui \
    restaurantf.ui \
    restaurantmanager.ui \
    restaurantregistration.ui \
    signin.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
