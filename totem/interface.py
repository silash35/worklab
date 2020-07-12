from kivy.lang.builder import Builder
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.label import Label
from kivy.graphics import *
from kivy.utils import get_color_from_hex
from paciente import *

nTelas = 3 #numero de telas atual (começa a contagem do 0)

Builder.load_file('interface.kv')
class Interface(ScreenManager):

    def proximaTela(self):

        if(int(self.current) == 0):
            paciente.zeraDados()

        if(int(self.current) == (nTelas-1)):
            paciente.publicarNoSite()

            self.ids['result'].color = [1,1,1,1]
            self.ids['result'].text = str(calculaGrau(paciente.pontosTotal())[0])
            #Desenha retangulo com a cor dependendo do grau de emergencia.
            #Aqui tem um Bug que ele só desenha na segunda vez que o programa roda, não consegui resolver
            with self.ids['result'].canvas.before:
                Color(
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[0],
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[1],
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[2],
                    get_color_from_hex(calculaGrau(paciente.pontosTotal())[1])[3],
                    )
                Rectangle(pos = self.ids['result'].pos, size = self.ids['result'].size)

        if(int(self.current) < nTelas):
            self.current = str(int(self.current) + 1)
        else:
            self.current = '0'
    def addPontos(self, pontos):
        paciente.pontosDePerguntas = int(paciente.pontosDePerguntas) + int(pontos)