from kivy.lang.builder import Builder
from kivy.uix.screenmanager import ScreenManager, Screen
from paciente import *

Builder.load_file('interface.kv')
class Interface(ScreenManager):
    def proximaTela(self):
        if(int(self.current) == 0):
            paciente.zeraDados()
        if(int(self.current) < 1): #1 é o numero de telas atual (começa a contagem do 0)
            self.current = str(int(self.current) + 1)