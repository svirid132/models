import QtQuick
import ViewModel
import ViewModelFactory
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root
    property AnimalViewModel animalViewModel: {
        return ViewModelFactory.createAnimalModelView()
    }
    ColumnLayout {
        anchors.fill: parent
        ListView {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: animalViewModel.animalModel
            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                RowLayout {
                    Label {
                        text: type
                    }
                    Label {
                        text: size
                    }
                    Button {
                        text: "change"
                        onClicked: {
                            type = "qwerty";
                            size = "bigbig";
                        }
                    }
                }
            }
        }
        RowLayout
        {
            Layout.fillWidth: true
            Button {
                text: qsTr("append animal")
                onClicked: {
                    animalViewModel.appendAnimal();
                }
            }
            Button {
                text: qsTr("remove animal")
                onClicked: {
                    animalViewModel.removeLastAnimal();
                }
            }
        }
    }
}
