# LoRa Range Test Comparison

## Introduction
This project compares the range performance of two LoRa modules: SX1276 and RYLR998. The aim is to provide insights into their capabilities under various conditions.

## Methodology
### Hardware Used
- **SX1276 Module**: [[Link to datasheet or product page](https://drive.google.com/file/d/1XbGJ3n85z9ruFIZIR3pf4iT_ciRSNruP/view?usp=drive_link)]
- **RYLR998 Module**: [[Link to datasheet or product page](https://drive.google.com/file/d/14TzN-kvCyWQNE_3eZQ7v73Q64Uy4R5tQ/view?usp=drive_link)]

### Test Setup
1. **Line of Sight**:The transmitter and the receiver should have a line of sight and there shouldn't be any concrete buildings in between because it causes a lot of decrease in range
2. **Weather conditions**: consider Operating on a sunny day and not in a rainy atmosphere

### Procedure
1. **Transmitter Setup**: The transmitter that we kept we on a little height (1st floor) to get a better range and we made sure that they are no concrete buildings in between. Also the transmitter is connected with an ESP 32 to get the log. define the transmitter and receiver pins corerectly and and the have the baud rate same. The codes are provided below
2. **Receiver Setup**: The receiver is also connected with an ESP 32 but to get the logs on mobile we connected the ESP to telnet WIFI server. Both the receiver's and transmitter code of lora1276 are provided below.

## Results
### SX1276
- **Maximum Range**:Around 3 kilometers (you can get more if your line of sight is very clear and the transmitter is at a greater height)
- **max RSSI**: -103 dBm

### RYLR998
- **Maximum Range**: same as SX1276
- **Average RSSI**: -115 dBm



## Conclusion

### LoRa SX1276
- **Flexibility**: Offers more control over various parameters, making it suitable for custom implementations.
- **Libraries and Support**: Widely used, with extensive community support and libraries available.
- **Range and Performance**: Provides a good range and performance, but dependent on implementation.
- **Complexity**: Requires more detailed setup and understanding of LoRa parameters.
- **Integration**: Typically used in custom PCBs and projects where you need detailed control over the radio settings.
  
### LoRa RYLR998
- **Ease of Use**: Simplified with built-in AT command set, making it easier to integrate and configure.
- **Libraries and Support**: Adequate support, though less extensive than SX1276.
- **Range and Performance**: Similar range as SX1276 , but with different RSSI values.
- **Complexity**: Less complex to set up, making it ideal for quick deployments and prototypes.
- **Integration**: Better for rapid development and projects where ease of use is prioritized.
  
### Key Considerations
- **Project Complexity**: For detailed and complex projects requiring fine-tuning, SX1276 might be better.
- **Development Speed**: For faster development and ease of integration, RYLR998 might be preferable.
- **Support and Community**: SX1276 has broader community support, which can be beneficial for troubleshooting and getting help.
- **Performance Needs**: Both modules performed similarly in range tests, so performance might not be a deciding factor unless specific conditions or configurations are required.
  
Given your experience and findings, if you need more control and flexibility, SX1276 is likely the better choice. If you prefer simplicity and quicker setup, RYLR998 would be more suitable.



## Acknowledgments
Thanks Arduino IDE and software serial library for this project and also thanks to 
