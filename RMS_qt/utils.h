#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QLineEdit>
#include <QDate>

QString hashPassword(const QString &password);
bool isValidEmail(const QString &email);
bool isOver18(const QString& dobStr);
void setupEyeButton(QLineEdit *passwordEdit);

#endif // UTILS_H
