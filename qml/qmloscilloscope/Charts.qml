import QtQuick 2.0
import QtCharts 2.1
import QtQuick.Layouts 1.0

ChartView {
    id: chartView
    Layout.alignment: Qt.AlignCenter
    Layout.fillHeight: true
    Layout.fillWidth: true
    ValueAxis {
        id: axisY1
        min: -1
        max: 4
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1024
    }
    LineSeries {
        id: lineSeries1
        name: "signal 1"
        axisX: axisX
        axisY: axisY1
    }
    Timer {
        id: refreshTimer
        interval: 1 / 60 * 1000 // 60 Hz
        running: true
        repeat: true
        onTriggered: {
            dataSource.update(charts.series(0),charts.chart_index);
            dataSource.update(charts1.series(0),charts1.chart_index);
            dataSource.update(charts2.series(0),charts2.chart_index);
        }
    }
}
