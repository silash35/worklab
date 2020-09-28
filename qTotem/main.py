import sys
from os.path import abspath, dirname, join
from threading import Thread

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine

from style import *

from interface.bridge import bridge
from paciente import paciente


# Código que irá rodar em loop em segundo plano
def runA():
    while(True):
        paciente.getDados()


t1 = Thread(target=runA)
t1.setDaemon(True)
t1.start()


# Código Qt
if __name__ == '__main__':
    app = QGuiApplication(sys.argv)
    qmlFile = join(dirname(__file__), 'interface/main.qml')

    # deixa a Classe Bridge disponível para os aquivos .qml
    engine = QQmlApplicationEngine()
    context = engine.rootContext()
    context.setContextProperty("py", bridge)
    engine.load(abspath(qmlFile))

    if not engine.rootObjects():
        sys.exit(-1)
    sys.exit(app.exec_())