/*
Envie os códigos a seguir + numero da bomba (Que vão de 0 a 4) para o SMS e os comandos serão
executados. É possível programar a execução do comandos de ligar e desligar as bombas mandando o
comando-0000 sendo 0000 o numero de minutos para o comando ser executado.

Caso o comando seja enviado sem o numero da bomba, então o comando valerá para todas as bombas.
Nesse caso não será possível programar a execução do comando e ele será executado instantaneamente
independentemente do tempo dado

Exemplos:
LB0-0005 irá ligar a bomba 0 depois de 5 minutos.
DB4-1000 irá desligar a bomba 4 depois de 1000 minutos.
LB2-0060 irá ligar a bomba 2 depois de 1 hora.

IMPORTANTE: Sempre envie os tempo com 4 caracteres, nem mais nem menos
*/

// Código para Ligar as Bombas (Ligar Bomba X)
#define LB "LB"

// Código para Desligar as Bombas (Desligar Bomba X)
#define DB "DB"

// Código para requerer informações dos sensores (Read Sensor X)
#define RS "RS"