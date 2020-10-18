import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    Rectangle {
        id: retResultado
        anchors.fill: parent
        anchors.bottomMargin: parent.height / 4
        color: "#ffffff"
        border.width: 0

        Label {
            id: resultado
            text: "Calculando Resultado"
            fontSizeMode: Text.Fit
            font.pointSize: 200
            minimumPointSize: 10
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 20
            anchors.leftMargin: 20

            anchors.fill: parent
        }
    }
    Page {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: retResultado.bottom
        anchors.bottom: parent.bottom

        Button {
            width: 200
            height: 100
            text: "Finalizar"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                py.getTexto(0);
                //stackView.clear();
                //stackView.push("inicio.qml");
                stackView.pop(null)
            }
        }
    }
    Component.onCompleted: {
        let pontos = py.getPontos();

        let grau = 'Não Urgente';
        let cor = '#ffffff';
        let corNome = 'branco';

        if(pontos <= 10){
            cor = '#1c5cff';
            grau = "Não Urgente";
            corNome = 'azul';
        }else if(pontos <= 20){
            cor = '#1fd158';
            grau = 'Pouco Urgente';
            corNome = 'verde';
        }else if(pontos <= 30){
            cor = '#f5d800';
            grau = 'Urgente';
            corNome = 'amarelo';
        }else if(pontos <= 40){
            cor = '#ff6f00';
            grau = 'Muito Urgente';
            corNome = 'laranja';
        }else if(pontos > 40){
            cor = '#ff1500';
            grau = 'Emergência';
            corNome = 'vermelho';
        }else{
            //ERRO
        }
        py.publicarNoSite(grau,corNome);
        retResultado.color = cor;
        resultado.text = grau + "\n Aguarde chamar o número " + py.getId();
        py.getTexto(10);
    }
}