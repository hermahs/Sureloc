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

1. Clone the repository:

```bash
git clone https://github.com/hermahs/sureloc.git
```

. Set up the hardware:

Connect the RFID reader and the Arduino microcontroller according to the instructions in the "hardware" folder. You will also need to program the microcontroller with the code in the "firmware" folder.

3. Install the software:

The software is written in C++ and can be compiled using the Arduino IDE or any other compatible software. Simply open the "software.ino" file in the Arduino IDE and upload it to the microcontroller.

4. Test the system:

Use the RFID reader to scan the SureLocs and test the borrowing and lending functionality. You can also view the borrowing and lending history by connecting the microcontroller to a computer and opening the serial monitor.

That's it! You should now be able to use the SureLoc system locally, and start testing and developing new features. Please note that this is a student project and may not be suitable for production use without additional setup and configuration.

## Support

If you encounter any issues or have questions about using SureLoc, please feel free to create a GitHub issue. We're here to help and improve the system together!
