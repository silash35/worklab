# Projeto Totem de Autoatendimento

> This is one of LabRob's projects. Therefore, its content is in Portuguese. Learn more in the main [Readme file](https://github.com/silash35/labrob/blob/master/README.md)

## Introdução

Um Totem de Autoatendimento para hospitais escrito em Python e Qml com o objetivo fazer a recepção de pacientes mais rápida e sem precisar de contato com outro ser humano.

O Totem faz perguntas para o usuário, classifica-os de acordo com o grau de emergência e mostra ao medico a lista de pacientes em espera já com as informações coletadas.

Foto da interface Qt, onde o paciente irá responder as perguntas

![Foto da interface Qt, onde o paciente irá responder as perguntas](https://raw.githubusercontent.com/silash35/labrob/master/qTotem/images/qtotem.webp)

Foto da interface Web, onde o medico ira visualizar todos os pacientes em espera

![Foto da interface Web, onde o medico ira visualizar todos os pacientes em espera](https://raw.githubusercontent.com/silash35/labrob/master/qTotem/images/qtotemWeb.png)

## Execução

Para rodar o aplicativo, primeiro vc irá precisar instalar as dependências Python que estão no arquivo "requirements.txt". Para fazer isso basta rodar o comando:

    pip install -r requirements.txt

Também é recomendado instalar os seguintes pacotes:

1. espeak (Para falar os textos da tela)
2. Git (Para atualizações automáticas)

Em seguida execute aqui "main.py". Neste único arquivo está incluso o servidor (Interface Web) e a interface em Qt.

    python main.py
