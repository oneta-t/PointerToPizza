#ifndef USER_H
#define USER_H
#include <QWidget>

class User
{
public:
    User();
    User(QString name,QString family,QString passw,QString username,QString phone,QString role);
    int getId() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getUsername() const;
    QString getPhone() const;
    QString getPassword() const;
    QString getRole()const;

private:
    static int NextId;
    int ID;
    QString Firstname;
    QString Lastname;
    QString Userame;
    QString Phonenum;
    QString Password;
    QString Role;
};

#endif // USER_H
