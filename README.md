# 2019_MorseButton
# Overview 
Morse Button is a program for communication with computer and Morse traslation.
# Description 
Morse Button is a program for STM32. Its main fuctionality is to translate morse code to latin alphabet. It can receive data from computer by Virtual Com port and directly from user with a button.
# Tools 
C language,STM32, Nokia 5110 screen, Thumb Joystick, Speaker with amplifier.
# How to run 
click run button
# How to compile 
- Clone, compile project to STM32F4 Discovery.
- Connect all pins correctly:
BL - PE6
CE - PC13
RST - PC15
SPI1_SCK - PA5
SPI1_MOSI - PA7
DC - PD11
Sound - PD15

# Attributions 
- Virtual Com Port: https://forbot.pl/blog/kurs-stm32-f4-11-komunikacja-przez-usb-id13477
- Nokia 5110 Screen inspiration: https://forbot.pl/blog/kurs-stm32-10-spi-w-praktyce-wyswietlacz-graficzny-2-id9964
# License
licence: MIT

# Credits
 Juliusz Horowski  
 Marcin Jasiński  
 
The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology. Supervisor: Tomasz Mańkowski
