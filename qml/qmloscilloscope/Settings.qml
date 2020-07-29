import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.2

TabView {
    Tab {
        id: tab1
        title: "Settings"
        Rectangle {
            id: rectangle1
            anchors.fill: parent
            color: "steelblue"
            ColumnLayout {
                id: columnLayout
                anchors.fill: parent
                spacing: 20
                GridLayout {
                    id: grid
                    anchors.top: columnLayout.top
                    anchors.left: columnLayout.left
                    anchors.right: columnLayout.right
                    columns: 3
                    rows: 4
                    columnSpacing: 1

                    Label {
                        text: "Peep"
                    }
                    SpinBox {
                        id: peep
                        value: 0
                    }
                    Text { text: "cm H2O"; }

                    Label {
                        text: "Flow"
                    }
                    SpinBox {
                        id: flows
                        value: 0
                    }
                    Text { text: "L/min"; }

                    Label {
                        text: "FiO2"
                    }
                    SpinBox {
                        id: fio2
                        value: 0
                    }
                    Text { text: "%"; }
                    Label {
                        text: "Psupport"
                    }
                    SpinBox {
                        id: psupport
                        value: 0
                    }
                    Text { text: "cm H2o"; }
                }
                Button {
                    id: button
                    text: "Set"
                    height: 200
                    width: 600
                    anchors.top: columnLayout.top
                    onClicked: settingChanged(peep.value,flows.value,fio2.value,psupport.value)
                }
            }
        }

    }
    Tab {
        id: tab2
        title: "Device Check"
        GridLayout {
            id: grid1
            columns: 2

            Label {
                text: "Self Test"
            }
            Button {
                text: "Start"
            }
            Label {
                text: "Leakage Test"
            }
            Button {
                text: "Start"
            }
            Label {
                text: "Flow Calibration"
            }
            Button {
                text: "Start"
            }
            Label {
                text: "Oxygen Sensor Calibration"
            }
            Button {
                text: "Start"
            }
        }
    }
}
