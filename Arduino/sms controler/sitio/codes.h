/*
Envie os códigos a seguir para o SMS e os comandos serão executados. É possível programar a execução
do comandos de ligar e desligar as bombas mandando o comando-0000 sendo 0000 o numero de minutos
para o comando ser executado. Exemplos:
LB1-0005 irá ligar a bomba 1 depois de 5 minutos.
DB5-1000 irá desligar a bomba 5 depois de 1000 minutos.
LB3-0060 irá ligar a bomba 3 depois de 1 hora.

IMPORTANTE: Sempre envie os comandos com 4 caracteres, nem mais nem menos
*/

// Códigos para Ligar as Bombas (Ligar Bomba X)
#define LB1 "LB1"
#define LB2 "LB2"
#define LB3 "LB3"
#define LB4 "LB4"
#define LB5 "LB5"

// Códigos para Desligar as Bombas (Desligar Bomba X)
#define DB1 "DB1"
#define DB2 "DB2"
#define DB3 "DB3"
#define DB4 "DB4"
#define DB5 "DB5"

// Códigos para requerer informações dos sensores (Read Sensor X)
#define RS1 "RS1"
#define RS2 "RS2"
#define RS3 "RS3"
#define RS4 "RS4"
#define RS5 "RS5"