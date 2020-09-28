import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Page {

    function passarPergunta(){
        if (py.proximaPergunta()) {
            labelPergunta.text = py.getPergunta()
        } else {
            stackView.push("resultado.qml");
        }
    }

    Label {
        id: labelPergunta
        text: py.getPergunta()
        fontSizeMode: Text.Fit
        font.pointSize: 200
        minimumPointSize: 10
        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 20
        anchors.leftMargin: 20

        anchors.fill: parent
        anchors.bottomMargin: parent.height / 4
    }
    Page{
        id: page
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: labelPergunta.bottom
        anchors.bottom: parent.bottom
        RowLayout{
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Button {
                Layout.preferredWidth: 200
                Layout.preferredHeight: 100
                text: "Não"
                onClicked: {
                    py.contablizarResposta(false);
                    passarPergunta();
                }
            }

            Button {
                Layout.preferredWidth: 200
                Layout.preferredHeight: 100
                text: "Sim"
                onClicked: {
                    py.contablizarResposta(true);
                    passarPergunta();
                }
            }
        }
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/
