#include "everykey/everykey.h"


typedef enum {
    GOTO = 0,        //arg1: LED mask, arg2: target value
    FADE,            //arg1: LED mask, arg2: target value, arg3: speed
    SPARKLE,         //arg1: LED mask
    SETTEXT,         //arg1: row, arg2: text index
    CLEARSCREEN,     //no args
    END,             //no args
    LOOP,            //no args
    TYPESTART,       //no args. Goes to line 1, turns on blinking cursor
    TYPE,            //arg2: char
    TYPEEND          //no args. Turns off blinking cursor
} COMMAND_ID;

typedef struct {
    uint16_t ticks;
    COMMAND_ID command;
    uint16_t arg1;
    uint8_t arg2;
    uint8_t arg3;
} Command;

const Command commands[] = {
    { 0, GOTO, 0b111111111, 0 },
    { 0, CLEARSCREEN, 0, 0, 0 },

    { 128, FADE, 0b000000011, 255, 2 }, //POST /bank fade up
//    {   0, SETTEXT, 0, 0, 0},           
    {   0, TYPESTART, 0, 0, 0 },
    { 200, TYPE, 0, 'P', 0 },
    {  30, TYPE, 0, 'O', 0 },
    {  30, TYPE, 0, 'S', 0 },
    {  30, TYPE, 0, 'T', 0 },
    {  30, TYPE, 0, ' ', 0 },
    {  30, TYPE, 0, '/', 0 },
    {  30, TYPE, 0, 'b', 0 },
    {  30, TYPE, 0, 'a', 0 },
    {  30, TYPE, 0, 'n', 0 },
    {  30, TYPE, 0, 'k', 0 },

    { 200, TYPEEND, 0, 0, 0 },     //blend to Hackathon Roadshow
    {   0, FADE, 0b000000001, 0, 2 },
    { 128, SETTEXT, 0, 1, 0},
    {   0, SETTEXT, 1, 2, 0},
    {   0, FADE, 0b000000001, 255, 2 },

    { 300, FADE, 0b000000011, 0, 2 },   //fade out
    
    { 128, SETTEXT, 0, 3, 0},           //Cologne
    {   0, SETTEXT, 1, 4, 0},
    {   0, FADE, 0b100000011, 255, 5 },
    { 200, FADE, 0b100000011, 0, 1 },

    { 128, SETTEXT, 0, 5, 0},           //Hamburg
    {   0, SETTEXT, 1, 6, 0},
    {   0, FADE, 0b010000011, 255, 5 },
    { 200, FADE, 0b010000011, 0, 1 },

    { 128, SETTEXT, 0, 7, 0},           //Berlin
    {   0, SETTEXT, 1, 8, 0},
    {   0, FADE, 0b001000011, 255, 5 },
    { 200, FADE, 0b001000011, 0, 1 },

    { 128, SETTEXT, 0, 9, 0},           //Munich
    {   0, SETTEXT, 1, 10, 0},
    {   0, FADE, 0b000100011, 255, 5 },
    { 200, FADE, 0b000100011, 0, 1 },

    { 128, SETTEXT, 0, 11, 0},          //Stuttgart
    {   0, SETTEXT, 1, 12, 0},
    {   0, FADE, 0b000010011, 255, 5 },
    { 200, FADE, 0b000010011, 0, 1 },

    { 128, SETTEXT, 0, 13, 0},          //Frankfurt
    {   0, SETTEXT, 1, 14, 0},
    {   0, FADE, 0b000001011, 255, 5 },
    { 200, FADE, 0b000001011, 0, 1 },

    { 128, SETTEXT, 0, 15, 0},          //Bonn
    {   0, SETTEXT, 1, 16, 0},
    {   0, FADE, 0b000000111, 255, 5 },
    { 200, FADE, 0b000000111, 0, 1 },

    { 128, SETTEXT, 0, 17, 0},          //Prize
    {   0, SETTEXT, 1, 18, 0},
    {   0, FADE, 0b000000011, 255, 2 },
    {   0, SPARKLE, 0b111111100, 0, 0 },
    { 200, FADE, 0b000000001, 150, 2},
    { 200, FADE, 0b000000001, 255, 2},
    { 200, FADE, 0b000000001, 150, 2},
    { 200, FADE, 0b000000001, 255, 2},
    { 200, FADE, 0b000000001, 150, 2},
    { 200, FADE, 0b000000001, 255, 2},
    { 200, FADE, 0b000000001, 150, 2},
    { 200, FADE, 0b000000001, 255, 2},
    { 200, FADE, 0b000000001, 150, 2},
    { 200, FADE, 0b000000001, 255, 2},
    { 200, FADE, 0b000000001, 150, 2},
    { 200, FADE, 0b000000001, 255, 2},
    { 200, FADE, 0b000000001, 150, 2},
    { 200, FADE, 0b000000001, 255, 2},
    { 200, FADE, 0b111111111, 0, 2 },

    { 200, LOOP, 0, 0, 0}
};

