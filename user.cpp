#include "user.h"

User::User(QString name,QString family,QString passw,QString username,QString phone,QString role)
{
    Firstname=name;
    Lastname=family;
    Phonenum=phone;
    Username=username;
    Password=passw;
    Role=role;
}

User::User()
{
    Firstname="user";
    Lastname="";
    Phonenum="000";
    Username="user0";
    Password="123";
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
    return Username;
}

QString User::getPhone() const
{
    return Phonenum;
}

QString User::getPassword() const
{
    return Password;
}

QString User::getRole()const
{
    return Role;
}

int User::getId()const
{
    return UserId
}





