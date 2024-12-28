byte loc, inv, hp = 3, enemy = 2, gold = 0;
char cmd;
bool trap_active = true;

const char s0[] PROGMEM = "╔═══════[ ТЕМНИЙ ЛІС ]═══════╗";
const char s1[] PROGMEM = "║  Пригоди чекають на тебе   ║";
const char s2[] PROGMEM = "╚════════════════════════════╝";
const char s3[] PROGMEM = "❤ ";
const char s4[] PROGMEM = "✧";
const char s5[] PROGMEM = "⚿";
const char s6[] PROGMEM = "❐";
const char s7[] PROGMEM = "⚔";
const char s8[] PROGMEM = "⌘";
const char s9[] PROGMEM = "⌂";
const char s10[] PROGMEM = "☗";
const char s11[] PROGMEM = "≈";
const char s12[] PROGMEM = "⛰";
const char s13[] PROGMEM = "♠";
const char s16[] PROGMEM = "✦ Знайдено ліхтар!";
const char s17[] PROGMEM = "✦ Знайдено ключ!";
const char s18[] PROGMEM = "⚠ Темрява поглинає тебе! -1❤";
const char s19[] PROGMEM = "✦ Знайдено древній меч!";
const char s20[] PROGMEM = "☺ Велика рибина! +1❤";
const char s21[] PROGMEM = "☹ Риба зірвалась...";
const char s22[] PROGMEM = "✦ Знайдено магічну карту!";
const char s23[] PROGMEM = "★ Могутнього дракона подолано!";
const char s24[] PROGMEM = "⚡ ПЕРЕМОГА! Легендарний скарб твій!";
const char s25[] PROGMEM = "⚠ Замок вимагає ключ!";
const char s26[] PROGMEM = "⚔ Вдалий удар! Дракон ослаб";
const char s27[] PROGMEM = "⚠ Полум'я дракона! -1❤";
const char s28[] PROGMEM = "✧ Легенда завершена ✧";
const char s29[] PROGMEM = "$";
const char s30[] PROGMEM = "⚠ Древня пастка! -1❤";
const char s31[] PROGMEM = "☘ Цілющий гриб!";
const char s32[] PROGMEM = "⚡ Дика блискавка! -2❤";
const char s33[] PROGMEM = "✦ Жменя золота (+5)!";
const char s34[] PROGMEM = "↺ Відпочити (2$)";
const char s35[] PROGMEM = "♨ Сили відновлено +1❤";
const char s36[] PROGMEM = "☹ Бракує золота";
const char s37[] PROGMEM = "════════════════════";

void printP(const char* str) {
  char c;
  while((c = pgm_read_byte(str++))) {
    Serial.print(c);
    delay(50);
  }
}

void printlnP(const char* str) {
  printP(str);
  Serial.println();
}

void printBar() {
  printlnP(s37);
}

void setup() {
  Serial.begin(1200);
  randomSeed(analogRead(0));
  intro();
}

void intro() {
  printlnP(s0);
  printlnP(s1);
  printlnP(s2);
  showStatus();
  Serial.print(F("\n["));
  printP(s8);
  Serial.println(F("] - Розпочати легенду"));
}

