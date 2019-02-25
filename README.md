# WorkatoBox
WorkatoBox is a minimalistic tool that improves your productivity using the principles of Pomodoro.

## How it works
After the setup is done the LEDs of the connected physical WorkatoBox will light up 5 times, afterwards the WorkatoBox is waiting for user input.

The WorkatoBox is controlled via the WorkatoBoxController.
This application handles the timer logic and controls the LEDs of the WorkatoBox via Serial communication (that means that you need to connect your WorkatoBox to your computer).
You can update your COM-port that should be used for communication between the WorkatoBox and the Controller and define your own shortcuts to use (should be shortcuts that are not used in another application or the system)