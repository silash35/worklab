#define MAX 900

int readBot(){
  
  int ires = 635;
  while(ires == 635){
    if(analogRead(A0) < MAX){
      ires = int('a');  
    }

    if(analogRead(A1) < MAX){
      ires = int('b');  
    }

    if(analogRead(A2) < MAX){
      ires = int('c');  
    }

    if(analogRead(A3) < MAX){
      ires = int('d');  
    }

    if(analogRead(A4) < MAX){
      ires = int('e');
    }

    if(analogRead(A5) < MAX){
      ires = int('q');  
    }
  }
  
  return ires;
}
