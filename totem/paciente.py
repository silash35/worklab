#Constantes medicas, só devem ser alteradas 1 vez
temperaturaMax = 0
saturacaoMin = 0
pressaoMin = 0
pressaoMax = 0

class Paciente:

    def __init__(self):
        self.temperatura = 0
        self.pressao = 0
        self.saturacao = 0
        # Não tem maneira melhor,e mais escalável de calcular o grau de emergencia do que com pontos
        self.pontosDePerguntas = 0

    def zeraDados(self):
        self.temperatura = 0
        self.pressao = 0
        self.saturacao = 0
        self.pontosDePerguntas = 0

    def getDados(self):
        #codigo leitura da GPIO

        # Como essa função vai rodar em Loop, 
        # talves ela pegue dados errados da GPIO, e não 
        # queremos que ela sobrescreva os dados antigos
        # caso os dados antigos sejam mais "graves"
        temp = 0
        press = 0 
        satura = 0
        if(temp > self.temperatura):
            self.temperatura = temp
        if(press > self.pressao):
            self.pressao = press
        if(satura < self.saturacao):
            self.saturacao = satura

    def pontosTotal(self):
        #codigo calcular total de pontos
        ptemp = 0
        if(self.temperatura > temperaturaMax):
            ptemp = 10

        ppress = 0
        if(self.pressao > pressaoMax or self.pressao < pressaoMin):
            ppress = 10

        psatura = 0
        if(self.saturacao < saturacaoMin):
            psatura = 10

        return (self.pontosDePerguntas + ptemp + ppress + psatura)

    def enviarEmail(self):
        #codigo enviar resultado para Email, chamando 'pontosTotal'
        pass

paciente = Paciente()

def calculaGrau(pontos):
    cor = '#ffffff'
    grau = 'Não Urgente'

    if(pontos <= 10):
        cor = '#1c5cff'
        grau = "Não Urgente"
    elif(pontos <= 20):
        cor = '#1fd158'
        grau = 'Pouco Urgente'
    elif(pontos <= 30):
        cor = '#f5d800'
        grau = 'Urgente'
    elif(pontos <= 40):
        cor = '#ff6f00'
        grau = 'Muito Urgente'
    elif (pontos > 40):
        cor = '#ff1500'
        grau = 'Emergência'
    else:
        pass #ERRO
    return [grau, cor]