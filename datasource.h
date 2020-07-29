/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>
#include<QDebug>
#include <QtSerialPort/QSerialPort>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)
QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QQuickView *appViewer, QObject *parent = 0)
        :
        QObject(parent),
        m_appViewer(appViewer),
        m_index(-1)
    {
        // Serial communication parameter initilization
//        const QString serialPortName = "/dev/tyUSB0";
//        serialPort.setPortName(serialPortName);

//        const int serialPortBaudRate = QSerialPort::Baud9600;
//        serialPort.setBaudRate(serialPortBaudRate);

//        if (!serialPort.open(QIODevice::ReadOnly)) {
//            qInfo() << QObject::tr("Failed to open port %1, error: %2").arg(serialPortName).arg(serialPort.error()) << endl;
//        }

        qRegisterMetaType<QAbstractSeries*>();
        qRegisterMetaType<QAbstractAxis*>();

        generateData(0, 5, 1024);
        for(qint8 i=0;i<=50;i++) {
            P1P2Diff.push_back(i);
        }
    }

Q_SIGNALS:

public slots:
    void generateData(int type, int rowCount, int colCount)
    {
        qInfo() << type <<"\t"<<rowCount<<"\t"<<colCount;
        // Remove previous data
        m_data.clear();

        // Append the new data depending on the type
        for (int i(0); i < 3; i++) {
            QVector<QPointF> points;
            points.reserve(colCount);
            for (int j(0); j < colCount; j++) {
                qreal x(0);
                qreal y(0);
                switch (i) {
                case 0:
                    // data with sin + random component
                    y = qSin(M_PI / 50 * j) + 0.5;
                    x = j;
                    break;
                case 1:
                    // linear data
                    x = j;
                    y = (qreal) i / 10;
                    break;
                default:
                    // unknown, do nothing
                    y = qSin(M_PI / 50 * j)+2;
                    x = j;
                    break;
                }
                points.append(QPointF(x, y));
            }
            m_data.append(points);
        }
    }
    void update(QAbstractSeries *series,int chart_index)
    {
        //    if (series) {
        //        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        //        m_index++;
        //        if (m_index > m_data.count() - 1)
        //            m_index = 0;

        //        QVector<QPointF> points = m_data.at(m_index);
        //        // Use replace instead of clear + append, it's optimized for performance
        //        xySeries->replace(points);
        //        //qInfo() << m_index <<"\t"<< m_data.count();
        //    }
        m_index++;
        m_index=m_index%1024;
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        QVector<QPointF> points;

//        if (serialPort.waitForReadyRead(1000)) {
//            QByteArray responseData = serialPort.readAll();
//            for(auto data : responseData) {
//                if(data != '\n') {
//                    res += data;
//                }
//                else {
//                    res.clear();
//                    const QString response = QString::fromUtf8(resData.back());
//                    if(resData.size()>100) resData.clear();
//                    qInfo() << response << "\t" << resData.size();
//                }
//                resData.push_back(res);
//            }
//        }

        if(chart_index == 0 && series) {
            points = m_data.at(chart_index);
        }
        else if(chart_index == 1 && series) {
            points = m_data.at(chart_index);
        }
        else if(chart_index == 2 && series) {
            points = m_data.at(chart_index);
        }
        xySeries->replace(points);

    }
    signals:
    void newMessagePosted(const QString &subject);

private:
    QQuickView *m_appViewer;
    QList<QVector<QPointF> > m_data;
    int m_index;
    QVector<qint8> P1P2Diff;

    // Serial communicatiuon parameters
    QSerialPort serialPort;
    QVector<QByteArray> resData;
    QByteArray res;
};

#endif // DATASOURCE_H
