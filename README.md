# Homecockpit_v1
First home cockpit build



# Ressources

## MCP23S17

## Led dimming

http://joost.damad.be/2012/09/dimming-12v-led-strip-with-mosfet-and.html

https://www.opensourcepartners.nl/~costar/leddimmer/

https://fr.aliexpress.com/i/4000133382112.html?gatewayAdapt=glo2fra

https://www.analog.com/media/en/technical-documentation/data-sheets/3761af.pdf

https://www.renesas.com/en/products/power-management/solid-state-lighting/solid-state-lighting-interface-ics/iw338-led-driver-secondary-side-pwm-signal-generator#overview

https://electronics.stackexchange.com/questions/79373/how-to-choose-right-pwm-frequency-for-led

https://www.nxp.com/docs/en/data-sheet/MC34844.pdf


### LP5012

https://www.ti.com/lit/ds/symlink/lp5012.pdf?ts=1727775113813

https://e2e.ti.com/support/power-management-group/power-management/f/power-management-forum/840785/lp5012-shorting-two-individual-channels-of-a-driver


### TLC 5947

- Dispose d'un internal oscillator et de 24 channels sur lesquels on peut mettre plusieurs led --> Très pertinent
- Pilotage par connexion série, nécessite uniquement 4 fils. Daisy chaining possible

- Prefered choice to date


https://www.mouser.fr/ProductDetail/Texas-Instruments/TLC5947DAP?qs=Vj8prLbzEFCmhzUYgG9r%252BQ%3D%3D

chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://www.ti.com/lit/ds/symlink/tlc5947.pdf?ts=1727829082976

Library arduino : https://github.com/RobTillaart/TLC5947