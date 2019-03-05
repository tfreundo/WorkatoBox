# WorkatoBox
WorkatoBox is a minimalistic tool that improves your productivity using the principles of Pomodoro.

## How it works
After the setup is done the LEDs of the connected physical WorkatoBox will light up one after another and then all together for 2 seconds.
Afterwards the WorkatoBox is waiting for user input.

The WorkatoBox is controlled via the WorkatoBoxController.
This application handles the timer logic and controls the LEDs of the WorkatoBox via Serial communication (that means that you need to connect your WorkatoBox to your computer).
You can update your COM-port that should be used for communication between the WorkatoBox and the Controller and define your own shortcuts to use (should be shortcuts that are not used in another application or the system).

## How it's made
Here you can find a description of the physical WorkatoBox.
The PCB layout is pretty simple, you have the microcontroller (MCU), in my case an old ESP8266, where 7 digital IO Pins (D0 to D6) are connected to the respective LED over a resistor in series:
![PCB Design](https://github.com/tfreundo/WorkatoBox/blob/master/images/pcb.jpg)

The box itself is a very cheap plastic box where I drilled some holes for the LEDs on the upper side and some mounting holes for the PCB on the lower side:
![Box Design](https://github.com/tfreundo/WorkatoBox/blob/master/images/box_layout.jpg)

Finally I used hot glue to fix the LEDs in place:
![Box Design](https://github.com/tfreundo/WorkatoBox/blob/master/images/box_interior.jpg)

And from the front the box finally looks like this:
![Box Design](https://github.com/tfreundo/WorkatoBox/blob/master/images/box_exterior.jpg)
Due to the very poor quality of the plastic material I had some issues when drilling the holes in it. Even with very low pressure and a high drilling speed the plastic bursted.

## Conclusion
This was a fun little project and I'm currently using the box for many tasks.
It sometimes really helps me to focus.
It's worth trying if you like to.