const char * const strings[] = {
    "POST /bank    ", //0
    "Hackathon     ", //1
    "Roadshow      ", //2
    "K\357ln          ", //3
    "3.-5.6.16     ", //4
    "Hamburg       ", //5
    "21.7.16       ", //6
    "Berlin        ", //7
    "30.9.-2.10.16 ", //8
    "M\365nchen       ", //9
    "20.10.16      ", //10
    "Stuttgart     ", //11
    "25.-27.11.16  ", //12
    "Frankfurt a.M.", //13
    "19.1.17       ", //14
    "Bonn          ", //15
    "17.3.17       ", //16
    "hack.institute", //17
    "sagt DANKE!   "  //18
};

const uint16_t gamma[] = {
    0,66,67,69,71,73,75,77,79,81,84,86,88,91,93,96,
    99,101,104,107,110,113,116,119,122,126,129,133,137,140,144,148,
    152,156,161,165,170,174,179,184,189,194,200,205,211,217,223,229,
    235,242,248,255,262,270,277,285,292,301,309,317,326,335,344,354,
    364,374,384,394,405,417,428,440,452,464,477,490,504,518,532,547,
    562,577,593,609,626,644,661,680,698,718,737,758,779,800,822,845,
    868,892,917,942,968,994,1022,1050,1079,1109,1139,1171,1203,1236,1270,1305,
    1341,1378,1416,1455,1495,1537,1579,1622,1667,1713,1760,1809,1859,1910,1963,2017,
    2072,2130,2188,2249,2311,2374,2440,2507,2576,2647,2720,2795,2872,2951,3033,3116,
    3202,3290,3381,3474,3570,3669,3770,3874,3980,4090,4203,4319,4438,4560,4686,4815,
    4948,5084,5224,5368,5516,5669,5825,5985,6150,6320,6494,6673,6857,7046,7241,7440,
    7645,7856,8073,8295,8524,8759,9000,9249,9504,9766,10035,10311,10596,10888,11188,11496,
    11813,12139,12474,12818,13171,13534,13907,14291,14685,15089,15505,15933,16372,16823,17287,17764,
    18254,18757,19274,19805,20351,20912,21489,22081,22690,23316,23958,24619,25298,25995,26712,27448,
    28205,28983,29782,30603,31446,32313,33204,34119,35060,36027,37020,38040,39089,40167,41274,42412,
    43581,44783,46018,47286,48590,49929,51306,52720,54174,55667,57202,58779,60400,62065,63776,65534
};


#define BUTTON_PORT 0
#define BUTTON_PIN 1

#define CT16B0_RESET_MAT 3
#define CT16B1_RESET_MAT 0
#define CT32B0_RESET_MAT 1
#define CT32B1_RESET_MAT 3

#define TIMER_PRESCALE 0
#define TIMER_PERIOD 65535
#define BIAS_VAL 2000

#define PWM1_PORT 0 //Circuit PWM4 - LED4 - Cologne
#define PWM1_PIN 11
#define PWM1_TIMER CT32B0
#define PWM1_MAT 3

#define PWM2_PORT 1 //Circuit PWM3 - LED5 - Hamburg
#define PWM2_PIN 1
#define PWM2_TIMER CT32B1
#define PWM2_MAT 0

#define PWM3_PORT 1 //Circuit PWM1 - LED6 - Berlin
#define PWM3_PIN 3
#define PWM3_TIMER CT32B1
#define PWM3_MAT 2

#define PWM4_PORT 0 //Circuit PWM8 - LED7 - Munich
#define PWM4_PIN 8
#define PWM4_TIMER CT16B0
#define PWM4_MAT 0

