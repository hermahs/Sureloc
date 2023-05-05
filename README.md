# SureLoc: Trust-Based Lending System

SureLoc is an open source project that provides a trust-based lending system for keeping track of who has taken out a certain physical item, called "SureLoc". The system allows users to borrow and lend SureLocs among themselves, while keeping a log of who has borrowed each item and for how long. This can help build trust and accountability among community members who share resources, especially in contexts where formal lending systems may not exist or may be difficult to access.

## Features

- User accounts: Users can create an account to participate in the lending system, and log in securely using their credentials.
- Item borrowing: Users can borrow SureLocs from other users, and keep track of who has borrowed each item.
- Item lending: Users can lend their own SureLocs to other users, and keep track of who has borrowed each item and for how long.
- Item history: The system keeps a log of all borrowing and lending activity for each SureLoc, including the borrower's name, the lending date, and the expected return date.
- Trust ratings: Users can rate each other based on their reliability as borrowers or lenders, and this rating can help other users decide whether to lend or borrow from them in the future.

## Technology

SureLoc is a student project that was developed using Arduino technology. The project uses RFID technology to identify the SureLocs, and an Arduino microcontroller to communicate with the RFID reader and log the borrowing and lending activity.

Please note that due to time constraints and limited resources, the project may not have all the features or functionality that a full-fledged system may have. However, we welcome contributions from anyone interested in helping to develop and improve SureLoc!

## Contributing

If you'd like to contribute to SureLoc, please take a look at our `CONTRIBUTING.md` file for guidelines on how to get started.

## License

SureLoc is licensed under the MIT License. See `LICENSE.md` for more information.

## Getting Started

To get started with SureLoc, follow these steps:

### Needed Components

Before you can use SureLoc, you'll need to gather the following components:

#### Control Box Components

| Component            | Quantity |
|----------------------|---------:|
| Arduino Uno v3       |        1 |
| RC522 RFID Reader    |        1 |
| 12v Power Adapter    |        1 |
| Buck Converter       |        1 |
| 100k ohm resistor    |        1 |
| SD card module        |        1 |
| SD card              |        1 |
| Breadboard           |        1 |
| Barrel jack          |        1 |
| 16x2 LCD screen      |  (optional) |
| Rotary encoder       |  (optional) |

#### Lending Module Components

| Component                  | Quantity |
|----------------------------|---------:|
| Arduino Pro Micro          |        1 |
| Servo                      |        1 |
| Small push press button    |        2 |
| Transistors                |        2 |
| 10k ohm resistor           |        2 |
| 1k ohm resistor            |        2 |
| Breadboard                 |        1 |
| Loadcell 5kg               |  (optional) x 4 |
| Loadcell amplifier         |  (optional) x 4 |

#### Parts Needed to be Printed

The following parts need to be 3D printed or laser cut:

##### Shelf module

| Part           | Quantity |
|----------------|---------:|
| Frame Left     |        1 |
| Frame Right    |        1 |
| Lock Container    |     1 |
| Moon lock      |        1 |
| Gears          |        2 |
| Frame Rails    |        4 |
| Drawer Rails   |        4 |
| Drawer       |          2 |
| Drawer lock holder |    2 |
| Clips Large    |        2 |
| Clips Small    |        2 |
| Breadboard holder | 1 |


##### Control box

| Part           | Quantity |
|----------------|---------:|
| Top hull     |        1 |
| Bottom plate    |        1 |
| Front plate    |     1 |
| Breadboard holder | 1 |
| RFID card reader | 1 |

Note that the box parts can also be laser cut in wood if you have the capability.

Please note that these components are not included in the SureLoc package and must be acquired separately.

## Assembly of the control box and shelf module

### Shelf Module Assembly Guide

1. Insert the clips into one side of the frame.
2. If you are using load cells, screw them into the frame with a little bit of space between them.
3. Insert the servo and moon lock into the lock container.
4. Screw the gears to the servo and moon lock.
5. Combine the frames with the lock container in the middle.
6. Add the rails to the frames.
7. Assemble the drawers.
8. Connect the wires and add the breadboard to the breadboard holder.

### Control Box Assembly Guide

1. Add the breadboard holder to the base plate.
2. Screw the RFID card reader into its holder on the front plate.
3. Attach the screen and rotary encoder to the front plate.
4. Add the buck converter and barrel jack for power.
5. Assemble the top hull over the base plate and screw together.

Note: This is a general guide for assembly and may not include all necessary steps.

## Assembly of the electrical systems

For the assembly of the electrical system, see the images below:



## Installing the Software

Once you have all the necessary components, you can install the SureLoc software on your Arduino microcontroller. To do this, follow these steps:

1. Download the SureLoc code from the GitHub repository.
2. Open the code in the Arduino IDE.
3. Connect the microcontroller to your computer via USB.
4. Upload the code to the microcontroller using the Arduino IDE.

## Support

If you encounter any issues or have questions about using SureLoc, please feel free to create a GitHub issue. We're here to help and improve the system together!
