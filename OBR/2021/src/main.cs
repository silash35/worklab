importar("seguirLinha")
importar("resgate")

bool isOnRescueArea(){
  return (bc.Inclination()>300) && (bc.Distance(2)<40) && (bc.Distance(1)<40);
}

void Main() {
  bc.TurnLedOn(255, 255, 255);
  bc.ActuatorUp(8000);

  while (!isOnRescueArea()) {
    seguirLinha();
  }

  regatarBolinhas();
}
