#define NUMBER_OF_QUESTIONS 80
String questions[NUMBER_OF_QUESTIONS]; //Array de Strings que vai armazenar as questões para o modo Alternativas
int answers[NUMBER_OF_QUESTIONS];  // Array de int que vai armazenar as respostas das questões do Array acima

void assimilate(){

  questions[0] = "{((2+[((-7)+3)-5+(-2)]}";
  answers[0] = -9;

  questions[1] = "{((2+(-3))-5+(-2)}";
  answers[1] = -8;

  questions[2] = "1+1+1+1+1+1";
  answers[2] = 5;

  questions[3] = "";
  answers[3] = 0;

  //...
}
