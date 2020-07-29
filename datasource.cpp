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

#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>
#include<QDebug>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QQuickView *appViewer, QObject *parent) :
    QObject(parent),
    m_appViewer(appViewer),
    m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    generateData(0, 5, 1024);
    for(qint8 i=0;i<=50;i++) {
        P1P2Diff.push_back(i);
    }
}

void DataSource::update(QAbstractSeries *series)
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
      QVector<QPointF> points = m_data.at(0);
      points.erase(points.begin()+m_index);
      xySeries->replace(points);
}

void DataSource::generateData(int type, int rowCount, int colCount)
{
    qInfo() << type <<"\t"<<rowCount<<"\t"<<colCount;
    // Remove previous data
    m_data.clear();

    // Append the new data depending on the type
    for (int i(0); i < rowCount; i++) {
        QVector<QPointF> points;
        points.reserve(colCount);
        for (int j(0); j < colCount; j++) {
            qreal x(0);
            qreal y(0);
            y = qSin(M_PI / 50 * j) + 0.5 + QRandomGenerator::global()->generateDouble();
            x = j;
//            switch (type) {
//            case 0:
//                // data with sin + random component
//                y = qSin(M_PI / 50 * j) + 0.5 + QRandomGenerator::global()->generateDouble();
//                x = j;
//                break;
//            case 1:
//                // linear data
//                x = j;
//                y = (qreal) i / 10;
//                break;
//            default:
//                // unknown, do nothing
//                break;
//            }
            points.append(QPointF(x, y));
        }
        m_data.append(points);
    }
}
