import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: mainWindow
    width: 500
    height: 500
    visible: true
    //visibility: "FullScreen"
    title: "Totem"

    header: ToolBar {
        ToolButton {
            text: "cancelar"
            onClicked: {
                stackView.push("telas/inicio.qml");
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "telas/inicio.qml"
    }
}