#define PWM5_PORT 0 //Circuit PWM7 - LED1 - Stuttgart
#define PWM5_PIN 9
#define PWM5_TIMER CT16B0
#define PWM5_MAT 1

#define PWM6_PORT 0 //Circuit PWM6 - LED2 - Frankfurt
#define PWM6_PIN 10
#define PWM6_TIMER CT16B0
#define PWM6_MAT 2

#define PWM7_PORT 1 //Circuit PWM5 - LED3 - Bonn
#define PWM7_PIN 10
#define PWM7_TIMER CT16B1
#define PWM7_MAT 1

#define BIASPWM_PORT 1
#define BIASPWM_PIN 6
#define BIASPWM_TIMER CT32B0
#define BIASPWM_MAT 0

#define LCDPWM_PORT 1
#define LCDPWM_PIN 2
#define LCDPWM_TIMER CT32B1
#define LCDPWM_MAT 1

#define LCD_RS_PORT 3
#define LCD_RS_PIN 3

#define LCD_E_PORT 1
#define LCD_E_PIN 7

#define LCD_D4_PORT 1
#define LCD_D4_PIN 5

#define LCD_D5_PORT 1
#define LCD_D5_PIN 4

#define LCD_D6_PORT 2
#define LCD_D6_PIN 3

#define LCD_D7_PORT 3
#define LCD_D7_PIN 1


/*   
 HD44780 write commands:
 
 D7  6  5  4  3  2  1  0
 
 0  0  0  0  0  0  0  1 : Clear display, home cursor
 0  0  0  0  0  0  1  - : Return cursor to home
 0  0  0  0  0  1  ID S : Set cursor move direction. ID=1: Increment cursor after write, S=Shift after write
 0  0  0  0  1  D  C  B : Enable display/cursor. D=1: Display on, C=1: Cursor on, B=1: Blink on
 0  0  0  1  SC RL -  - : Move cursor/shift display: SC=1:Shift display on, RL=1:shift right
 0  0  1  DL N  F  -  - : Set interface: DL=1:8 Bit (4 otherwise), N=1:2 lines (1 otherwise), F=1:5x10 font (5x7 otherwise)
 0  1  A  A  A  A  A  A : Move cursor to CGRAM. A:address
 1  A  A  A  A  A  A  A : Move cursor to display. A:address
 
 */

/** Simple busy wait. Should not be used from outside. Probably waits too long... */
void LCD_Wait_US(uint32_t us) {
    volatile uint32_t i = 30 * us;
    while (i > 0) i--;
}

/** writes one nibble. Should not be used from outside */
void LCD_Write4(bool rs, uint8_t value) {
    every_gpio_write(LCD_RS_PORT, LCD_RS_PIN, rs);
    every_gpio_write(LCD_D7_PORT, LCD_D7_PIN, value & 8);
    every_gpio_write(LCD_D6_PORT, LCD_D6_PIN, value & 4);
    every_gpio_write(LCD_D5_PORT, LCD_D5_PIN, value & 2);
    every_gpio_write(LCD_D4_PORT, LCD_D4_PIN, value & 1);
    
    every_gpio_write(LCD_E_PORT, LCD_E_PIN, true);
    LCD_Wait_US(1);
    
    every_gpio_write(LCD_E_PORT, LCD_E_PIN, false);
    LCD_Wait_US(1);
}

/** writes one byte using a 4 bit interface. Should not be used from outside */
void LCD_Write8(bool rs, uint8_t value) {
    LCD_Write4(rs, (value >> 4) & 0x0f);
    LCD_Write4(rs, value & 0x0f);
    LCD_Wait_US(60);
    if (!rs) LCD_Wait_US(2000);

}

/** writes a string onto screen, starting at the current cursor position. Chars 8-15 are also mapped to custom chars
 so that custom char 0 can be used even though 0 is end of string. */
void LCD_WriteString(const uint8_t* string) {
    int i=0;
    while (true) {
        uint8_t ch = string[i++];
        if (!ch) break;
        if ((ch >= 0x08) && (ch < 0x10)) ch-=8;
        LCD_Write8(true, ch);
    }
}

/** Clears the screen and homes the cursor */
void LCD_ClearScreen() {
    LCD_Write8(false, 0x01);    //clear screen, home cursor
}

/** Moves the cursor to the top left position. In contrast to GotoPosition, shifting is also reset. */
void LCD_Home() {
    LCD_Write8(false, 0x02);    //home cursor, reset shifts
}

