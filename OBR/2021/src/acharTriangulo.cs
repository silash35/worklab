float acharTriangulo() {
  for(int i = 0; i<500; ++i){
    bc.MoveFrontal((float)800, (float)800);
    bc.wait(1);

    if(bc.Distance(0)<25){
      bc.MoveFrontalAngles(100, 90);
      i = 0;
    }
  }

  return bc.Compass();
}