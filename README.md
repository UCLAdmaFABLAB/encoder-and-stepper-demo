## DMA Fab Lab Encoder/Stepper demo project

![Encoder demo gif](/Photos/Encoder.gif)

### Parts list:

- [Arduino Leonardo](https://store.arduino.cc/products/arduino-leonardo-with-headers) - Could be anything, we used what we had around
- [Stepper motor - NEMA-17 size - 200 steps/rev, 12V 350mA](https://www.adafruit.com/product/324)
- [Encoder - Yumo E6B2-CWZ3E](https://www.mouser.com/datasheet/2/307/e6b2-c_ds_csm491-25665.pdf)
- 2 X [Pololu Universal Aluminum Mounting Hub for 5mm Shaft](https://www.pololu.com/product/1203)
- [Nylon spacers for PCBs](https://www.amazon.com/Lystaii-Standoff-Motherboard-Standoffs-Assortment/dp/B08LPYR49C/ref=sr_1_3?keywords=pcb%2Bspacers&qid=1702333765&sr=8-3&th=1)
- [3 x 3 mm magnet](https://www.amazon.com/FINDMAG-Magnets-Magnetic-Whiteboard-Refrigerator/dp/B092MCQ3NL/ref=sr_1_3?crid=3TSIQPVJFTKLE&keywords=3mm%2Bmagnets&qid=1702333936&sprefix=3mm%2Bmagnet%2Caps%2C128&sr=8-3&th=1)
- [Reed switch](https://www.sparkfun.com/products/8642)
- [Female Threaded Hex Standoff, 13mm Hex, 52mm Long, M6 x 1mm Thread](https://www.mcmaster.com/94868A778/) - Any spacer longer than 1.75" will do
- 4 X [3 mm LEDs](https://www.adafruit.com/product/778)
- [12mm Momentary Push Button Switch 1/2" Mounting Hole](https://www.amazon.com/Twidec-Waterproof-Momentary-Pre-soldered-PBS-33B-BK-X/dp/B099ML1F48/ref=sr_1_14?crid=3R8W9XJ4TM3QT&keywords=button%2Bswitch&qid=1702334727&sprefix=button%2Bswitch%2Caps%2C130&sr=8-14&th=1) - We're using these ones but any momentary switch will do
- [12 V DC power supply](https://www.adafruit.com/product/2591) - Something like this should do
- [DRV8880 Stepper Motor Driver](https://www.pololu.com/product/2971)
- [Jumper wires](https://www.adafruit.com/product/1957) or ribbon cable - we're using ribbon cable with crimpable connectors
- [40 x 60 mm perfboard](https://www.amazon.com/MECCANIXITY-Prototyping-Soldering-Electronic-40mmx60mm/dp/B09NR8F8HX)
- 4 X [470 Ω resistors](https://www.adafruit.com/product/2781)
- [22AWG Solid core wire](https://www.adafruit.com/product/2988) 
- Assorted screws and nuts for mounting part


### Code:

- Use the *EncoderProject_06* arduino sketch from the *Code* folder
- This project uses two libraries: the [Encoder library](https://github.com/PaulStoffregen/Encoder) and the [StepperDriver library](https://github.com/laurb9/StepperDriver/tree/master)
- Code is a bit messy and not very commented for now

### Fabrication:

- This project requires some laser cutting. There are two files in the *Fabrication* folder: 
    - *Electronics plate laser cut.ai* 
    - *Main plate laser cut.ai*. 
    - Both files contain instructions for materials
- There are two optional 3D printed parts. Both can be found in the *Fabrication* folder:
    - *CableGuide v3* is a small cable routing part that can help managing the wires
    -  *Reed Switch Holder v2* supports the reed switch at the correct rotation relative to the magnet