/** turns the display and cursor features on or off. Does not modify memory contents. */
void LCD_EnableDisplay(bool screenOn, bool cursorOn, bool blinkOn) {
    LCD_Write8(false, 0x08 | (screenOn ? 0x04 : 0x00) | (cursorOn ? 0x02 : 0x00) | (blinkOn ? 0x01 : 0x00));    //display, cursor, blink on
}

/** sets the cursor to a given position. Note that this does not reflect funny memory maps found in some display configurations. 
 Two row displays should be fine */
void LCD_GotoPosition(uint8_t row, uint8_t col) {
    LCD_Write8(false, 0x80 | (row << 6) | col);
}

/** Defines a custom character (codes 0-7).
 Bitmap should be 8 bytes (rows, pixels right-aligned) even though sometimes only 7 are shown.
 Function will reset cursor position to home. */
void LCD_DefineChar(uint8_t charCode, const uint8_t bitmap[]) {
    LCD_Write8(false, 0x40 | (charCode << 3));
    int i;
    for (i=0; i<8; i++) {
        LCD_Write8(true, bitmap[i]);
    }
    LCD_Home();
}

/** initializes the pins and configures the display to a usable state */
void LCD_Init() {
    EVERY_GPIO_SET_FUNCTION(LCD_RS_PORT, LCD_RS_PIN, PIO, ADMODE_DIGITAL);
    every_gpio_set_dir(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
    every_gpio_write(LCD_RS_PORT, LCD_RS_PIN, 0);  //RS: 0 = command, 1 = data

    EVERY_GPIO_SET_FUNCTION(LCD_E_PORT, LCD_E_PIN, PIO, ADMODE_DIGITAL);
    every_gpio_set_dir(LCD_E_PORT, LCD_E_PIN, OUTPUT);
    every_gpio_write(LCD_E_PORT, LCD_E_PIN, 0);  //E: falling edge triggers transfer

    EVERY_GPIO_SET_FUNCTION(LCD_D4_PORT, LCD_D4_PIN, PIO, IOCON_IO_ADMODE_DIGITAL);
    every_gpio_set_dir(LCD_D4_PORT, LCD_D4_PIN, OUTPUT);
    every_gpio_write(LCD_D4_PORT, LCD_D4_PIN, 0);

    EVERY_GPIO_SET_FUNCTION(LCD_D5_PORT, LCD_D5_PIN, PIO, IOCON_IO_ADMODE_DIGITAL);
    every_gpio_set_dir(LCD_D5_PORT, LCD_D5_PIN, OUTPUT);
    every_gpio_write(LCD_D5_PORT, LCD_D5_PIN, 0);

    EVERY_GPIO_SET_FUNCTION(LCD_D6_PORT, LCD_D6_PIN, PIO, IOCON_IO_ADMODE_DIGITAL);
    every_gpio_set_dir(LCD_D6_PORT, LCD_D6_PIN, OUTPUT);
    every_gpio_write(LCD_D6_PORT, LCD_D6_PIN, 0);

    EVERY_GPIO_SET_FUNCTION(LCD_D7_PORT, LCD_D7_PIN, PIO, IOCON_IO_ADMODE_DIGITAL);
    every_gpio_set_dir(LCD_D7_PORT, LCD_D7_PIN, OUTPUT);
    every_gpio_write(LCD_D7_PORT, LCD_D7_PIN, 0);

    LCD_Wait_US(40000);
    
    LCD_Write4(false, 0x02);
    LCD_Wait_US(5000);

    LCD_Write8(false, 0x28);    //function set: 4 bit, 2 lines, 5x7 font
    LCD_Write8(false, 0x06);    //entry mode: Move cursor
    LCD_EnableDisplay(true, false, false);
    LCD_ClearScreen();
}

uint16_t timerValues[9];    //LED1-7, LCD BG, LCD BIAS

void PWM_UpdateValues() {
    Timer_SetMatchValue(PWM1_TIMER, PWM1_MAT, timerValues[0]);
    Timer_SetMatchValue(PWM2_TIMER, PWM2_MAT, timerValues[1]);
    Timer_SetMatchValue(PWM3_TIMER, PWM3_MAT, timerValues[2]);
    Timer_SetMatchValue(PWM4_TIMER, PWM4_MAT, timerValues[3]);
    Timer_SetMatchValue(PWM5_TIMER, PWM5_MAT, timerValues[4]);
    Timer_SetMatchValue(PWM6_TIMER, PWM6_MAT, timerValues[5]);
    Timer_SetMatchValue(PWM7_TIMER, PWM7_MAT, timerValues[6]);
    Timer_SetMatchValue(LCDPWM_TIMER, LCDPWM_MAT, timerValues[7]);
    Timer_SetMatchValue(BIASPWM_TIMER, BIASPWM_MAT, timerValues[8]);
}

void PWM_Init() {
    Timer_Enable(CT16B0, true);
    Timer_Enable(CT16B1, true);
    Timer_Enable(CT32B0, true);
    Timer_Enable(CT32B1, true);
    Timer_SetPrescale(CT16B0, TIMER_PRESCALE);
    Timer_SetPrescale(CT16B1, TIMER_PRESCALE);
    Timer_SetPrescale(CT32B0, TIMER_PRESCALE);
    Timer_SetPrescale(CT32B1, TIMER_PRESCALE);
    Timer_SetMatchValue(CT16B0, CT16B0_RESET_MAT, TIMER_PERIOD);
    Timer_SetMatchValue(CT16B1, CT16B1_RESET_MAT, TIMER_PERIOD);
    Timer_SetMatchValue(CT32B0, CT32B0_RESET_MAT, TIMER_PERIOD);
    Timer_SetMatchValue(CT32B1, CT32B1_RESET_MAT, TIMER_PERIOD);
    Timer_SetMatchBehaviour(CT16B0, CT16B0_RESET_MAT, TIMER_MATCH_RESET);
    Timer_SetMatchBehaviour(CT16B1, CT16B1_RESET_MAT, TIMER_MATCH_RESET);
    Timer_SetMatchBehaviour(CT32B0, CT32B0_RESET_MAT, TIMER_MATCH_RESET);
    Timer_SetMatchBehaviour(CT32B1, CT32B1_RESET_MAT, TIMER_MATCH_RESET);

    Timer_EnablePWM(PWM1_TIMER, PWM1_MAT, true);
    Timer_EnablePWM(PWM2_TIMER, PWM2_MAT, true);
    Timer_EnablePWM(PWM3_TIMER, PWM3_MAT, true);
    Timer_EnablePWM(PWM4_TIMER, PWM4_MAT, true);
    Timer_EnablePWM(PWM5_TIMER, PWM5_MAT, true);
    Timer_EnablePWM(PWM6_TIMER, PWM6_MAT, true);
    Timer_EnablePWM(PWM7_TIMER, PWM7_MAT, true);
    Timer_EnablePWM(LCDPWM_TIMER, LCDPWM_MAT, true);
    Timer_EnablePWM(BIASPWM_TIMER, BIASPWM_MAT, true);

    EVERY_GPIO_SET_FUNCTION(PWM1_PORT, PWM1_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(PWM2_PORT, PWM2_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(PWM3_PORT, PWM3_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(PWM4_PORT, PWM4_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(PWM5_PORT, PWM5_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(PWM6_PORT, PWM6_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(PWM7_PORT, PWM7_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(LCDPWM_PORT, LCDPWM_PIN, TMR, ADMODE_DIGITAL);
    EVERY_GPIO_SET_FUNCTION(BIASPWM_PORT, BIASPWM_PIN, TMR, ADMODE_DIGITAL);

    for (int i=0; i<8; i++) {
        timerValues[i] = 65535;
    }
    timerValues[8] = BIAS_VAL;
    PWM_UpdateValues();

    Timer_Reset(CT16B0);
    Timer_Reset(CT16B1);
    Timer_Reset(CT32B0);
    Timer_Reset(CT32B1);
    Timer_Start(CT16B0);
    Timer_Start(CT16B1);
    Timer_Start(CT32B0);
    Timer_Start(CT32B1);
}

void main(void) {

    EVERY_GPIO_SET_FUNCTION(BUTTON_PORT, BUTTON_PIN, PIO, ADMODE_DIGITAL);
    every_gpio_set_dir(BUTTON_PORT, BUTTON_PIN, INPUT);
    EVERY_GPIO_SET_PULL(BUTTON_PORT,BUTTON_PIN, PULL_UP);

    PWM_Init();
    LCD_Init();
    
    const uint8_t char0[] = {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
    const uint8_t char1[] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};
    const uint8_t char2[] = {0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c};
    const uint8_t char3[] = {0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e};
    const uint8_t char4[] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
    LCD_DefineChar(0,char0);
    LCD_DefineChar(1,char1);
    LCD_DefineChar(2,char2);
    LCD_DefineChar(3,char3);
    LCD_DefineChar(4,char4);

    SYSCON_StartSystick_10ms();
}

uint32_t ticks = 0;
uint32_t totalTicks = 0;
uint32_t commandIdx = 0;
bool running = true;
uint8_t ledValue[9];
uint8_t ledTarget[9];
uint8_t ledSpeed[9];    //ff = sparkle

void parseCommand() {
    if (!running) { //not running: check start condition
        if (!every_gpio_read(BUTTON_PORT, BUTTON_PIN)) {
            ticks = 0;
            commandIdx = 0;
            running = true;
        } else {
            return;
        }
    }
    ticks++;
    totalTicks++;
    uint16_t nextTick = commands[commandIdx].ticks;
    while (ticks >= nextTick) {
        COMMAND_ID cmd = commands[commandIdx].command;
        uint16_t arg1 = commands[commandIdx].arg1;
        uint8_t arg2 = commands[commandIdx].arg2;
        uint8_t arg3 = commands[commandIdx].arg3;
        switch (cmd) {
            case GOTO:
                for (int i=0; i<9; i++) {
                    if (arg1 & (0x100 >> i)) {
                        ledValue[i] = arg2;
                        ledTarget[i] = arg2;
                        ledSpeed[i] = 0;
                    }
                }
                break;
            case FADE:
                for (int i=0; i<9; i++) {
                    if (arg1 & (0x100 >> i)) {
                        ledTarget[i] = arg2;
                        ledSpeed[i] = arg3;
                    }
                }
                break;
            case SPARKLE:
                for (int i=0; i<9; i++) {
                    if (arg1 & (0x100 >> i)) {
                        ledSpeed[i] = 0xff;
                    }
                }
                break;
            case SETTEXT:
                LCD_GotoPosition(arg1,1);
                LCD_WriteString(strings[arg2]);
                break;
            case CLEARSCREEN:
                LCD_ClearScreen();
                break;
            case END:
                running = false;
                break;
            case LOOP:
                commandIdx = 0;
                ticks = 0;
                return;
                break;
            case TYPESTART:
                LCD_EnableDisplay(true, true, true);
                LCD_GotoPosition(0,1);
                break;
            case TYPE:
                LCD_Write8(true, arg2);
                break;
            case TYPEEND:
                LCD_EnableDisplay(true, false, false);
                break;

        }   
        commandIdx++;
        ticks = 0;
        if (!running) break;
        nextTick = commands[commandIdx].ticks;
    }
}

void animateLEDs() {
    for (int i=0; i<9; i++) {
        uint8_t speed = ledSpeed[i];
        if (speed == 0xff) {                      //sparkle
            uint8_t val = 255 - 2 * (totalTicks & 0x7f); //ramp down
            val += 36*i;  //shift LEDs
            ledValue[i] = val;
        } else if (ledTarget[i] > ledValue[i]) {  //fade up
            uint8_t delta = ledTarget[i] - ledValue[i];
            if (speed <= delta) {
                delta = speed;
            }
            ledValue[i] += delta;
        } else if (ledTarget[i] < ledValue[i]) {  //fade down
            uint8_t delta = ledValue[i] - ledTarget[i];
            if (speed <= delta) {
                delta = speed;
            }
            ledValue[i] -= delta;
        }
    }
    for (int i=0; i<8; i++) {
        timerValues[i] = 65534 - gamma[ledValue[i]];
    }
    timerValues[8] = 8 * ledValue[8];
    PWM_UpdateValues();
}

void systick() {
    parseCommand();
    animateLEDs();


    // static uint32_t counter;
    // counter++;
    // uint32_t phase = counter & 0x7f;
    // uint32_t stage = counter >> 7;

    //     for (int i=0; i<8; i++) {
    //         timerValues[i] = (counter << 8) + 8192 * i;
    //     }
    //     PWM_UpdateValues();

    // if (phase == 0) {
    //     LCD_Home();
    //     LCD_WriteString("Hello");
    //     LCD_GotoPosition(1,0);
    //     LCD_WriteString("World");
    // }       
}
