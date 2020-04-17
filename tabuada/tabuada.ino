#define NQ 80
String questoes[NQ]; //Array de Strings que vai armazenar as questões para o modo Alternativas
int resp[NQ];  // Array de int que vai armazenar as respostas das questões do Array acima

int x, y, ires, acertos, erros, nperguntas, aux, trueAlt;
unsigned long long int pTime, fTime; // Declaração das variaveis pTime (Tempo parcial, que armazena o resultado da função milis()) e fTime (Tempo final, que armazena o tempo parcial somado de todas as questões)
String sres, nda; //Declaração da variavel sres (Que armazena a string lida pelo Serial) e nda (Que armazena armazena o valor do Serial vazio)

int randomicNumber(int menor, int maior) { //função que gera numeros aleatorios
  delay(45);
  randomSeed(millis());
  return random(menor, maior+1);
}

void setup(){

  Serial.begin(9600);
  x = y = ires = acertos = erros = nperguntas = fTime = pTime = trueAlt= 0; //Iguala todos as variaveis Int a 0

  sres = nda = Serial.readString();
  assimilar(); //Executa a função que coloca valores nas Strings do Array questoes
}

void loop(){

  //Imprime na tela o Menu para sellecionar o modo de jogo

  Serial.println("Selecione o modo:");
  Serial.println("0: Aleatorio");
  Serial.println("1: Ordenado");
  Serial.println("2: Personalizado");
  Serial.println("3: Alternativas");
  Serial.println("4: Alternativas com botão");
  Serial.println("5: Reset");

  //Espera o usuario a digitar algo no Monitor Serial adciona o valor na variavel sres
  
  sres = nda;
  while(sres == nda){
    sres = Serial.readString();
  }

  //Se a leitura do monitor Serial diferente de 'q', converte sres para int, para podermos mexer com a variavel com mais facilidade
  
  if(sres != "q"){
    ires = sres.toInt();
  }

  switch(ires){ //Switch que vai alterar a execução do codigo dependendo do modo selecionado no menu acima
    case 0: //Aleatorio, gera questões de multiplicação com os fatores gerados aleatoriamente
      for(;;){
        x = randomicNumber(0, 10);
        y = randomicNumber(0, 10);
        Serial.print("Quanto é ");
        Serial.print(x);
        Serial.print(" X ");
        Serial.print(y);
        Serial.println(" ?");

        pTime = millis();

        sres = nda;
        while(sres == nda){
          sres = Serial.readString();
        }

        fTime += millis() - pTime; //adiciona a fTime o tempo demorado para o usuario responder
        
        if(!(sres[0] == 'q')){
          ires = sres.toInt();
        }

        aux = x*y;
  
        if(ires == aux){
          Serial.println("Parabens, voce acertou!");
          acertos++;
        }else{
          Serial.println("Respota Incorreta");
          erros++;
        }
        nperguntas++;

        if((sres[0] == 'q')){ //caso o usuario tenha digitado 'q' o programa deve parar de perguntar e voltar ao menu
          break;
        }
      }
    break;
    case 1: //Ordenado, pergunta a tabuada na ordem correta (0x0, 0x1, 0x2, 0x3...)

      for(x = 0;x <= 10; ++x){
        y = 0;
        for(y = 0; y <= 10; ++y){
          if(aux != 634){
            Serial.print("Quanto é ");
            Serial.print(x);
            Serial.print(" X ");
            Serial.print(y);
            Serial.println(" ?");
          
           pTime = millis();

           sres = nda;
           while(sres == nda){
             sres = Serial.readString();
           }

          fTime += millis() - pTime;
  
            if(!(sres[0] == 'q')){
              ires = sres.toInt();
            }

            if(ires == (x*y)){
              Serial.println("Parabens, voce acertou!");
              acertos++;
            }else{
              Serial.println("Respota Incorreta");
              erros++;
            }
            nperguntas++;
          
            if((sres[0] == 'q')){
              aux = 634; //quanto o usuario digitar q, a variavel aux recebe 634, o valor nescessario para parar o loop e voltar ao menu
            }
          }  
        }
      }
      aux = 0; //zera aux para evitar problemas
    case 2: //personalizado, pergunta ao usuario quais os fatores da multiplicação antes de perguntar
        while(!(sres[0] == 'q')){
        Serial.println("Digite o primeiro multiplicador:");
        
        sres = nda;
        while(sres == nda){
          sres = Serial.readString();
        }
        
        x = sres.toInt();
      
        Serial.println("Digite o segundo multiplicador:");
        
        sres = nda;
        while(sres == nda){
          sres = Serial.readString();
        }
        
        y = sres.toInt();

        Serial.print("Quanto é ");
        Serial.print(x);
        Serial.print(" X ");
        Serial.print(y);
        Serial.println(" ?");
          
        pTime = millis();

        sres = nda;
        while(sres == nda){
          sres = Serial.readString();
        }
        
        fTime += millis() - pTime;
  
        if(!(sres[0] == 'q')){
          ires = sres.toInt();
        }

        if(ires == (x*y)){
          Serial.println("Parabens, voce acertou!");
           acertos++;
        }else{
          Serial.println("Respota Incorreta");
          erros++;
        }
        nperguntas++;
      }
    break;
    
    case 3: //Alternativas, escolhe uma pergunta aleatoria no arquivo questoes.ino e a questiona colocando alternativas
      sres = "";
      while(sres[0] != 'q'){
        x = randomicNumber(0, (NQ - 1));
        trueAlt = randomicNumber(0, 4); //Gera um numero aleatorio de 0 a 4, representando as letras A,B,C,D e E. por exemplo, caso o numero seja 3, a alternativa correta será D 
        Serial.print("Quanto é ");
        Serial.print(questoes[x]);
        Serial.println(" ?");

        Serial.println(" ");

        switch(trueAlt){ //imprime na tela as alternativas, usando trueAlt como base para escolher qual será a correta
          case 0:
            Serial.print("a)");
            Serial.println(resp[x]);
            Serial.print("b)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
          break;
          case 1:
            Serial.print("a)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println(resp[x]);
            Serial.print("c)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
          break;
          case 2:
            Serial.print("a)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println(resp[x]);
            Serial.print("d)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
          break;
          case 3:
            Serial.print("a)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println(resp[x]);
            Serial.print("e)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
          break;
          case 4:
            Serial.print("a)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println(resp[x]);
          break;
        }

        pTime = millis();

        sres = nda;
        while(sres == nda){
          sres = Serial.readString();
        }

        fTime += millis() - pTime;

        // lê a letra que o usuario digitou e confere se ela corresponde a variavel trueAlt
       
        if(sres[0] == 'a'){
          if(trueAlt == 0){
            Serial.println("Parabens, voce acertou!");
            acertos++;
          }else{
            Serial.println("Respota Incorreta");
            erros++;
          }
        }

        if(sres[0] == 'b'){
          if(trueAlt == 1){
            Serial.println("Parabens, voce acertou!");
            acertos++;
          }else{
            Serial.println("Respota Incorreta");
            erros++;
          }
        }

        if(sres[0] == 'c'){
          if(trueAlt == 2){
            Serial.println("Parabens, voce acertou!");
            acertos++;
          }else{
            Serial.println("Respota Incorreta");
            erros++;
          }
        }

        if(sres[0] == 'd'){
          if(trueAlt == 3){
            Serial.println("Parabens, voce acertou!");
            acertos++;
          }else{
            Serial.println("Respota Incorreta");
            erros++;
          }
        }
        
        if(sres[0] == 'e'){
          if(trueAlt == 4){
            Serial.println("Parabens, voce acertou!");
            acertos++;
          }else{
            Serial.println("Respota Incorreta");
            erros++;
          }
        }
        delay(1000);
        nperguntas++;
      }
      erros++;
    break;

    case 4: //Alternativas com botão, escolhe uma pergunta aleatoria no arquivo questoes.ino e a questiona colocando alternativas, que seram respondidas usando botões nas entradas analogicas
      ires = 0;
      while(char(ires+97) != 'q'){
        x = randomicNumber(0, (NQ - 1));
        trueAlt = randomicNumber(0, 4); //Gera um numero aleatorio de 0 a 4, representando as letras A,B,C,D e E. por exemplo, caso o numero seja 3, a alternativa correta será D 
        Serial.print("Quanto é ");
        Serial.print(questoes[x]);
        Serial.println(" ?");

        Serial.println(" ");

        switch(trueAlt){ //imprime na tela as alternativas, usando trueAlt como base para escolher qual será a correta
          case 0:
            Serial.print("a)");
            Serial.println(resp[x]);
            Serial.print("b)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
          break;
          case 1:
            Serial.print("a)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println(resp[x]);
            Serial.print("c)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
          break;
          case 2:
            Serial.print("a)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println(resp[x]);
            Serial.print("d)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
          break;
          case 3:
            Serial.print("a)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println(resp[x]);
            Serial.print("e)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
          break;
          case 4:
            Serial.print("a)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("b)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("c)");
            Serial.println((resp[x] + randomicNumber(1, 100)));
            Serial.print("d)");
            Serial.println((resp[x] - randomicNumber(1, 100)));
            Serial.print("e)");
            Serial.println(resp[x]);
          break;
        }

        pTime = millis();

        ires = (readBot() - 97); //diminuir 97 para transformar o codigo char da  letra em numeros começando do inicio

        fTime += millis() - pTime;

        // checar se a letra que o usuario apertou confere com a variavel trueAlt

        if(char(ires+97) != 'q'){ //adciona 97 para poder converter em char de novo
          if(ires == trueAlt){
            Serial.println("Parabens, voce acertou!");
            acertos++;
          }else{
            Serial.println("Respota Incorreta");
            erros++;
          }
        }
        delay(1000);
        nperguntas++;
      }
      erros++;
    break;
    
    case 5: //reset, iguala todas as variaveis a 0, resetando o programa

      x = y = ires = acertos = 0;
      erros = nperguntas = 1;
      fTime = 0;
      pTime = 0;
      Serial.println("Resetado com sucesso");

    break;
  }
  erros--;
  nperguntas--;

//Imprime na tela o desempenho do usuario em responder as questões

  Serial.print("De ");
  Serial.print(nperguntas);
  Serial.print(" perguntas, você acertou ");
  Serial.print(acertos);
  Serial.print(" vezes, e errou ");
  Serial.print(erros);
  Serial.println(" vezes");

  Serial.print("Isso significa que você acertou ");
  Serial.print(((acertos*100)/nperguntas));
  Serial.println("%");

  delay(1000);
  
  Serial.print("Voce demorou ");
  Serial.print(int(fTime/1000));
  Serial.println(" Segundos");

}
