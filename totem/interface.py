from kivy.lang.builder import Builder
from kivy.uix.screenmanager import ScreenManager, Screen

from kivy.graphics.context_instructions import Color
from kivy.graphics.instructions import InstructionGroup
from kivy.graphics.vertex_instructions import Rectangle

from kivy.utils import get_color_from_hex
from paciente import *
from textos import *

nTelas = 10 #numero de telas atual (começa a contagem do 0)
primeiraVez = True #Solução temporaria pra o bug misterioso

Builder.load_file('interface.kv')
class Interface(ScreenManager):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        textToSpeech(textosDaTela[0])


    def proximaTela(self):

        if(int(self.current) == nTelas):
            paciente.zeraDados()

        if(int(self.current) < nTelas):
            self.current = str(int(self.current) + 1)
        else:
            self.current = '0'
            textToSpeech(textosDaTela[0])

        
        global primeiraVez
        if(primeiraVez):
            self.current = str(nTelas)
            paciente.pontosDePerguntas = 1

        if(paciente.pontosDePerguntas != 0):

            self.current = str(nTelas)

            self.ids['result'].color = [1,1,1,1]
            self.ids['result'].text = str(calculaGrau(paciente.pontosTotal())[0])
            #Desenha retângulo com a cor dependendo do grau de emergência.
            corGrau = InstructionGroup()
            corGrau.add(
                Color(
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[0],
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[1],
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[2],
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[3]
                )
            )
            corGrau.add(
                Rectangle(
                    pos=self.ids['result'].pos,
                    size=self.ids['result'].size
                )
            )
            self.ids['result'].canvas.before.add(corGrau)
            
            if(primeiraVez):
                paciente.id = -1
                paciente.zeraDados()
            else:
                paciente.publicarNoSite()

        if(primeiraVez):
            primeiraVez = False
            self.current = '1'
        textToSpeech(textosDaTela[int(self.current)])

    def addPontos(self, pontos):
        paciente.pontosDePerguntas = int(paciente.pontosDePerguntas) + int(pontos)

    def atualizarCovid(self, pergunta, valor):
        paciente.covid[pergunta] = valor

    def cancelar(self):
        paciente.zeraDados()
        self.current = '0'
        textToSpeech(textosDaTela[0])