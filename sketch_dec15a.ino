#include <LiquidCrystal.h>
#include <Limits.h>

// Define as conexões e cria o objeto para acesso
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int backLight = 10;
const int sensorTemp = A1;
const int sensorTensao = A2;
const int sensorTensao1= A3;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte a[8]= {B00110,B01001,B00110,B00000,B00000,B00000,B00000,B00000,};
// Limites para detecção das teclas, em ordem crescente
struct {
  int limite;
  char *nome;

} teclas[] = {
  {   50, "pressao ="},
  {  150, "tensao =" },
  {  300, "Baixo   " },
  {  500, "Esquerda" },
  {  750, "Select  " },
  { 1024, "        " }  // nenhuma tecla apertada
};
 
int temppadrao = 23; 
float pressao;  
float tensao;
float tensao1;
// Iniciação
void setup() {
  //Progama o pino de backlight como saída
  pinMode(backLight, OUTPUT);
  // Inicia o display e coloca uma mensagem
  lcd.begin(16, 2);
  //lcd.print("Sensores");
  // Acende o backlight
  digitalWrite(backLight, HIGH);
  pinMode(d4, OUTPUT);  
}
 
// Laço principal
void loop() {
  static int teclaAnt = -1;   // última tecla detectada
  int valorSensor = analogRead(sensorTemp);
  int valorSensorten = analogRead(sensorTensao);
  int valorSensorten1= analogRead(sensorTensao1);
  tensao = ((valorSensorten/1024.0)*0.5)*10;
  tensao1 = ((valorSensorten1/1024.0)*0.5)*10;
  pressao = (valorSensor*5/1024)*55;
  // Lê a tensão no pino A0
  int leitura = analogRead(A0);


  
  // Identifica a tecla apertada pela tensão lida
  int teclaNova;
  for (teclaNova = 0; ; teclaNova++) {
    if (leitura < teclas[teclaNova].limite) {
      break;
    }
  }
  //mostra sensor pressão
 lcd.setCursor(0, 0); 
 lcd.print("pressao="); 
 lcd.setCursor(9,0);
 lcd.print(pressao);

//mostra Tensão A
 lcd.setCursor(0,1);
 lcd.print("A= ");
 lcd.setCursor(3,1);
 lcd.print(tensao);

 //mostrar tensão B
 lcd.setCursor(9,1);
 lcd.print("B= ");
 lcd.setCursor(12,1);
 lcd.print(tensao1);

  if(teclas[teclaNova].limite == 50){
    digitalWrite(d4, HIGH);
  }




   
    
   /* Atualiza a tela se pressionou uma nova tecla
  if (teclaNova != teclaAnt) {
    lcd.setCursor(0,1);
    lcd.print(teclas[teclaNova].nome);
    if(teclas[teclaNova].limite == 50 ){
      lcd.print(temperaturaC);
    } else{
      lcd.print("            ");
    }
    if (teclas[teclaNova].limite == 150){
      lcd.setCursor(9, 1);      
      lcd.print(tensao);
      lcd.setCursor(13, 1);      
      lcd.print("V");
    }else{
      lcd.print("         ");
    }
    
    teclaAnt = teclaNova;
  }
 */
  // Dá um tempo antes do próximo teste
  delay (100);
}