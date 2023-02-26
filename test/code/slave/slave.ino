// DECLARE THE ULTRASONIC PINES
// Ultrasonic above the rail
int T1 = 13; // Trigger 
int E1 = 12; // Echo

// Ultrasonic in left side
int T2 = 11; // Trigger
int E2 = 10; // Echo
int travelTime2;sol
// Ultrasonic in right side
int T3 = 6; // Trigger
int E3 = 5; // Echo
int travelTime3;


void setup() {
  Serial.begin(9600);

  // Declare mode 
  // trigger as output
  pinMode(T1,OUTPUT); 
  pinMode(T2,OUTPUT); 
  pinMode(T3,OUTPUT); 
  // echo as input
  pinMode(E1,INPUT);
  pinMode(E2,INPUT);
  pinMode(E3,INPUT);

  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  
  digitalWrite(13, HIGH); // set teh motor
}

void startEng(bool start){
  digitalWrite(9, start);
}

void move(bool forward) {
  digitalWrite(7, forward);
  digitalWrite(8, !forward);
}

void startMesuare() {
  // start sending from trigger
  digitalWrite(T1, HIGH);
  digitalWrite(T2, HIGH);
  digitalWrite(T3, HIGH);
  delayMicroseconds(10);
  // shut down 
  digitalWrite(T1, LOW);
  digitalWrite(T2, LOW);
  digitalWrite(T3, LOW);
  delay(25);
  // read the time travel This time is in us
  above( pulseIn(E1, HIGH) ); 
  travelTime2 = pulseIn(E2, HIGH);
  travelTime3 = pulseIn(E3, HIGH);

  sides(travelTime2, travelTime3);
  
}

void sides(int time1, int time2){
  int ancho = 12; // 12cm
  int ancho_caja;
  
  int t1 = time1; // tiempo que demora en llegar el izquierdo
  int t2 = time2; // tiempo que demora en llegar el derecho

  int d1 = t1/59; // distancia en cm  izquierda
  int d2 = t2/59; // distancia en cm  derecha

  ancho_caja = (ancho - d1 - d2); // ancho de la caja
  Serial.println("Ancho de la caja: " + ancho_caja);     
}
void above(int timeTravel ){
  int height = 10; // 10cm donde se encuentra el sensor de la rampa 
  int box_height; // alto de la caja
  int t; // tiempo que demora en llegar el eco
  int d; // distancia en cm
  t = timeTravel;
  d = t/59; // distancia en centimetros
  // alto de la caja
  box_height = (height - d);
  Serial.println("Alto de la caja: " + box_height);   
}

void loop() {
  // put your main code here, to run repeatedly:
  startMesuare();    
}
