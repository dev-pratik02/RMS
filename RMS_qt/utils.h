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
// utils.h
inline void setupPasswordToggle(QLineEdit *passwordLineEdit)
{
    QToolButton *eyeButton = new QToolButton(passwordLineEdit);

    QIcon eyeIcon("C:/Users/Swift/OneDrive/Desktop/eye.png");
    QIcon eyeOffIcon("C:/Users/Swift/OneDrive/Desktop/eyeoff.png");

    eyeButton->setIcon(eyeIcon);
    eyeButton->setCursor(Qt::PointingHandCursor);
    eyeButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");

    // Set icon size explicitly
    int iconSize = passwordLineEdit->height() * 0.6;
    eyeButton->setIconSize(QSize(iconSize, iconSize));
    eyeButton->resize(QSize(iconSize + 4, iconSize + 4));  // slight padding

    // Adjust margins inside QLineEdit
    int frameWidth = passwordLineEdit->style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    passwordLineEdit->setTextMargins(0, 0, eyeButton->width() + frameWidth, 0);

    // Position the eye button correctly
    eyeButton->move(passwordLineEdit->rect().right() - eyeButton->width() - frameWidth,
                    (passwordLineEdit->rect().height() - eyeButton->height()) / 2);
    eyeButton->show();

    // Update position if resized
    QObject::connect(passwordLineEdit, &QLineEdit::textChanged, [=]() {
        eyeButton->move(passwordLineEdit->rect().right() - eyeButton->width() - frameWidth,
                        (passwordLineEdit->rect().height() - eyeButton->height()) / 2);
    });

    // Toggle password visibility
    QObject::connect(eyeButton, &QToolButton::clicked, [=]() mutable {
        bool isHidden = passwordLineEdit->echoMode() == QLineEdit::Password;
        passwordLineEdit->setEchoMode(isHidden ? QLineEdit::Normal : QLineEdit::Password);
        eyeButton->setIcon(isHidden ? eyeOffIcon : eyeIcon);
    });
}


#endif // UTILS_H
