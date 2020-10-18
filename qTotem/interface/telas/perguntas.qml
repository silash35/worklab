import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import "../logic.js" as Js

Page {

    Label {
        id: labelPergunta
        text: Js.getPerguntaAtual()
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
                    Js.contarResposta(false);
                    Js.proximaPergunta();
                }
            }

            Button {
                Layout.preferredWidth: 200
                Layout.preferredHeight: 100
                text: "Sim"
                onClicked: {
                    Js.contarResposta(true);
                    Js.proximaPergunta();
                }
            }
        }
    }
}