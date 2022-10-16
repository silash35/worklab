import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "logic.js" as Js

ApplicationWindow {
    id: mainWindow
    width: 500
    height: 500
    visible: true
    //visibility: "FullScreen"
    title: "Totem"
    Material.theme: Material.Dark
    Material.accent: Material.Blue
    Material.primary: Material.Red

    header: ToolBar {
        ToolButton {
            text: "cancelar"
            onClicked: {
                Js.falarTexto(0);
                stackView.push("telas/inicio.qml");
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "telas/inicio.qml"
    }

    Component.onCompleted: {
        Js.falarTexto(0);
    }

}