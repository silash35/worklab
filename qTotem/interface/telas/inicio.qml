import QtQuick 2.15
import QtQuick.Controls 2.15

Page {

    Label {
        id: introText
        text: "Responda às perguntas a seguir"
        fontSizeMode: Text.Fit
        font.pointSize: 200
        minimumPointSize: 10
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 20
        anchors.leftMargin: 20

        anchors.fill: parent
        anchors.bottomMargin: parent.height / 4
    }

    Page {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: introText.bottom
        anchors.bottom: parent.bottom

        Button {
            objectName: "btnComecar"
            width: 200
            height: 100
            text: "Começar"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                stackView.push("perguntas.qml");
                py.comecar();
            }
        }
    }
}