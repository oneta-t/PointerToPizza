#include "user.h"

int User::NextId=0;

User::User()
{
    ++NextId;
}

User::User(QString name,QString family,QString passw,QString username,QString phone)
{
    Firstname=name;
    Lastname=family;
    Phonenum=phone;
    Userame=username;
    password=passw;
    ID=++NextId;
}

int User::getId() const
{
    return ID;
}

QString User::getFirstName() const
{
    return Firstname;
}

QString User::getLastName() const
{
    return Lastname;
}

QString User::getUsername() const
{
    return Userame;
}

QString User::getPhone() const
{
    return Phonenum;
}

QString User::getPassword() const
{
    return password;
}






