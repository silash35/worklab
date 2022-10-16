let numeroDePerguntas = 9;
var perguntaAtual = 0;

let perguntas = [
  '"Tosse seca" é um dos seus sintomas?',
  'Você sentiu "Febre alta" por mais de 5 dias?',
  "Você está sentindo dificuldade em respirar?",
  '"Diarreia" é um dos seus sintomas?',
  "Recentemente você teve contato com alguém com Covid?",

  `Você esta sentindo algum desses sintomas?
  — Comprometimento da via aérea
  — Respiração ineficaz
  — Choque
  — Criança não responde`,

  `Você esta sentindo algum desses sintomas?
  — Dor severa
  — Hemorragia Grande incontrolável
  — Criança quente
  Ou há alguma alteração do nível de consciência?`,

  `Você esta sentindo algum desses sintomas?
  — Dor moderada
  — Pequena hemorragia incontrolável
  — Vômitos persistentes`,

  `Você esta sentindo algum desses sintomas?
  — Dor
  — Vômitos
  Ou seu problema é recente?`,
];

const opções = `Toque no botão da esquerda, caso a resposta seja sim.
  Toque no botão da direita, caso a resposta seja não.`;

const textosDeAcessibilidade = [
  "Responda às perguntas a seguir. Toque no botão, um pouco abaixo do centro da tela para começar",
  "Tosse seca é um dos seus sintomas?" + opções,
  "Você sentiu Febre alta por mais de 5 dias?" + opções,
  "Você está sentindo dificuldade em respirar?" + opções,
  "Diarreia é um dos seus sintomas?" + opções,
  "Recentemente você teve contato com alguém com Covid?" + opções,

  `Você esta sentindo algum desses sintomas?
      Comprometimento da via aérea
      Respiração ineficaz
      Choque
      Criança não responde` + opções,

  `Você esta sentindo algum desses sintomas?
      Dor severa
      Hemorragia Grande incontrolável
      Criança quente
      Ou há alguma alteração do nível de consciência?` + opções,

  `Você esta sentindo algum desses sintomas?
      Dor moderada
      Pequena hemorragia incontrolável
      Vômitos persistentes` + opções,

  `Você esta sentindo algum desses sintomas?
      Dor
      Vômitos
      Ou seu problema é recente?` + opções,

  "Pronto, suas respostas foram computadas e enviadas para analise, em breve você será atendido",
];

function contarResposta(resposta) {
  let pontos = 0;

  if (resposta) {
    if (perguntaAtual < 5) {
      Py.setCovid(perguntaAtual);
    } else if (perguntaAtual == 5) {
      pontos = 50;
    } else if (perguntaAtual == 6) {
      pontos = 31;
    } else if (perguntaAtual == 7) {
      pontos = 21;
    } else if (perguntaAtual == 8) {
      pontos = 11;
    }
  }
  Py.addPontos(pontos);

  if (pontos != 0) {
    stackView.push("telas/resultado.qml");
  }
}

function falarTexto(i) {
  Py.falarTexto(textosDeAcessibilidade[i]);
}

function getPerguntaAtual() {
  falarTexto(perguntaAtual + 1);
  return perguntas[perguntaAtual];
}

function proximaPergunta() {
  perguntaAtual++;
  if (perguntaAtual < numeroDePerguntas) {
    labelPergunta.text = getPerguntaAtual();
  } else {
    stackView.push("telas/resultado.qml");
  }
}
