#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"

typedef enum {Pressed, Released} buttons; //FSM for button

int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    unsigned char buttonhistory = UNPRESSED;

    // TODO: Declare the variables that main uses to interact with your state machine.
   // static colors instcolor = off;

    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER0, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER1, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        if(timer0Expired())
        {
            count0++;
        }

        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        if(timer1Expired())
        {
            buttonhistory = checkStatus_BoosterpackS1();

        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        if (fsmBoosterpackButtonS1(buttonhistory))
        // TODO: If a completed, debounced button press has occurred, increment count1.
        count1++;
        }
    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
        switch (count % 8 ) //Since there are 8 cases the count had to be modulus with 8
        {
        case 0:
            turnOff_LaunchpadLED2Blue();
            turnOff_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Red();
            break;
        case 1:
            turnOff_LaunchpadLED2Blue();
            turnOff_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Red();
            break;
        case 2:
            turnOff_LaunchpadLED2Blue();
            turnOn_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Red();
            break;
        case 3:
            turnOff_LaunchpadLED2Blue();
            turnOn_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Red();
            break;
        case 4:
            turnOn_LaunchpadLED2Blue();
            turnOff_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Red();
            break;
        case 5:
            turnOn_LaunchpadLED2Blue();
            turnOff_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Red();
            break;
        case 6:
            turnOn_LaunchpadLED2Blue();
            turnOn_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Red();
            break;
        case 7:
            turnOn_LaunchpadLED2Blue();
            turnOn_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Red();
            break;
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    switch (count % 8)
    {
    case 0:
        turnOff_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDRed();
        break;
    case 1:
        turnOff_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDRed();
        break;
    case 2:
        turnOff_BoosterpackLEDBlue();
        turnOn_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDRed();
        break;
    case 3:
        turnOff_BoosterpackLEDBlue();
        turnOn_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDRed();
        break;
    case 4:
        turnOn_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDRed();
        break;
    case 5:
        turnOn_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDRed();
        break;
    case 6:
        turnOn_BoosterpackLEDBlue();
        turnOn_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDRed();
        break;
    case 7:
        turnOn_BoosterpackLEDBlue();
        turnOn_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDRed();
        break;
    }
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned char buttonhistory)
{
    char Curr_status;
    static char Prev_Status = UNPRESSED;

    static buttons state = Released;
    bool pressed = false;

    //Fist input of FSM
    char firstbuttonvalue = checkStatus_BoosterpackS1();

    //Output of FSM
    bool debouncedstatus;
    switch (state) //Switch case when the button is pressed and not pressed
    {
        case Pressed:
            debouncedstatus = PRESSED;
            if (buttonhistory == UNPRESSED)
                state = Released;
            break;
        case Released:
            debouncedstatus = UNPRESSED;
            if (buttonhistory == PRESSED)
                state = Pressed;
            break;
    }
    Curr_status = debouncedstatus;
    if ((Prev_Status == UNPRESSED) && (Curr_status == PRESSED)) //Resulting Output
        pressed = true;
        Prev_Status = Curr_status;
       return pressed;
}
