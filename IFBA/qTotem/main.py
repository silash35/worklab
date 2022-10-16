import sys
from os import path, system
from threading import Thread

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine

from interface.ponte import ponte
from paciente import paciente
from web.server import app


def loopGPIO():
    while True:
        paciente.getDados()


def server():
    from waitress import serve

    serve(app, host="0.0.0.0", port=8080)


# Procurar e instalar atualizações
system("git pull")

# Iniciar Loop em segundo plano para ler os dados da GPIO
gpioThread = Thread(target=loopGPIO)
gpioThread.daemon = True
gpioThread.start()

# Iniciar Servidor para interface Web
serverThread = Thread(target=server)
serverThread.daemon = True
serverThread.start()


# Iniciar interface Qt
if __name__ == "__main__":
    # Apply Material Style
    sys_argv = sys.argv
    sys_argv += ["--style", "material"]

    qtApp = QGuiApplication(sys_argv)
    qmlFile = path.join(path.dirname(__file__), "interface/main.qml")

    # deixa a Classe Bridge disponível para os aquivos .qml
    engine = QQmlApplicationEngine()
    context = engine.rootContext()
    context.setContextProperty("Py", ponte)
    engine.load(path.abspath(qmlFile))

    if not engine.rootObjects():
        sys.exit(-1)
    # initServer()
    sys.exit(qtApp.exec_())
