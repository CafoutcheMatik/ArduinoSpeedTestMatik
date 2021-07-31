// Arduino Speed Test Benchmarking Program
// Original Program Credit: Arduino.cc
// pour ARDUINO MEGA 2560 REV3
//
// Adapté par Hervé CHUTEAU
// pour le BistroMatik
// août 2021
// dans le cadre d'un projet de séquenceur hardware
// avec acquisition de +500 boutons avec led et de +70 potentiomètres
// le but n'est pas de comparer la vitesse de différents Arduino mais d'estimer le temps probable des instructions

// découvert sur http://electroniqueamateur.blogspot.com/2019/07/test-de-vitesse-arduino-uno-stm32.html
// Source originale : https://github.com/RafaGS/Arduino-Speedtest/blob/master/Arduino-Speedtest.ino
// Comme l'ARDUINO MEGA est lent, le code des boucles est simplifié en utilisant les micro secondes

#include <Arduino.h>
// Permet de forcer le compilateur à ne faire aucune optimisation pouvant fausser les relevés
// probable qur déclarer les variables "volatile" est le même résultat
// A priori ne fonctionne pas pour un fichier INO
#pragma GCC optimize("-O0")

#define PIN_ENTREE_PULLUP 13       // PIN configurée en entrée avec PullUp interne
#define PIN_ENTREE 12              // PIN configurée en entrée
#define PIN_SORTIE 11              // PIN configurée en sortie
#define SERIAL_SPEED_HIGH 250000ul // sur ce projet 250000bauds
#define SERIAL_SPEED_LOW 9600      // bauds trés lent
#define NB_BOUCLE 10000            // la mesure de temps à la micro seconde sur Méga
#define DELAY_PRINT 0              // pour laisser le temps de vider le buffer en millis

unsigned int i; // int pour ne pas trop impacter
// dans l'original ajout de "register"
volatile bool auxBool;
volatile bool bool_3, bool_11, bool_12, bool_21, bool_22, bool_31, bool_32, bool_41, bool_42, bool_51, bool_52;
volatile byte auxByte;
volatile byte byte_3, byte_11, byte_12, byte_21, byte_22, byte_31, byte_32, byte_41, byte_42, byte_51, byte_52;
volatile char auxChar;
volatile char char_1, char_2, char_3;
volatile int auxInt;
volatile unsigned int auxUnsignedInt;
volatile int int_3, int_11, int_12, int_21, int_22, int_31, int_32, int_41, int_42, int_51, int_52;
volatile word auxWord;
volatile word word_1, word_2, word_3;
volatile long auxLong;
volatile unsigned long auxUnsignedLong;
volatile long long_3, long_11, long_12, long_21, long_22, long_31, long_32, long_41, long_42, long_51, long_52;
volatile long long auxLongLong;
volatile long long longLong_1, longLong_2, longLong_3;
volatile float auxFloat;
volatile float float_3, float_11, float_12, float_21, float_22, float_31, float_32, float_41, float_42, float_51, float_52;
volatile double auxDouble;
volatile double double_1, double_2, double_3;
volatile String auxString;

/* Valeur dans ArduinoSpeedTest
* byte  * 2, 3    / 253, 3    + 1, 2
* int   * 2, 3    / 31415, 3  + 1, 3
* long   * 2, 3   / 2000000000L, 3   + 500000000L, 123
* float  * 3.24, 1.25   / 312645.24, 1.21   + 9876.54, 1.23;
* itoa  1     ltoa 314159L   dtostrf (3.14159265, 6, 2, buffer)   random(-2147483647,2147483647);
*/
unsigned long auxMicros, dureeBoucleVide, dureeTest;
float dureeMicros_0, dureeMicros_1, dureeMicros_2, dureeMicros_3, dureeMicros_4, dureeMicros_5, dureeMicros_6;
float dureeMicrosMin_1, dureeMicrosMin_2, dureeMicrosMin_3, dureeMicrosMin_4, dureeMicrosMin_5, dureeMicrosMin_6;
float dureeMicrosMax_1, dureeMicrosMax_2, dureeMicrosMax_3, dureeMicrosMax_4, dureeMicrosMax_5, dureeMicrosMax_6;

