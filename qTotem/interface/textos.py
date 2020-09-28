from threading import Thread
from os import system

perguntas = [
    '"Tosse seca" é um dos seus sintomas?',
    'Você sentiu "Febre alta" por mais de 5 dias?',
    'Você está sentindo dificuldade em respirar?',
    '"Diarreia" é um dos seus sintomas?',
    'Recentemente você teve contato com alguém com Covid?',

    '''Você esta sentindo algum desses sintomas?
    — Comprometimento da via aérea
    — Respiração ineficaz
    — Choque
    — Criança não responde''',

    '''Você esta sentindo algum desses sintomas?
    — Dor severa
    — Hemorragia Grande incontrolável
    — Criança quente
    Ou há alguma alteração do nível de consciência?''',

    '''Você esta sentindo algum desses sintomas?
    — Dor moderada
    — Pequena hemorragia incontrolável
    — Vômitos persistentes''',

    '''Você esta sentindo algum desses sintomas?
    — Dor
    — Vômitos
    Ou seu problema é recente?'''
]

opções = ''' Toque no botão da esquerda, caso a resposta seja sim.
    Toque no botão da direita, caso a resposta seja não.'''

textosDeAcessibilidade = [
    'Responda às perguntas a seguir. Toque no botão, um pouco abaixo do centro da tela para começar',
    'Tosse seca é um dos seus sintomas?' + opções,
    'Você sentiu Febre alta por mais de 5 dias?' + opções,
    'Você está sentindo dificuldade em respirar?' + opções,
    'Diarreia é um dos seus sintomas?' + opções,
    'Recentemente você teve contato com alguém com Covid?' + opções,

    '''Você esta sentindo algum desses sintomas?
        Comprometimento da via aérea
        Respiração ineficaz
        Choque
        Criança não responde''' + opções,

    '''Você esta sentindo algum desses sintomas?
        Dor severa
        Hemorragia Grande incontrolável
        Criança quente
        Ou há alguma alteração do nível de consciência?''' + opções,

    '''Você esta sentindo algum desses sintomas?
        Dor moderada
        Pequena hemorragia incontrolável
        Vômitos persistentes''' + opções,

    '''Você esta sentindo algum desses sintomas?
        Dor
        Vômitos
        Ou seu problema é recente?''' + opções,

    'Pronto, suas respostas foram computadas e enviadas para analize, em breve você será atendido'
]

def falarTextos(i):
    t3 = Thread(target=__falarTextos__,args=(i,))
    t3.daemon = True
    t3.start()

def __falarTextos__(i):
    system('espeak -v pt-br "' + textosDeAcessibilidade[i] + '"')