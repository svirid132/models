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
    ListView {
        clip: true
        anchors.fill: parent
        model: animalViewModel.animalModel
        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            RowLayout {
                Button {
                    text: qsTr("changed")
                    onClicked: {
                        type = "fox";
                        size = "12345";
                    }
                }
                Label {
                    text: type
                }
                Label {
                    text: size
                }
            }
        }
    }
}
