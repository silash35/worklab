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
            id: cancelar
            text: "cancelar"
            onClicked: py.cancelar()
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "telas/inicio.qml"
    }
}