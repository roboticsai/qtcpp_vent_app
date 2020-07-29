#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QDebug>

class MessageBoard : public QObject
{
    Q_OBJECT
public:
    MessageBoard() {
        startTimer(1000);
    }
    Q_INVOKABLE void triggerEvent(QString text) {
        emit newMessagePosted(text);
    }
    void timerEvent(QTimerEvent *e) {
        QString text = "The text";
        triggerEvent(text);
    }
    Q_INVOKABLE bool postMessage(const QString &msg) {
        qDebug() << "Called the C++ method with" << msg;
        return true;
    }

public slots:
    void refresh() {
        qDebug() << "Called the C++ slot";
        newMessagePosted("from backend dickhead!");
    }
public:
    // ...
signals:
    void newMessagePosted(const QString &subject);
};
