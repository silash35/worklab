numero direitaS = 0
numero esquerdaS = 0
numero objetivo = 0

# PID
# Valores que precisam ser calibrados
numero kP = 20
numero kI = 1
numero kD = 1
numero tolerancia = 4
# Valores vão ser calculados ao longo do programa
numero p = 0
numero i = 0
numero d = 0
numero erro = 0
numero saida = 0
numero entrada = 0
numero t = 0
numero t1 = 0
numero t2 = 0
tarefa calcularPID{


  
  erro = objetivo - entrada

  p = kP * erro
  i = kI * erro * t

  escrever(1,virartexto(t))
  t = t+1

  saida = p + i + d
  se (erro < tolerancia) entao {
    saida = 0
    t = 0
  }
}


inicio
  objetivo = luz(1)
  enquanto (verdadeiro) farei {
    direitaS = luz(1)
    esquerdaS = luz(2)
    #escrever(1,virartexto(direitaS))
    #escrever(2,virartexto(esquerdaS))

    entrada = direitaS
    calcularPID()
    se (saida != 0) entao {
      direita(saida)
    } senao {
      entrada = esquerdaS
      calcularPID()
      se (saida != 0) entao {
        esquerda(saida)
      } senao {
        frente(80)
      }
    }
  }
fim