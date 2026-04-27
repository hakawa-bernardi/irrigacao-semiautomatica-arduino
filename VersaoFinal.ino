// Inclusão das bibliotecas necessárias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_VL53L0X.h>

// Inicialização do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inicialização do sensor VL53L0X
Adafruit_VL53L0X lox;

// Definição dos pinos
#define LED_PIN 8
#define SOIL_SENSOR_PIN A0
#define RELAY_PIN 11
#define BUTTON_PIN 2

// Variáveis
unsigned long lastBlinkTime = 0;
bool ledState = false;
bool manualIrrigation = false;

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();

  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  

  digitalWrite(LED_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);

  // Inicializa o sensor VL53L0X
  if (!lox.begin()) {
  Serial.println("Falha ao iniciar VL53L0X!");
  lcd.print("ERRO VL53L0X");
  delay(2000);
}

  lcd.setCursor(0, 0);
  lcd.print("Sistema Iniciado");
  delay(2000);
  lcd.clear();
}

int medirDistancia() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {  // 4 = erro na leitura
    return measure.RangeMilliMeter / 10; // Converte para cm
  } else {
    return -1; // Indica erro no sensor
  }
}

void exibirLCD(int dist) {
  lcd.setCursor(0, 0);
  if (dist >= 0) {
    lcd.print("Distancia: ");
    lcd.print(dist);
    lcd.print("cm   ");

    lcd.setCursor(0, 1);
    if (dist > 10) {
      lcd.print("Reabastecer!!!   ");
      digitalWrite(LED_PIN, HIGH);
    } else {
      lcd.print("Nivel Adequado   ");
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("ERRO NO SENSOR!  ");
    lcd.setCursor(0, 1);
    lcd.print("                ");

    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= 500) {
      lastBlinkTime = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }
  }
}

void controlarBomba() {
  if (!manualIrrigation) {  
    int umidade = analogRead(SOIL_SENSOR_PIN);
    if (umidade < 800) {
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}

void piscarLED(int vezes) {
  for (int i = 0; i < vezes; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    piscarLED(3);
    manualIrrigation = true;
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(RELAY_PIN, LOW);
    manualIrrigation = false;
    delay(3000);
  }

  int distance = medirDistancia();
  if (distance >= 0) {
    exibirLCD(distance);
    controlarBomba();
  } else {
    exibirLCD(-1);
  }
  
  delay(1000);
}
