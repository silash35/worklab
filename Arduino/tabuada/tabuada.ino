#include "questions.hpp"
#include "utils.hpp"

int intSerialResponse, hits, mistakes, answeredQuestions, trueAlt;
unsigned long long int partTime, finalTime;
String serialResponse;
String emptySerialString;

//Variables that will be reused several times to save space.
int x, y;

void reset(){
  intSerialResponse = hits = mistakes = answeredQuestions = trueAlt =
  partTime = finalTime =
  x = y = 0;
}

void setup(){

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }
  serialResponse = emptySerialString = Serial.readString();

  reset();
  assimilate();
}

void loop(){

  //print main menu
  Serial.println("Selecione o modo:");
  Serial.println("0: Aleatorio (Padrão)");
  Serial.println("1: Ordenado");
  Serial.println("2: Personalizado");
  Serial.println("3: Alternativas");
  Serial.println("4: Alternativas com botão");
  Serial.println("5: Reset");

  //wait for user input
  serialResponse = getSerialResponse(emptySerialString);

  intSerialResponse = stringToInt(serialResponse);
  switch(intSerialResponse){
    case 0: //Aleatorio, gera questões de multiplicação com os fatores gerados aleatoriamente
      for(;;){
        x = getRandomNumber(0, 10);
        y = getRandomNumber(0, 10);
        askMultiply(x,y);

        partTime = millis();
        serialResponse = getSerialResponse(emptySerialString);
        finalTime += millis() - partTime;

        intSerialResponse = stringToInt(serialResponse);

        if(intSerialResponse == x*y){
          Serial.println("Parabens, voce acertou!");
          hits++;
        }else{
          Serial.println("Respota Incorreta");
          mistakes++;
        }
        answeredQuestions++;

        if(serialResponse[0] == 'q'){
          break;
        }
      }
    case 1: //Ordenado, pergunta a tabuada na ordem correta (0x0, 0x1, 0x2, 0x3...)
      for(x = 0;x <= 10; ++x){
        y = 0;
        for(y = 0; y <= 10; ++y){
          askMultiply(x,y);

          partTime = millis();
          serialResponse = getSerialResponse(emptySerialString);
          finalTime += millis() - partTime;

          intSerialResponse = stringToInt(serialResponse);

          if(intSerialResponse == (x*y)){
            Serial.println("Parabens, voce acertou!");
            hits++;
          }else{
            Serial.println("Resposta Incorreta");
            mistakes++;
          }
          answeredQuestions++;

          if((serialResponse[0] == 'q')){
            break;
          }
        }
      }
    case 2: //personalizado, pergunta ao usuário quais os fatores da multiplicação
      serialResponse = emptySerialString;
      while(serialResponse[0] != 'q'){

        Serial.println("Digite o primeiro multiplicador:");
        serialResponse = getSerialResponse(emptySerialString);
        x = stringToInt(serialResponse);

        Serial.println("Digite o segundo multiplicador:");
        serialResponse = getSerialResponse(emptySerialString);
        y = stringToInt(serialResponse);

        askMultiply(x,y);

        partTime = millis();
        serialResponse = getSerialResponse(emptySerialString);
        finalTime += millis() - partTime;

        intSerialResponse = stringToInt(serialResponse);

        if(intSerialResponse == (x*y)){
          Serial.println("Parabens, voce acertou!");
          hits++;
        }else{
          Serial.println("Respota Incorreta");
          mistakes++;
        }
        answeredQuestions++;
      }
    break;
    case 3: //Alternativas, escolhe uma pergunta aleatoria do aquivo questions.hpp
      serialResponse = emptySerialString;
      while(serialResponse[0] != 'q'){
        x = getRandomNumber(0, (NUMBER_OF_QUESTIONS - 1));
        //Gera um numero aleatorio de 0 a 4, representando as letras A,B,C,D e E.
        trueAlt = getRandomNumber(0, 4);
        Serial.print("Quanto é ");
        Serial.print(questions[x]);
        Serial.println(" ?");

        Serial.println(" ");

        //imprime na tela as alternativas, usando trueAlt como base para escolher qual será a correta
        for (y = 0; y < 5; y++){

          Serial.print(intToLetter(y));
          Serial.print(')');

          if(trueAlt == y){
            Serial.println(answers[x]);
          }else{
            Serial.println((answers[x] - getRandomNumber(1, 100)));
          }
        }

        partTime = millis();
        serialResponse = getSerialResponse(emptySerialString);
        finalTime += millis() - partTime;

        if(serialResponse[0] == intToLetter(trueAlt)){
          Serial.println("Parabens, voce acertou!");
          hits++;
        }else{
          Serial.println("Respota Incorreta");
          mistakes++;
        }
        answeredQuestions++;
        delay(500);
      }
    break;
    case 4: //Alternativas com botão, escolhe uma pergunta aleatoria no arquivo questions.hpp
      serialResponse = emptySerialString;
      while(serialResponse[0] != 'q'){
        x = getRandomNumber(0, (NUMBER_OF_QUESTIONS - 1));
        //Gera um numero aleatorio de 0 a 4, representando as letras A,B,C,D e E.
        trueAlt = getRandomNumber(0, 4);
        Serial.print("Quanto é ");
        Serial.print(questions[x]);
        Serial.println(" ?");

        Serial.println(" ");

        //imprime na tela as alternativas, usando trueAlt como base para escolher qual será a correta
        for (y = 0; y < 5; y++){

          Serial.print(intToLetter(y));
          Serial.print(')');

          if(trueAlt == y){
            Serial.println(answers[x]);
          }else{
            Serial.println((answers[x] - getRandomNumber(1, 100)));
          }
        }

        partTime = millis();
        serialResponse = getButtonsResponse();
        finalTime += millis() - partTime;

        if(serialResponse[0] == intToLetter(trueAlt)){
          Serial.println("Parabens, voce acertou!");
          hits++;
        }else{
          Serial.println("Respota Incorreta");
          mistakes++;
        }
        answeredQuestions++;
        delay(500);
      }
    break;
    case 5: //reset
      reset();
      Serial.println("Resetado com sucesso");
    break;
    default:
    // do nothing
    break;
  }

  Serial.print("De ");
  Serial.print(answeredQuestions);
  Serial.print(" perguntas, você acertou ");
  Serial.print(hits);
  Serial.print(" vezes, e errou ");
  Serial.print(mistakes);
  Serial.println(" vezes");

  Serial.print("Isso significa que você acertou ");
  Serial.print(((hits*100)/answeredQuestions));
  Serial.println("%");

  delay(1000);

  Serial.print("Voce demorou ");
  Serial.print(int(finalTime/1000));
  Serial.println(" Segundos");
}