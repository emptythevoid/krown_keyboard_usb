/*
 * Krown keyboard interpreter
 * 
 * Converts signals from a Krown keyboard's key matrix to a stndard USB keyboard when using a Teensy LC.
 * 
 * DISP is the Escape key
 * CTRL is Caps Lock
 * Left and right arrow keys are not properly assigned
 * Shift works to capitalize and convert numbers to their normal symbols
 * The secondary key legends are not working yet.
 * This means no equals, plus, tilde, accent, tab, del, window, dash, slash, colon, quote, apostrophe, underscore, brackets or curley braces, question mark, backslash, arrow keys
 */

#include <Keypad.h>

const byte ROWS = 9; //eight rows
const byte COLS = 8; //eight columns

#ifdef M
#undef M
#endif
#define M(n) ((n) & KEYCODE_MASK)

char keys[ROWS][COLS] = {
  {M(KEY_SLASH),M(KEY_M),M(KEY_P),M(KEY_SLASH),M(KEY_SLASH),M(KEY_COMMA),M(KEY_SLASH),M(KEY_ENTER)},
  {M(KEY_F),M(KEY_U),M(KEY_T),M(KEY_SLASH),M(KEY_SLASH),M(KEY_I),M(KEY_S),M(KEY_ESC)},
  {M(KEY_G),M(KEY_SLASH),M(KEY_Y),M(KEY_A),M(KEY_SLASH),M(KEY_L),M(KEY_D),M(KEY_SLASH)},
  {M(KEY_B),M(KEY_N),M(KEY_H),M(KEY_Z),M(KEY_4),M(KEY_PERIOD),M(KEY_C),M(KEY_BACKSPACE)},
  {M(KEY_SPACE),M(KEY_K),M(KEY_J),M(KEY_X),M(KEY_SLASH),M(KEY_O),M(KEY_V),M(KEY_0)},
  {M(KEY_E),M(KEY_6),M(KEY_R),M(KEY_Q),M(KEY_6),M(KEY_O),M(KEY_W),M(KEY_6)},
  {M(KEY_3),M(KEY_5),M(KEY_4),M(KEY_1),M(KEY_CAPS_LOCK),M(KEY_7),M(KEY_2),M(KEY_7)},
  {M(KEY_SLASH),M(KEY_SLASH),M(KEY_4),M(KEY_1),M(KEY_TILDE),M(KEY_8),M(KEY_2),M(KEY_8)},
  {M(KEY_TILDE),M(KEY_7),M(KEY_TILDE),M(KEY_TILDE),M(MODIFIERKEY_SHIFT),M(KEY_8),M(KEY_TILDE),M(KEY_9)},
};
byte rowPins[ROWS] = {1,2,3,4,6,7,8,9,17}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,11,12,13,14,15,16,5}; //connect to the column pinouts of the keypad

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;
int x = 0;

void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {
    loopCount++;
    //char key = kpd.getKey();
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }
    
    
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";

                    
                    
                    Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);
                // release all the keys at the same instant
                 Keyboard.set_key1(kpd.key[i].kchar);
                Keyboard.send_now();
               
                //Keyboard.set_key1(0);
                //Keyboard.send_now();
                if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
                  Serial.print("Shift ");
                  Keyboard.set_modifier(MODIFIERKEY_SHIFT);
                  Keyboard.send_now();
                  x=1;
             
        }
        
                break;
                 
                    case HOLD:
                    msg = " HOLD.";
                    //Keyboard.set_modifier(MODIFIERKEY_SHIFT);
                    //Keyboard.send_now();
                    
                    Keyboard.set_key1(kpd.key[i].kchar);
                Keyboard.send_now();
                    
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                    Serial.println(msg);
                    Keyboard.set_key1(0);
                Keyboard.send_now();
                if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
                  Serial.print("Shift Released ");
                  Keyboard.set_modifier(0);
                  Keyboard.send_now();
                  x=0;
                }
               
                break;
                    case IDLE:
                    msg = " IDLE.";
                    
                }
                
            }
        }
    }
}  // End ffffSsSssSssSdddDdddDddDdDdddDdDdddDddDddC
