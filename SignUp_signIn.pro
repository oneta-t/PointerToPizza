QT       += core gui
QT       += core network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cart.cpp \
    createfood.cpp \
    database.cpp \
    fooditeam.cpp \
    main.cpp \
    mainwindow.cpp \
    menuf.cpp \
    menurepository.cpp \
    order.cpp \
    restaurantf.cpp \
    restaurantmanager.cpp \
    customer.cpp \
    restaurantmodel.cpp \
    restaurantregistration.cpp \
    restaurantrepository.cpp \
    signin.cpp \
    signup.cpp \
    user.cpp \
    userinformationpage.cpp \
    userrepository.cpp

HEADERS += \
    cart.h \
    createfood.h \
    database.h \
    fooditeam.h \
    mainwindow.h \
    menuf.h \
    menurepository.h \
    order.h \
    restaurantf.h \
    restaurantmanager.h \
    customer.h \
    restaurantmodel.h \
    restaurantregistration.h \
    restaurantrepository.h \
    signin.h \
    signup.h \
    user.h \
    userinformationpage.h \
    userrepository.h

FORMS += \
    cart.ui \
    createfood.ui \
    fooditeam.ui \
    mainwindow.ui \
    customer.ui \
    menuf.ui \
    restaurantf.ui \
    restaurantmanager.ui \
    restaurantregistration.ui \
    signin.ui \
    signup.ui \
    userinformationpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
