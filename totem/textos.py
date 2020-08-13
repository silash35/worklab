from threading import Thread
import os

opções = '''Toque no botão da esquerda, caso a resposta seja sim.
    Toque no botão da direita, caso a resposta seja não.'''

textosDaTela = [
    'Responda as perguntas a seguir. Toque no botão de borda azul (Um pouco abaixo do centro da tela) para começar',
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
        Vômitos persistentes'''  + opções,

    '''Você esta sentindo algum desses sintomas?
        Dor
        Vômitos
        Ou seu problema é recente?''' + opções,

    'Pronto, suas respostas foram computadas e enviadas para analize, em breve você será atendido'

    ]

def textToSpeech(text):
    t2 = Thread(target=__textToSpeech__,args=(text,))
    t2.start()

def __textToSpeech__(text):
    os.system('espeak -v pt-br "'+ text + '"')