void setup()
{
  Serial.begin(SERIAL_SPEED_HIGH);

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB
  }

  pinMode(PIN_SORTIE, OUTPUT);
  pinMode(PIN_ENTREE, INPUT);
  pinMode(PIN_ENTREE_PULLUP, INPUT);

  Serial.begin(SERIAL_SPEED_HIGH);

  delay(DELAY_PRINT);
  Test();
}

void loop()
{
  // On laisse vide, le test n'est fait qu'une fois
}

void Test()
{

  //

  Serial.println(F("Speed test Matik"));
  Serial.println(F("\"us\" pour micro seconde"));
  Serial.println(F("----------"));
  Serial.print(F("F_CPU = "));
  Serial.print(F_CPU / 1000000, DEC);
  Serial.println(F(" MHz"));
  Serial.print(F("1/F_CPU = "));
  Serial.print((1000000.0 / (float)F_CPU), 4);
  Serial.println(F(" us"));

  delay(1000); // temps de transmission pour libérer le Serial

  auxMicros = micros();
  for (i = 0; i < (NB_BOUCLE); i++)
  {
    // Boucle vide permettant de mesurer le temps pris par une boucle vide
    // la mesure est au pas de 4 microsecondes
  }
  dureeBoucleVide = micros() - auxMicros;
  Serial.println(F(""));
  Serial.print("temps d'exécution d'une boucle vide de ");
  Serial.print(NB_BOUCLE);
  Serial.print(" = ");
  Serial.print(dureeBoucleVide);
  Serial.print(F(" soit "));
  Serial.print((float)dureeBoucleVide / (float)NB_BOUCLE);
  Serial.println(F(" us "));

  delay(1000);

  /* ***************************
  *        S I Z E O F        */
  Serial.println(F(""));
  Serial.print(F("sizeof() :"));
  Serial.print(F("   bool="));
  auxLong = sizeof(auxBool);
  Serial.print(auxLong);
  Serial.print(F("   byte="));
  auxLong = sizeof(auxByte);
  Serial.print(auxLong);
  Serial.print(F("   int="));
  auxLong = sizeof(auxInt);
  Serial.print(auxLong);
  Serial.print(F("   word="));
  auxLong = sizeof(auxWord);
  Serial.print(auxLong);
  Serial.print(F("   long="));
  auxLong = sizeof(auxLong);
  Serial.print(auxLong);
  Serial.print(F("   long_long="));
  auxLong = sizeof(auxLongLong);
  Serial.print(auxLong);
  Serial.print(F("   float="));
  auxLong = sizeof(auxFloat);
  Serial.print(auxLong);
  Serial.print(F("   double="));
  auxLong = sizeof(auxDouble);
  Serial.println(auxLong);
  Serial.println(F("les tests numériques se feront pour les types : byte int long float"));
  Serial.println(F(""));
  Serial.print(F("valeur en us (microseconde"));
  Serial.println(F(""));
  delay(DELAY_PRINT);

  /* ***************************
  *   D E B O R D E M E N T   */
  Serial.println(F(""));
  Serial.print(F("débordement 0-10 :"));
  Serial.print(F("   char="));
  auxChar = 0;
  auxChar -= 10;
  Serial.print(auxChar);
  Serial.print(F("   byte="));
  auxByte = 0;
  auxByte -= 10;
  Serial.print(auxByte);
  Serial.print(F("   int="));
  auxInt = 0;
  auxInt -= 10;
  Serial.print(auxInt);
  Serial.print(F("   unsigned int="));
  auxUnsignedInt = 0;
  auxUnsignedInt -= 10;
  Serial.print(auxUnsignedInt);
  Serial.print(F("   word="));
  auxWord = 0;
  auxWord -= 10;
  Serial.print(auxWord);
  Serial.print(F("   long="));
  auxLong = 0;
  auxLong -= 10;
  Serial.print(auxLong);
  Serial.print(F("   unsigned long="));
  auxUnsignedLong = 0;
  auxUnsignedLong -= 10;
  Serial.print(auxUnsignedLong);
  Serial.print(F("   float="));
  auxFloat = 0;
  auxFloat -= 10;
  Serial.print(auxFloat);
  Serial.println(F(""));
  delay(DELAY_PRINT);


  Serial.println(F("int val1 = 3;  int val2 = 2;  float val3;"));
  Serial.print(F("val3 = val1 / val1;   donne val3="));
  int_11 = 3;
  int_12 = 2;
auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = int_11 / int_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  Serial.print(auxFloat);
Serial.print(" en ");
Serial.println(dureeMicros_1);

Serial.print(F("val3 = (float)val1 / (float)val1;   donne un résultat faux val3="));
auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = (float)int_11 / (float)int_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  Serial.print(auxFloat);
Serial.print(" en ");
Serial.println(dureeMicros_1);
  

Serial.println(F(""));

  /* ***************************************
*               B Y T E                 */
  dureeMicrosMin_1 = 0;
  dureeMicrosMin_2 = 0;
  dureeMicrosMin_3 = 0;
  dureeMicrosMin_4 = 0;
  dureeMicrosMin_5 = 0;
  dureeMicrosMin_6 = 0;
  dureeMicrosMax_1 = 0;
  dureeMicrosMax_2 = 0;
  dureeMicrosMax_3 = 0;
  dureeMicrosMax_4 = 0;
  dureeMicrosMax_5 = 0;
  dureeMicrosMax_6 = 0;

  byte_11 = 2; // addition
  byte_12 = 1;
  byte_21 = 2; // soustraction
  byte_22 = 1;
  byte_31 = 2; // multiplication
  byte_32 = 3;
  byte_41 = 253; // division
  byte_42 = 3;
  byte_51 = 13; // modulo
  byte_52 = 3;
  Test_Byte("byte ArduinoSpeedTest    ");
  //
  byte_11 = (byte)210; // addition
  byte_12 = (byte)123;
  byte_21 = (byte)210; // soustraction
  byte_22 = (byte)123;
  byte_31 = (byte)11; // multiplication
  byte_32 = (byte)22;
  byte_41 = (byte)255; // division
  byte_42 = (byte)12;
  byte_51 = (byte)255; // modulo
  byte_52 = (byte)7;
  Test_Byte("byte 123                 ");
  //
  byte_11 = 2; // addition
  byte_12 = 1;
  byte_21 = 2; // soustraction
  byte_22 = 1;
  byte_31 = 2; // multiplication
  byte_32 = 1;
  byte_41 = 3; // division
  byte_42 = 2;
  byte_51 = 3; // modulo
  byte_52 = 2;
  Test_Byte("byte 1                   ");
  //
  Serial.print("byte min_max             ");
  Serial.print(F(" + "));
  Serial.print(dureeMicrosMin_1, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicrosMin_2, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicrosMin_3, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicrosMin_4, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_4, 2);
  Serial.print(F("   % "));
  Serial.print(dureeMicrosMin_5, 2);
  Serial.print(F("_"));
  Serial.println(dureeMicrosMax_5, 2);
  Serial.println(" ");
  delay(DELAY_PRINT);

  /* ***************************************
*                I N T                  */
  dureeMicrosMin_1 = 0;
  dureeMicrosMin_2 = 0;
  dureeMicrosMin_3 = 0;
  dureeMicrosMin_4 = 0;
  dureeMicrosMin_5 = 0;
  dureeMicrosMin_6 = 0;
  dureeMicrosMax_1 = 0;
  dureeMicrosMax_2 = 0;
  dureeMicrosMax_3 = 0;
  dureeMicrosMax_4 = 0;
  dureeMicrosMax_5 = 0;
  dureeMicrosMax_6 = 0;

  int_11 = 3; // addition
  int_12 = 1;
  int_21 = 3; // soustraction
  int_22 = 1;
  int_31 = 2; // multiplication
  int_32 = 3;
  int_41 = 31415; // division
  int_42 = 3;
  int_51 = 31415; // modulo
  int_52 = 3;
  Test_Int("int ArduinoSpeedTest     ");
  //
  int_11 = 123; // addition
  int_12 = 123;
  int_21 = 255; // soustraction
  int_22 = 123;
  int_31 = 12; // multiplication
  int_32 = 11;
  int_41 = 253; // division
  int_42 = 12;
  int_51 = 253; // modulo
  int_52 = 7;
  Test_Int("int 123                  ");
  //
  int_11 = 2; // addition
  int_12 = 1;
  int_21 = 2; // soustraction
  int_22 = 1;
  int_31 = 2; // multiplication
  int_32 = 1;
  int_41 = 3; // division
  int_42 = 2;
  int_51 = 3; // modulo
  int_52 = 2;
  Test_Int("int 1                    ");
  //
  Serial.print("int min_max              ");
  Serial.print(F(" + "));
  Serial.print(dureeMicrosMin_1, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicrosMin_2, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicrosMin_3, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicrosMin_4, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_4, 2);
  Serial.print(F("   % "));
  Serial.print(dureeMicrosMin_5, 2);
  Serial.print(F("_"));
  Serial.println(dureeMicrosMax_5, 2);
  Serial.println(" ");
  delay(DELAY_PRINT);

  /* ***************************************
*               L O N G                  */
  dureeMicrosMin_1 = 0;
  dureeMicrosMin_2 = 0;
  dureeMicrosMin_3 = 0;
  dureeMicrosMin_4 = 0;
  dureeMicrosMin_5 = 0;
  dureeMicrosMin_6 = 0;
  dureeMicrosMax_1 = 0;
  dureeMicrosMax_2 = 0;
  dureeMicrosMax_3 = 0;
  dureeMicrosMax_4 = 0;
  dureeMicrosMax_5 = 0;
  dureeMicrosMax_6 = 0;

  long_11 = 500000000L; // addition
  long_12 = 123;
  long_21 = 500000000L; // soustraction
  long_22 = 123;
  long_31 = 2; // multiplication
  long_32 = 3;
  long_41 = 2000000000L; // division
  long_42 = 3;
  long_51 = 2000000000L; // modulo
  long_52 = 3;
  Test_Long("long ArduinoSpeedTest    ");
  //
  long_11 = 123456789L; // addition
  long_12 = 1234578L;
  long_21 = 123456789L; // soustraction
  long_22 = 1234567L;
  long_31 = 1234567L; // multiplication
  long_32 = 123456L;
  long_41 = 123456789L; // division
  long_42 = 123456L;
  long_51 = 123456789L; // modulo
  long_52 = 7L;
  Test_Long("long 123                 ");
  //
  long_11 = 2; // addition
  long_12 = 1;
  long_21 = 2; // soustraction
  long_22 = 1;
  long_31 = 2; // multiplication
  long_32 = 1;
  long_41 = 3; // division
  long_42 = 2;
  long_51 = 3; // modulo
  long_52 = 2;
  Test_Long("long 1                   ");
  //
  Serial.print("long min_max             ");
  Serial.print(F(" + "));
  Serial.print(dureeMicrosMin_1, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicrosMin_2, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicrosMin_3, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicrosMin_4, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_4, 2);
  Serial.print(F("   % "));
  Serial.print(dureeMicrosMin_5, 2);
  Serial.print(F("_"));
  Serial.println(dureeMicrosMax_5, 2);
  Serial.println(" ");
  delay(DELAY_PRINT);

  /* ***************************************
*               F L O A T                 */
  dureeMicrosMin_1 = 0;
  dureeMicrosMin_2 = 0;
  dureeMicrosMin_3 = 0;
  dureeMicrosMin_4 = 0;
  dureeMicrosMin_5 = 0;
  dureeMicrosMin_6 = 0;
  dureeMicrosMax_1 = 0;
  dureeMicrosMax_2 = 0;
  dureeMicrosMax_3 = 0;
  dureeMicrosMax_4 = 0;
  dureeMicrosMax_5 = 0;
  dureeMicrosMax_6 = 0;

  float_11 = 9876.54; // addition
  float_12 = 1.23;
  float_21 = 9876.54; // soustraction
  float_22 = 1.23;
  float_31 = 3.24; // multiplication
  float_32 = 1.25;
  float_41 = 312645.24; // division
  float_42 = 1.21;
  float_51 = 312645.24; // division
  float_52 = 1.21;
  Test_Float("float ArduinoSpeedTest   ");
  //

  float_11 = 123456789.123; // addition
  float_12 = 1234578.321;
  float_21 = 123456789.123; // soustraction
  float_22 = 1234567.321;
  float_31 = 123456789.123; // multiplication
  float_32 = 123456.321;
  float_41 = 123456789.123; // division
  float_42 = 123.456;
  float_51 = 123456789.123; // division
  float_52 = 123.456;
  Test_Float("float 123                ");
  float_11 = 123456.789123; // addition
  float_12 = 1234.578321;
  float_21 = 123456.789123; // soustraction
  float_22 = 1234.567321;
  float_31 = 123456.789123; // multiplication
  float_32 = 123.456321;
  float_41 = 123456.789123; // division
  float_42 = 1.23456;
  float_51 = 123456.789123; // division
  float_52 = 1.23456;
  Test_Float("float 12                 ");
  //
  float_11 = 2.123; // addition
  float_12 = 1.321;
  float_21 = 2.123; // soustraction
  float_22 = 1.321;
  float_31 = 2.123; // multiplication
  float_32 = 1.321;
  float_41 = 3.123; // division
  float_42 = 2.321;
  float_51 = 3.123; // division
  float_52 = 2.321;
  Test_Float("float 1                  ");
  //
  Serial.print("float min_max            ");
  Serial.print(F(" + "));
  Serial.print(dureeMicrosMin_1, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicrosMin_2, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicrosMin_3, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicrosMin_4, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_4, 2);
  Serial.print(F("   /= "));
  Serial.print(dureeMicrosMin_5, 2);
  Serial.print(F("_"));
  Serial.println(dureeMicrosMax_5, 2);
  delay(DELAY_PRINT);

/* **********************************
  *       C O N V E R S I O N       */

  // BYTE
  byte_11 = 123;
  int_11 = 12345;
  long_11 = 123456789l;
  float_11 = 123456.789f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxByte = (byte)int_11;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxByte = (byte)long_11;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxByte = (byte)float_11;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.println(F(""));
  Serial.print("conversion vers byte   ");
  Serial.print(F(" int "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   float "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  // INT
  byte_11 = 123;
  int_11 = 12345;
  long_11 = 123456789l;
  float_11 = 123456.789f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxInt = (int)byte_11;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxInt = (int)long_11;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxInt = (int)float_11;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.print("conversion vers int    ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   float "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  // LONG
  byte_11 = 123;
  int_11 = 12345;
  long_11 = 123456789l;
  float_11 = 123456.789f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxLong = (int)byte_11;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxLong = (int)int_11;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxLong = (int)float_11;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.print("conversion vers long   ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   float "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  // FLOAT
  byte_11 = 123;
  int_11 = 12345;
  long_11 = 123456789l;
  float_11 = 123456.789f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = (float)byte_11;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = (float)int_11;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = (float)long_11;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.print("conversion vers float  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);



  /* **********************************
  *             M A T H             */

  float_11 = 1.00f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = sin(float_11);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = cos(float_11);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = tan(float_11);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.println(F(""));
  Serial.print("Math sur float (écart important selon valeur)  ");
  Serial.print(F(" sin "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   cos "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   tan "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  //
float_11 = 123456.789f;
float_12 = 3.00f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = abs(float_11);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = pow(float_11,float_12);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = sq(float_11);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.print("Math sur float (écart possible selon valeur)  ");
  Serial.print(F(" abs "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   pow "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   sq "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);

/* **********************************
  *       C O N S T R A I N           */

  int_11 = 12345;
  long_11 = 123456789l;
  float_11 = 123.25f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxInt = constrain(int_11,1000,2000);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxLong = constrain(long_11,1000000,2000000);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = constrain(float_11,(float)1000,(float)2000);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("constrain : limite min-max   ");
  Serial.print(F(" int "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   float "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  
/* **********************************
  *    M A P   mise à l'échelle     */

  int_11 = 123;
  long_11 = 123l;
  float_11 = 123.25f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxInt = map(int_11,100,200,1000,2000);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxLong = map(long_11,100,200,1000,2000);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = map(float_11,(float)100,(float)200,(float)1000,(float)2000);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("map : mise à l'échelle   ");
  Serial.print(F(" int "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   float "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);

/* **********************************
  *       M I N      M A X        */

  int_11 = 123;
  int_12 = 321;
  long_11 = 12345l;
  long_12 = 65432l;
  float_11 = 123.45f;
  float_12 = 543.21f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxInt = max(int_11,int_12);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxLong = max(long_11,long_12);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxFloat = max(float_11,float_12);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("min max    ");
  Serial.print(F(" int "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   float "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);

/* **********************************
  *         R A N D O M           */

  long_12 = 123456;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxLong = random(float_11);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("random (long)    ");
  Serial.println(dureeMicros_1, 2);
  delay(DELAY_PRINT);


  /* **********************************
  *       B O O L   E T    O U       */
  bool_11 = true;
  bool_12 = false;
  bool_21 = true;
  bool_22 = false;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bool_3 = bool_11 && bool_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bool_3 = bool_21 || bool_22;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.println("opération booléen   ");
  Serial.print(F("bool                && "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   || "));
  Serial.println(dureeMicros_2, 2);
  delay(DELAY_PRINT);

  //
  /* *************************************
  *  T E S T    c O M P A R A I S O N  */
  //
  byte_11 = 123;
  byte_21 = 210;
  int_21 = 12345;
  int_22 = 54321;
  long_31 = 123456789l;
  long_32 = 987654321l;
  float_41 = 123456.789f;
  float_42 = 987654.321f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bool_3 = byte_11 == byte_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bool_3 = int_21 == int_22;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bool_3 = long_31 == long_32;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bool_3 = float_41 == float_42;
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_4, &dureeMicrosMax_4, &dureeMicros_4);
  Serial.println(F(""));
  Serial.print("test comparaison  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   float "));
  Serial.println(dureeMicros_4, 2);
  delay(DELAY_PRINT);
  /* *************************************
  *      B O O L E A N   bit à bit    */
  //
  byte_11 = 123;
  byte_21 = 210;
  int_21 = 12345;
  int_22 = 54321;
  long_31 = 123456789l;
  long_32 = 987654321l;
  float_41 = 123456.789f;
  float_42 = 987654.321f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_11 ^ byte_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_21 ^ int_22;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_31 ^ long_32;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.println(F(""));
  Serial.print("booléen bit à bit  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicros_3, 2);
  delay(DELAY_PRINT);

  /* *************************************
  *      B O O L E A N   bit à bit    */
  //
  byte_11 = 123;
  byte_21 = 210;
  int_21 = 12345;
  int_22 = 54321;
  long_31 = 123456789l;
  long_32 = 987654321l;
  float_41 = 123456.789f;
  float_42 = 987654.321f;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = ~byte_11;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = ~int_21;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = ~long_31;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;

  //
  Serial.println(F(""));
  Serial.print("  NOT ~ bit à bit  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.println(dureeMicros_3, 2);
  Serial.println(F(""));
  delay(DELAY_PRINT);

  /* ***************************************
*         D E C A L A G E    <<           */
  dureeMicrosMin_1 = 0;
  dureeMicrosMin_2 = 0;
  dureeMicrosMin_3 = 0;
  dureeMicrosMin_4 = 0;
  dureeMicrosMin_5 = 0;
  dureeMicrosMin_6 = 0;
  dureeMicrosMax_1 = 0;
  dureeMicrosMax_2 = 0;
  dureeMicrosMax_3 = 0;
  dureeMicrosMax_4 = 0;
  dureeMicrosMax_5 = 0;
  dureeMicrosMax_6 = 0;
  //
  byte_11 = 0b01010101;
  int_21 = 0b01010101010101;
  long_31 = 0b0101010101010101010101010101l;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_11 << 1;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_11 << 1;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_31 << 1;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //

  Serial.println(F(""));
  Serial.print("décalage gauche <<  1    ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  byte_11 = 0b01010101;
  int_21 = 0b01010101010101;
  long_31 = 0b0101010101010101010101010101l;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_11 << 7;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_11 << 15;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_31 << 31;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //

  Serial.print("décalage gauche <<  max  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.println(dureeMicros_3, 2);
  delay(500);
  Serial.print("décalage gauche min_max  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicrosMin_1, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicrosMin_2, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_2, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicrosMin_3, 2);
  Serial.print(F("_"));
  Serial.println(dureeMicrosMax_3, 2);
  delay(DELAY_PRINT);

  /* ***************************************
*         D E C A L A G E    >>           */
  dureeMicrosMin_1 = 0;
  dureeMicrosMin_2 = 0;
  dureeMicrosMin_3 = 0;
  dureeMicrosMin_4 = 0;
  dureeMicrosMin_5 = 0;
  dureeMicrosMin_6 = 0;
  dureeMicrosMax_1 = 0;
  dureeMicrosMax_2 = 0;
  dureeMicrosMax_3 = 0;
  dureeMicrosMax_4 = 0;
  dureeMicrosMax_5 = 0;
  dureeMicrosMax_6 = 0;
  //
  byte_11 = 0b01010101;
  int_21 = 0b01010101010101;
  long_31 = 0b0101010101010101010101010101l;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_11 >> 1;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_11 >> 1;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_31 >> 1;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //

  Serial.println(F(""));
  Serial.print("décalage droit >>  1    ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  byte_11 = 0b01010101;
  int_21 = 0b01010101010101;
  long_31 = 0b0101010101010101010101010101l;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_11 >> 7;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_11 >> 15;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_31 >> 31;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //

  Serial.print("décalage droit >>  max  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   long "));
  Serial.println(dureeMicros_3, 2);
  delay(500);
  Serial.print("décalage droit min_max  ");
  Serial.print(F(" byte "));
  Serial.print(dureeMicrosMin_1, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_1, 2);
  Serial.print(F("   int "));
  Serial.print(dureeMicrosMin_2, 2);
  Serial.print(F("_"));
  Serial.print(dureeMicrosMax_2, 2);
  Serial.print(F("   long "));
  Serial.print(dureeMicrosMin_3, 2);
  Serial.print(F("_"));
  Serial.println(dureeMicrosMax_3, 2);
  delay(DELAY_PRINT);

  /* ***************************************
*         low  high word           */
  //
  auxInt = 0b0000000111111110;
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxByte = lowByte(auxInt);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxByte = highByte(auxInt);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxUnsignedInt = word(auxByte, auxByte);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("extraction de byte  ");
  Serial.print(F(" lowByte "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   highByte "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   word "));
  Serial.println(dureeMicros_3, 2);
  delay(DELAY_PRINT);
  //
  /* ***************************************
*      P O I D S    D U    B I T       */
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxUnsignedLong = bit(0);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxUnsignedLong = bit(7);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxUnsignedLong = bit(15);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxUnsignedLong = bit(31);
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("poids du byte  ");
  Serial.print(F(" 0="));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   7="));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   15="));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   31="));
  Serial.println(dureeMicros_4, 2);
  delay(DELAY_PRINT);

  /* ***************************************
*          B I T             */
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bitSet(auxByte, 0);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bitClear(auxByte, 0);
    ;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = bitRead(auxByte, 0);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = bitWrite(auxByte, 0, false);
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("byte  ");
  Serial.print(F(" bitSet "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   BitClear "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   bitRead "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   bitWrite "));
  Serial.println(dureeMicros_4, 2);
  delay(DELAY_PRINT);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bitSet(auxInt, 0);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bitClear(auxInt, 0);
    ;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = bitRead(auxInt, 0);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = bitWrite(auxInt, 0, false);
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.print("int   ");
  Serial.print(F(" bitSet "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   BitClear "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   bitRead "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   bitWrite "));
  Serial.println(dureeMicros_4, 2);
  delay(DELAY_PRINT);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bitSet(auxLong, 0);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    bitClear(auxLong, 0);
    ;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = bitRead(auxLong, 0);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = bitWrite(auxLong, 0, false);
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.print("long  ");
  Serial.print(F(" bitSet "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   BitClear "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   bitRead "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   bitWrite "));
  Serial.println(dureeMicros_4, 2);
  delay(DELAY_PRINT);


/* ***************************************
*            G P I O           */

  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = digitalRead(PIN_ENTREE);
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = digitalRead(PIN_ENTREE_PULLUP);
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    digitalWrite(PIN_SORTIE,LOW);
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxByte = PINA;
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    auxBool = PINA0;
  }
  dureeMicros_5 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  //
  Serial.println(F(""));
  Serial.print("GPIO    ");
  Serial.print(F(" digitalRead "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   digitalRead_pullup "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   digitalWrite "));
  Serial.print(dureeMicros_3, 2);
    Serial.print(F("   registre PINA "));
  Serial.print(dureeMicros_4, 2);
  Serial.print(F("   registre PINA0 "));
  Serial.print(dureeMicros_5, 2);
  delay(DELAY_PRINT);




  /* ***************************
  *          F I N          */
}

/* ***************************************
*       sous programme    B Y T E       */
void Test_Byte(const char *stexte)
{
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_11 + byte_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_21 - byte_22;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_31 * byte_32;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_41 / byte_42;
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_4, &dureeMicrosMax_4, &dureeMicros_4);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    byte_3 = byte_51 % byte_52;
  }
  dureeMicros_5 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_5, &dureeMicrosMax_5, &dureeMicros_5);
  //
  Serial.print(stexte);
  Serial.print(F(" + "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicros_4, 2);
  Serial.print(F("   % "));
  Serial.println(dureeMicros_5, 2);
  delay(DELAY_PRINT);
}

/* ***************************************
*        sous programme    I N T        */
void Test_Int(const char *stexte)
{
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_11 + int_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_21 - int_22;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_31 * int_32;
    ;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_41 / int_42;
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_4, &dureeMicrosMax_4, &dureeMicros_4);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    int_3 = int_51 % int_52;
    ;
  }
  dureeMicros_5 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_5, &dureeMicrosMax_5, &dureeMicros_5);
  //
  Serial.print(stexte);
  Serial.print(F(" + "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicros_4, 2);
  Serial.print(F("   % "));
  Serial.println(dureeMicros_5, 2);
  delay(DELAY_PRINT);
}

/* ***************************************
*        sous programme    L O N G        */
void Test_Long(const char *stexte)
{
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_11 + long_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_21 - long_22;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_31 * long_32;
    ;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_41 / long_42;
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_4, &dureeMicrosMax_4, &dureeMicros_4);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    long_3 = long_51 % long_52;
  }
  dureeMicros_5 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_5, &dureeMicrosMax_5, &dureeMicros_5);
  //
  Serial.print(stexte);
  Serial.print(F(" + "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicros_4, 2);
  Serial.print(F("   % "));
  Serial.println(dureeMicros_5, 2);
  delay(DELAY_PRINT);
}

/* ***************************************
*      sous programme    F L O A T       */
void Test_Float(const char *stexte)
{
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    float_3 = float_11 + float_12;
  }
  dureeMicros_1 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_1, &dureeMicrosMax_1, &dureeMicros_1);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    float_3 = float_21 - float_22;
  }
  dureeMicros_2 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_2, &dureeMicrosMax_2, &dureeMicros_2);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    float_3 = float_31 * float_32;
  }
  dureeMicros_3 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_3, &dureeMicrosMax_3, &dureeMicros_3);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    float_3 = float_41 / float_42;
  }
  dureeMicros_4 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_4, &dureeMicrosMax_4, &dureeMicros_4);
  //
  auxMicros = micros();
  for (i = 0; i < NB_BOUCLE; i++)
  {
    float_51 /= float_52;
  }
  dureeMicros_5 = (float)(micros() - auxMicros - dureeBoucleVide) / (float)NB_BOUCLE;
  dureeMinMax(&dureeMicrosMin_5, &dureeMicrosMax_5, &dureeMicros_5);
  //
  Serial.print(stexte);
  Serial.print(F(" + "));
  Serial.print(dureeMicros_1, 2);
  Serial.print(F("   - "));
  Serial.print(dureeMicros_2, 2);
  Serial.print(F("   * "));
  Serial.print(dureeMicros_3, 2);
  Serial.print(F("   / "));
  Serial.print(dureeMicros_4, 2);
  Serial.print(F("   /= "));
  Serial.println(dureeMicros_5, 2);
  delay(DELAY_PRINT);
}

/* ***************************************
*      D U R E E   M I N   M A X        */

void dureeMinMax(float *sDureeMin, float *sDureeMax, float *sDuree)
{
  // mémorise les minis et les maxis
  if ((*sDureeMin == 0) || (*sDureeMin > *sDuree))
  {
    *sDureeMin = *sDuree;
  }
  if (*sDureeMax < *sDuree)
  {
    *sDureeMax = *sDuree;
  }
}