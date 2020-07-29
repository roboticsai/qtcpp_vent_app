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

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtCharts 2.0
import Message 1.0

Item {
    id: main
    width: 600
    height: 400

    RowLayout {
        id: rawlayout0
        anchors.fill: parent
        spacing: 6

        Settings {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
            signal settingChanged(int peep, int flow, int fio2, int psupport);

            onSettingChanged: {
                dataSource.generateData(peep, flow, fio2);
                charts.axisX().max = sampleCount;
            }
        }
        ColumnLayout {
            spacing: 0
            Charts {
                id: charts
                property int chart_index: 0
                theme: ChartView.ChartThemeDark
            }
            Charts {
                id: charts1
                property int chart_index: 1
                theme: ChartView.ChartThemeDark
            }
            Charts {
                id: charts2
                property int chart_index: 2
                theme: ChartView.ChartThemeDark
            }
        }
    }
}
