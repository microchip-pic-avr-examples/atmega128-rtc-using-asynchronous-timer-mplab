<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Real Time Clock (RTC) Using the Asynchronous Timer

This repository describes how to implement a real time counter (RTC) on AVR microcontrollers that features the RTC module. The implementation requires only one discrete component – a 32.768 kHz watch crystal. The application has very low power consumption because the microcontroller operates in Power-save mode most of the time. In Power-save mode the AVR controller is sleeping with only a timer running. The Timer is clocked by the external crystal. On every Timer overflow the time, date, month, and year are counted. This RTC implementation is written for the ATmega128, and can easily be ported to other AVRs with RTC Module. For testing purposes the hardware used is listed below.
<br/>The advantages of implementing an RTC in software compared to an external hardware RTC are obvious:
 - Lower cost
 - Few external components
 - Lower power
 - Greater flexibility

<br/>This example is based on the Application Note [AVR134 - Real Time Clock (RTC) Using the Asynchronous Timer](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-1259-Real-Time-Clock-RTC-Using-the-Asynchronous-Timer_AP-Note_AVR134.pdf)


## Related Documentation

- [AVR134 - Real Time Clock (RTC) Using the Asynchronous Timer](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-1259-Real-Time-Clock-RTC-Using-the-Asynchronous-Timer_AP-Note_AVR134.pdf)
- [ATmega128 Device Page](https://www.microchip.com/wwwproducts/en/ATmega128)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) 5.40 or later
- [ATmega DFP](http://packs.download.atmel.com/) 2.2.108 or later
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) 2.20 or a later
- [AVR/GNU C Compiler](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers) 5.4.0 or later


## Hardware Used
- [ATmega128 TQFP](https://www.microchip.com/wwwproducts/en/ATmega128)
- 32.768 kHz crystal oscillator
- [STK600 Starter Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSTK600)
- [STK600 Routing Card](https://www.microchip.com/developmenttools/ProductDetails/ATSTK600-RC09)
- [STK600 Socket Card](https://www.microchip.com/developmenttools/ProductDetails/ATSTK600-SC02)
- [ATMEL-ICE](https://www.microchip.com/DevelopmentTools/ProductDetails/ATATMEL-ICE) to be able to program the STK600 in MPLAB X IDE.

## Setup
1. Connect the 32.768 kHz crystal oscillator directly between the pins TOSC1 and TOSC2. Refer to the device datasheet for details on crystal connections. For devices not mounted on a board, the [STK600 Starter Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSTK600) from Microchip can be used, it also has a socket for connecting the crystal.

## Operation

1. Connect the board to the PC.

2. Download the zip file or clone the example to get the source code.

3. Open the .project in MPLAB X IDE.

4. Build the solution and program the device.

## Conclusion

You have now seen an example of how to implement a real time counter on AVR controllers that features the RTC module.

