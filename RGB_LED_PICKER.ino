/*
To Do:
add second Color DONE
add blink rate picker DONE
Can i make fade an option? Or is strobe good enough?


Notes:
Math must b 'x = x - y;' not 'x - y;'

Instructions;

If you want one color on permenantly choose the first color then brightness, choose any second color/brightness 
and then only press the button briefly when selecting flashing setting.
WILL THIS FLASH BETWEEN THE TWO OF STAY AT THE FIRST COLOR?
*/


int RGB[] = {255,255,255};
int storedRGB[2][3] = {{255,255,255},{255,255,255}};
int pins[] = {3,10,5};

int colors [8][3] {{0,255,255},{0,0,255},{255,0,255},{255,0,0},{255,255,0},{0,255,0},{0,0,0},{255,255,255}};
//red = 0
//yellow = 1
//green = 2
//cyan = 3
//blue = 4
//purple = 5
//white = 6
//off = 7;

int btn = 11;
bool colorSet0 = false;
bool colorSet1 = false;
bool brightSet0 = false;
bool brightSet1 = false;
bool flashSet = false;
bool lit = true;

//for hiding choose flash dialogue, remove for final version.
bool ask = false;

unsigned long pMillis = 0;
unsigned long pMillis1 = 0;

int interval = 1000;

//The starting value when changing the flashing setting.
int flashInt = 0;


void setup() {
  // put your setup code here, to run once:
pinMode(pins[0],OUTPUT);
pinMode(pins[1],OUTPUT);
pinMode(pins[2],OUTPUT);

pinMode(btn,INPUT);

Serial.begin(9600);

setLED();
}


