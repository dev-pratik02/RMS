#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QLineEdit>
#include <QToolButton>
#include <QStyle>
#include <QIcon>
#include <QObject>

// Hashing
inline QString hashPassword(const QString &password)
{
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hashed.toHex();
}

// Email validation
inline bool isValidEmail(const QString &email)
{
    QRegularExpression emailRegex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
    QRegularExpressionMatch match = emailRegex.match(email);
    return match.hasMatch();
}

#endif // UTILS_H
