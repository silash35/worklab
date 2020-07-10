from kivy.app import App
from interface import *
from paciente import *

class Totem(App):
    def build(self):
        return Interface()
Totem().run()