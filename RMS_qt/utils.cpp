#include "utils.h"
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QToolButton>
#include <QPixmap>
#include <QDebug>
#include <QStyle>
#include <QLineEdit>
#include <QEvent>

// --- Hash password with SHA-256 ---
QString hashPassword(const QString &password) {
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

// --- Validate email format ---
bool isValidEmail(const QString &email) {
    QRegularExpression regex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return regex.match(email).hasMatch();
}

// --- ResizeFilter Class for eye button positioning ---
class ResizeFilter : public QObject {
public:
    QToolButton *button;
    QLineEdit *lineEdit;
    int frameWidth;
    int buttonWidth;

    ResizeFilter(QToolButton *btn, QLineEdit *le, int fw, int bw)
        : QObject(le), button(btn), lineEdit(le), frameWidth(fw), buttonWidth(bw) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == lineEdit && event->type() == QEvent::Resize) {
            button->setGeometry(
                lineEdit->rect().right() - buttonWidth - frameWidth,
                (lineEdit->rect().height() - button->sizeHint().height()) / 2,
                buttonWidth,
                button->sizeHint().height()
                );
        }
        return QObject::eventFilter(obj, event);
    }
};


void setupEyeButton(QLineEdit *passwordEdit) {
    passwordEdit->setEchoMode(QLineEdit::Password);

    QToolButton *eyeButton = new QToolButton(passwordEdit);
    QPixmap pixmap("C:/Users/Swift/RMS/RMS-assets/eye.png");  // Update if using resource file

    if (pixmap.isNull()) {
        qDebug() << "Eye image not found.";
    } else {
        eyeButton->setIcon(QIcon(pixmap));
    }

    eyeButton->setCursor(Qt::PointingHandCursor);
    eyeButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");

    int frameWidth = passwordEdit->style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    int buttonWidth = eyeButton->sizeHint().width();
    passwordEdit->setTextMargins(0, 0, buttonWidth + frameWidth + 2, 0);

    eyeButton->setGeometry(
        passwordEdit->rect().right() - buttonWidth - frameWidth,
        (passwordEdit->rect().height() - eyeButton->sizeHint().height()) / 2,
        buttonWidth,
        eyeButton->sizeHint().height()
        );
    eyeButton->show();
    eyeButton->raise();

    QObject::connect(eyeButton, &QToolButton::pressed, [=]() {
        passwordEdit->setEchoMode(QLineEdit::Normal);
    });

    QObject::connect(eyeButton, &QToolButton::released, [=]() {
        passwordEdit->setEchoMode(QLineEdit::Password);
    });

    QObject::connect(passwordEdit, &QLineEdit::textChanged, [=]() {
        eyeButton->setGeometry(
            passwordEdit->rect().right() - buttonWidth - frameWidth,
            (passwordEdit->rect().height() - eyeButton->sizeHint().height()) / 2,
            buttonWidth,
            eyeButton->sizeHint().height()
            );
    });

    ResizeFilter *filter = new ResizeFilter(eyeButton, passwordEdit, frameWidth, buttonWidth);
    passwordEdit->installEventFilter(filter);
}
