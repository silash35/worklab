from PySide2.QtCore import QObject, Slot
from interface.textos import perguntas, falarTextos
from paciente import paciente

numeroDePerguntas = 9
perguntaAtual = 0

class Bridge(QObject):

    def __init__(self):
        super().__init__()
        falarTextos(0)

    @Slot()
    def comecar(self):
        pass

    @Slot(bool)
    def contablizarResposta(self, resposta):
        if resposta:
            if perguntaAtual < 5:
                paciente.covid[perguntaAtual] = True
        else:
            pass

    @Slot(result=bool)
    def proximaPergunta(self):
        global perguntaAtual
        perguntaAtual += 1
        falarTextos(perguntaAtual+1)
        return not(perguntaAtual >= numeroDePerguntas)

    @Slot(result=str)
    def getPergunta(self):
        return perguntas[perguntaAtual]

    @Slot()
    def cancelar(self):
        pass

bridge = Bridge()