void loop() {
  // put your main code here, to run repeatedly:

  if(colorSet0 && brightSet0 && colorSet1 && brightSet1 && flashSet && flashInt > 5){
    if(millis() - pMillis >= flashInt){
//      Serial.print("NOW FLASHING");
//      Serial.print("\n");
//      Serial.print(flashInt);
//      Serial.print("\n");
      lit = !lit;
      pMillis = millis();
    }
    if(lit){
      setRGB(storedRGB[0][0],storedRGB[0][1],storedRGB[0][2]);
    }
    else if(!lit){
      setRGB(storedRGB[1][0],storedRGB[1][1],storedRGB[1][2]);
    }
  }
  else if(colorSet0 && brightSet0 && colorSet1 && brightSet1 && flashSet && flashInt == 5){
    Serial.print("NOW STATIC");
    Serial.print("\n");
    setRGB(storedRGB[0][0],storedRGB[0][1],storedRGB[0][2]);
  }

  if(digitalRead(btn) == LOW && !colorSet0 && !colorSet1 && !brightSet0){
    Serial.print("CHOOSE COLOR 1");
    Serial.print("\n");
    for(int c = 0; c <=7;){   
      if(pMillis + interval < millis()){
        if(digitalRead(btn) == HIGH){
          storeRGB(0,RGB[0],RGB[1],RGB[2]);
          colorSet0 = true;
          Serial.print("COLOR 1 CHOSEN");
          Serial.print("\n");
          setRGB(colors[7][0],colors[7][1],colors[7][2]);
          break;
        }
        setRGB(colors[c][0],colors[c][1],colors[c][2]);
        c++;
        pMillis = millis();
      }
    }
  }

    if(digitalRead(btn) == LOW && colorSet0 && !colorSet1 && brightSet0){
    Serial.print("CHOOSE COLOR 2");
    Serial.print("\n");
    for(int c = 0; c <=7;){   
      if(pMillis + interval < millis()){
        if(digitalRead(btn) == HIGH){
          storeRGB(1,RGB[0],RGB[1],RGB[2]);
          colorSet1 = true;
          Serial.print("COLOR 2 CHOSEN");
          Serial.print("\n");
          setRGB(colors[7][0],colors[7][1],colors[7][2]);
          break;
        }
        setRGB(colors[c][0],colors[c][1],colors[c][2]);
        c++;
        pMillis = millis();
      }
    }
  }


  if(digitalRead(btn) == LOW && colorSet0 && !brightSet0){
    Serial.print("CHOOSE BRIGHTNESS 1");
    Serial.print("\n");
    for(float b = 0; b < 255 ;){
      if(pMillis + (interval/100) < millis()){
        if(digitalRead(btn) == HIGH){
          Serial.print("BRIGHTNESS 1 CHOSEN");
          Serial.print("\n");
          brightSet0 = true;
          setRGB(colors[7][0],colors[7][1],colors[7][2]);
          break;
        }
        if(storedRGB[0][0]<255){
           storedRGB[0][0] = storedRGB[0][0] + 1;
        }
        if(storedRGB[0][1]<255){
           storedRGB[0][1] = storedRGB[0][1] + 1;
        }
        if(storedRGB[0][2]<255){
           storedRGB[0][2] = storedRGB[0][2] + 1;
        }
        b++;
        setRGB(storedRGB[0][0],storedRGB[0][1],storedRGB[0][2]);
        pMillis = millis();
      }
    }

  }

    if(digitalRead(btn) == LOW && colorSet0 && colorSet1 && brightSet0 && !brightSet1){
    Serial.print("CHOOSE BRIGHTNESS 2");
    Serial.print("\n");
    for(float b = 0; b < 255 ;){
      if(pMillis + (interval/100) < millis()){
        if(digitalRead(btn) == HIGH){
          Serial.print("BRIGHTNESS 2 CHOSEN");
          Serial.print("\n");
          brightSet1 = true;
          setRGB(colors[7][0],colors[7][1],colors[7][2]);
          break;
        }
        if(storedRGB[1][0]<255){
           storedRGB[1][0] = storedRGB[1][0] + 1;
        }
        if(storedRGB[1][1]<255){
           storedRGB[1][1] = storedRGB[1][1] + 1;
        }
        if(storedRGB[1][2]<255){
           storedRGB[1][2] = storedRGB[1][2] + 1;
        }
        b++;
        setRGB(storedRGB[1][0],storedRGB[1][1],storedRGB[1][2]);
        pMillis = millis();
      }
    }

  }


    if(digitalRead(btn) == LOW && colorSet0 && colorSet1 && brightSet0 && brightSet1 && !flashSet){
      
      if(!ask){
        Serial.print("CHOOSE FLASH SPEED");
        Serial.print("\n");
        ask = true;
      }
      pMillis = millis();
      while(millis() - pMillis <= 1500){
        if(digitalRead(btn) == HIGH){
          Serial.print("FLASH SPEED SET");
          Serial.print("\n");
          Serial.print(flashInt);
          Serial.print("\n");
          flashSet = true;
          break;
        }
        if(interval == 10){
          Serial.print("FLASH SPEED SET");
          Serial.print("\n");
          Serial.print(flashInt);
          Serial.print("\n");
          flashSet = true;
          break;
        }


        if(millis() - pMillis1 >= flashInt){
          lit = !lit;
          pMillis1 = millis();
          }
        if(lit){
          setRGB(storedRGB[0][0],storedRGB[0][1],storedRGB[0][2]);
        }
        else if(!lit){
          setRGB(storedRGB[1][0],storedRGB[1][1],storedRGB[1][2]);
        }
        
      }
      flashInt = flashInt + 5;
    }
}

//Write the RGB levels to the relevant pins set in the variables
void setLED(){
  for(int i = 0; i<3; i++){
    analogWrite(pins[i], RGB[i]);
  }
}

//the working RGB values. takes in 3 ints, stores them in a RGB array and passes it on to be analogWrite'ed
void setRGB(int r,int g,int b){
  RGB[0] = r;
  RGB[1] = g;
  RGB[2] = b;
  setLED();
}

//used to store the final used values for the RGB. Read Only by the end
void storeRGB(int x, int r,int g,int b){
  storedRGB[x][0] = r;
  storedRGB[x][1] = g;
  storedRGB[x][2] = b;
}

