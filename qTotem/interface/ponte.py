from PySide2.QtCore import QObject, Slot
from interface.textos import perguntas, falarTextos
from paciente import paciente

numeroDePerguntas = 9
perguntaAtual = 0

class Ponte(QObject):

    def __init__(self):
        super().__init__()
        falarTextos(0)

    @Slot()
    def comecar(self):
        global perguntaAtual
        paciente.zeraDados()
        perguntaAtual = 0

    @Slot(bool)
    def contablizarResposta(self, resposta):
        global perguntaAtual
        if resposta:
            if perguntaAtual < 5:
                paciente.covid[perguntaAtual] = True
            elif perguntaAtual == 5:
                paciente.pontosDePerguntas += 50
            elif perguntaAtual == 6:
                paciente.pontosDePerguntas += 31
            elif perguntaAtual == 7:
                paciente.pontosDePerguntas += 21
            elif perguntaAtual == 8:
                paciente.pontosDePerguntas += 11

        if paciente.pontosDePerguntas > 0:
            perguntaAtual = numeroDePerguntas-1

    @Slot(result=str)
    def getPerguntaAtual(self):
        falarTextos(perguntaAtual+1)
        return perguntas[perguntaAtual]

    @Slot(int,result=str)
    def getTexto(self, i):
        falarTextos(i)
        return perguntas[i]

    @Slot(result=bool)
    def proximaPergunta(self):
        global perguntaAtual
        perguntaAtual += 1
        return not(perguntaAtual >= numeroDePerguntas)

    @Slot(result=int)
    def getPontos(self):
        return paciente.pontosTotal()

    @Slot(result=str)
    def getId(self):
        return str(paciente.id)

    @Slot(str,str)
    def publicarNoSite(self, grau, corNome):
        paciente.publicarNoSite(grau, corNome)

ponte = Ponte()