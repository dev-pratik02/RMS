#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QLineEdit>

QString hashPassword(const QString &password);
bool isValidEmail(const QString &email);
void setupEyeButton(QLineEdit *passwordEdit);

#endif // UTILS_H
