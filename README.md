This is a keyboard matrix translation for a Krown keyboard (pulled from a TTY unit) using a Teensy LC.

This assumes that pin 1 (red) on the keyboard ribbon is connected to pin 1 on the teensy, and so on.

DISP is the ESC key
CTRL is a Caps lock.
Left and Right arrow keys are not properly assigned to anything useful

Shift keys work and will capitalize letters and turn numbers into their corresponding symbols (based on your keyboard layout).

The modifiers on the keycaps are not currently set, so a lot of characters can't be typed.  Will need to look into a more sophisticated modifier arrangement.  

This is mainly a proof of concept at this point.
