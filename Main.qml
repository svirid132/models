import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Models")

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        TabBar {
            id: bar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Animal")
            }
            TabButton {
                text: qsTr("Files")
            }
        }

        Loader {
            Layout.fillWidth: true
            Layout.fillHeight: true
            active: bar.currentIndex === 0
            sourceComponent: AnimalView {}
        }
    }

    Settings {
        id: settings
        property alias barCurrentIndex: bar.currentIndex
    }
}
