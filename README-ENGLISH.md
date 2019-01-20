![alt text](http://dezatec.es/wp-content/uploads/2019/01/ardu-clima.png)

Arduino based low-cost climate controller

Español: https://github.com/pablo-lp/ardu-clima/blob/master/README.md

# Required components

See in: http://dezatec.es/ardu-clima

# Installation

1 - Add the libraries that are inside "Libraries" to your Arduino software, to avoid errors it is advised to use the included versions that are already tested. Then you can delete this folder.

2 - Open the sketch with our Arduino software

3 - Compile and upload it to your board (Tested only with Arduino Uno)

# How does it work?

The climate controller maintains a constant temperature and humidity (within configurable ranges) by activating 4 outputs, 2 for the temperature and 2 for the humidity. Therefore you can control dehumidification/humidification and heating/ventilation (or AC). It can be configured using the on-screen keyboard or with a remote control.

# How to use it?

To be able to start the climate controller all the indicated components must be correctly connected. The IR remote control is optional.

Connect the power to the module and configure it through the menus.

According to the manufacturer of the LCD or remote control that we buy, the buttons may not work properly.

If the LCD buttons do not respond we must adjust the values of each one in the core.h file inside the read_inputs() method on line 100. We can see the values of the buttons on the serial monitor uncommenting lines 114 and 115 (We have to activate the serial port output by also uncommenting line 37 of the file Ardu_Clima.ino).

To adjust the remote control keys, we will uncomment lines 106 and 107 of the core.h file and configure the values that appear on the serial monitor in the config.h file.

# License

This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

# Disclaimer

The software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and non infringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software.