void loop() {
  if (Serial.available()) {
    cmd = Serial.read();
    
    switch(loc) {
      case 0:
        if(cmd == 's') {
          loc = 1;
          showLocation();
        }
        break;
        
      case 1:
        switch(cmd) {
          case '1': loc = 2; break;
          case '2': loc = 3; break;
          case '3': loc = 4; break;
          case '4': loc = 5; break;
        }
        if(random(5) == 0 && loc != 1) {
          hp-=2;
          showStatus();
          printlnP(s32);
          if(hp <= 0) gameOver();
        }
        showLocation();
        break;
        
      case 2:
        switch(cmd) {
          case '1':
            if(!(inv & 1)) {
              printlnP(s16);
              inv |= 1;
            }
            else if(!(inv & 2)) {
              printlnP(s17);
              inv |= 2;
            }
            else if(random(3) == 0) {
              printlnP(s33);
              gold += 5;
              showStatus();
            }
            if(trap_active && random(3) == 0) {
              hp--;
              showStatus();
              printlnP(s30);
              trap_active = false;
              if(hp <= 0) gameOver();
            }
            Serial.print(F("[1] Шукати далі   [2] Вийти"));
            if(gold >= 2) {
              Serial.print(F("   [3] "));
              printlnP(s34);
            }
            Serial.println();
            break;
            
          case '2':
            loc = 1;
            showLocation();
            break;
            
          case '3':
            if(gold >= 2) {
              gold -= 2;
              hp++;
              showStatus();
              printlnP(s35);
            } else {
              printlnP(s36);
            }
            break;
        }
        break;
        
      case 3:
        switch(cmd) {
          case '1':
            if(!(inv & 1)) {
              hp--;
              showStatus();
              printlnP(s18);
              if(hp <= 0) gameOver();
            } 
            else if(!(inv & 8)) {
              printlnP(s19);
              inv |= 8;
            }
            else if(random(3) == 0) {
              printlnP(s31);
              hp++;
              showStatus();
            }
            Serial.println(F("[1] Глибше   [2] Назад"));
            break;
            
          case '2':
            loc = 1;
            showLocation();
            break;
        }
        break;
        
      case 4:
        switch(cmd) {
          case '1':
            if(random(2)) {
              hp++;
              showStatus();
              printlnP(s20);
              if(random(3) == 0) {
                gold += 2;
                showStatus();
                printlnP(s33);
              }
            } else {
              printlnP(s21);
            }
            Serial.println(F("[1] Ще ловити   [2] До лісу"));
            break;
            
          case '2':
            loc = 1;
            showLocation();
            break;
        }
        break;
        
      case 5:
        switch(cmd) {
          case '1':
            if(!(inv & 4)) {
              printlnP(s22);
              inv |= 4;
            }
            else if(enemy > 0) {
              if(inv & 8) {
                if(random(4) > 0) {
                  enemy--;
                  if(enemy == 0) {
                    printlnP(s23);
                    if(inv & 2) {
                      printlnP(s24);
                      gold += 20;
                      showStatus();
                      gameOver();
                    } else {
                      printlnP(s25);
                    }
                  } else {
                    printlnP(s26);
                  }
                } else {
                  printlnP(s21);
                }
              } else {
                hp--;
                showStatus();
                printlnP(s27);
                if(hp <= 0) gameOver();
              }
            }
            Serial.println(F("[1] Вперед   [2] Назад"));
            break;
            
          case '2':
            loc = 1;
            showLocation();
            break;
        }
        break;
    }
    
    while(Serial.available()) Serial.read();
  }
}

void showLocation() {
  showStatus();
  printBar();
  
  switch(loc) {
    case 1:
      printP(s13);
      Serial.println(F(" Темний ліс"));
      printBar();
      Serial.println(F("[1] До хатини"));
      Serial.println(F("[2] До печери"));
      Serial.println(F("[3] До річки"));
      Serial.println(F("[4] До гір"));
      break;
      
    case 2:
      printP(s9);
      Serial.println(F(" Стара хатина"));
      printBar();
      Serial.print(F("[1] Шукати далі   [2] Вийти"));
      if(gold >= 2) {
        Serial.print(F("   [3] "));
        printlnP(s34);
      }
      Serial.println();
      break;
      
    case 3:
      printP(s10);
      Serial.println(F(" Темна печера"));
      printBar();
      Serial.println(F("[1] Глибше   [2] Назад"));
      break;
      
    case 4:
      printP(s11);
      Serial.println(F(" Гірська річка"));
      printBar();
      Serial.println(F("[1] Ловити рибу   [2] Назад"));
      break;
      
    case 5:
      printP(s12);
      Serial.println(F(" Драконячі гори"));
      printBar();
      Serial.println(F("[1] Вгору   [2] Назад"));
      break;
  }
  printBar();
}

void showStatus() {
  Serial.print(F("\n"));
  printP(s3);
  Serial.print(hp);
  Serial.print(F("   "));
  printP(s29);
  Serial.println(gold);
  
  Serial.print(F("Спорядження: "));
  if(inv & 1) { printP(s4); Serial.print(F(" ")); }
  if(inv & 2) { printP(s5); Serial.print(F(" ")); }
  if(inv & 4) { printP(s6); Serial.print(F(" ")); }
  if(inv & 8) { printP(s7); Serial.print(F(" ")); }
  Serial.println();
}

void gameOver() {
  loc = 0;
  inv = 0;
  hp = 3;
  enemy = 2;
  gold = 0;
  trap_active = true;
  Serial.println();
  printlnP(s28);
  Serial.print(F("["));
  printP(s8);
  Serial.println(F("] - Нова легенда"));
}
