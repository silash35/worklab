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
        self.id = 0

    def zeraDados(self):
        self.temperatura = 0
        self.pressao = 0
        self.saturacao = 0
        self.pontosDePerguntas = 0
        self.id = self.id + 1

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

    def publicarNoSite(self):
        f = open('./site/templates/users/'+str(self.id)+'.html','wt')
        f.write('''
        <div class="card hoverable">
    <div class="card-image waves-effect waves-block waves-light">
      <!-- Card Image -->
      <img class="activator" src="static/images/users/'''+calculaGrau(self.pontosTotal())[2]+'''.png">
    </div>
    <div class="card-content activator" style="cursor:pointer">
      <!-- Card Title -->
      <span class="card-title grey-text text-darken-4">'''+str(self.id)+'''</span>
    </div>
    <div class="card-reveal">
      <!-- Card Reveal Content -->
      <span class="card-title grey-text text-darken-4">'''+str(self.id)+'''<i class="material-icons right">close</i></span>

      <p>
        '''+ str(calculaGrau(self.pontosTotal())[0]) +'''
      </p>

      <p class="center">
	Temperatura: '''+str(self.temperatura)+'''<br>
	Pressão: '''+str(self.pressao)+'''<br>
	Saturação: '''+str(self.saturacao)+'''<br>
	Covid: '''+'false'+'''<br>
      </p>

    </div>
  </div>
        ''')
        f.close()

paciente = Paciente()

def calculaGrau(pontos):
    grau = 'Não Urgente'
    cor = '#ffffff'
    corNome = 'branco'

    if(pontos <= 10):
        cor = '#1c5cff'
        grau = "Não Urgente"
        corNome = 'azul'
    elif(pontos <= 20):
        cor = '#1fd158'
        grau = 'Pouco Urgente'
        corNome = 'verde'
    elif(pontos <= 30):
        cor = '#f5d800'
        grau = 'Urgente'
        corNome = 'amarelo'
    elif(pontos <= 40):
        cor = '#ff6f00'
        grau = 'Muito Urgente'
        corNome = 'laranja'
    elif (pontos > 40):
        cor = '#ff1500'
        grau = 'Emergência'
        corNome = 'vermelho'
    else:
        pass #ERRO
    return [grau, cor, corNome]