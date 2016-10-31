/*
  Ileana Anahi Topete Morales
  Codificador Convolucional
*/


//arreglo de lectura dipswitch
int val[4];
//arreglo para corrimiento [][][]
int secIn[3];
//arreglo de salida secuencia codificada 8 bits
int secOut[8];


int i = 0, j = 0;
int cont = 3; //cont para corrimento [][][]
int contOut = 0; //con para salida

//pines de output LEDS
int oPin[] = {2, 3, 4, 5, 6, 7, 8, 9};


void setup() {

  //leds declaracion de salidas leds
  for (i = 0; i < 8; i++) {
    pinMode(oPin[i], OUTPUT);
  }

  //switch DIP declaracion de entradas
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  //para monitor (debuguear)
  //Serial.begin(9600);

}



void loop() {
  //inicializa Secuencia de entrada [][][] en 0
  for (i = 0; i < 3; i++) {
    secIn[i] = 0;
    //inicializa los valores
    val[i] = 0;
  }
  //inicializa sec salida 8 bits
  for (i = 0; i < 8; i++) {
    secOut[i] = 0;
  }

  //obteniendo valores del dip switch
  val[0] = digitalRead(A0);
  val[1] = digitalRead(A1);
  val[2] = digitalRead(A2);
  val[3] = digitalRead(A3);

  // debuguear entrada del dip
    //Serial.println("inicio: ");
    //for (i = 0; i < 4; i++)
     // Serial.println(val[i]);

  //probar que enciendan todos los leds
  //  for (i = 0; i < 8; i++)
  //  digitalWrite(oPin[i], HIGH);

  cont = 3;
  contOut = 0;


  //mientras entren los 4bits a la secuencia de entrada
  while (cont >= 0) {
    //recorrer secuencia de entrada 1 posicion para poner un bit nuevo
    for (i = 0; i < 3; i++) {
      if (i != 2) { //ya que se recorrieron los primeros 2
        secIn[i] = secIn[i + 1];
      }
      else { //se pone un bit de la entrada
        secIn[i] = val[cont];
        cont--;
      }
    }

    //si se llenaron los 8 bits de salida recorrer para dejar 2 libres al final
    if (contOut == 8) {
      for (j = 0; j < 6; j++) {
        secOut[j] = secOut[j + 2];
      }
      contOut = 6;
    }

    //agregando bits a la salida
    //si el ultimo bit y el segundo son iguales se pone 0
    if ((secIn[2] == 0 && secIn[1] == 0) || (secIn[2] == 1 && secIn[1] == 1)) {
      secOut[contOut] = 0;
      contOut++;
    }
    else {//sino 1
      secOut[contOut] = 1;
      contOut++;
    }

    //si el ultimo y el primero son iguales se pone 0
    if ((secIn[2] == 0 && secIn[0] == 0) || (secIn[2] == 1 && secIn[0] == 1)) {
      secOut[contOut] = 0;
      contOut++;
    }
    else {//sino 1
      secOut[contOut] = 1;
      contOut++;
    }

    //aviso de que mostrara iteracion
    for (i = 0; i < 8; i++)
     digitalWrite(oPin[i], HIGH);
    delay(1000);
  
    //mostrando resultados
    for (j = 0; j < 8; j++) {
      if (secOut[j] == 0)
        digitalWrite(oPin[j], LOW);
      else
        digitalWrite(oPin[j], HIGH);
    }

    delay(5000);
  }

  //al final apagar los leds y esperar nueva entrada
  for (j = 0; j < 8; j++) {
    digitalWrite(oPin[j], LOW);
  }
  delay(10000);

}



