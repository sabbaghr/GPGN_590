# Introduction
This GitHub repository contains the code and details for a low-cost infrasound wave sensor. Infrasound waves are a type of acoustic (pressure) wave with frequencies below the human audible threshold—typically under 20 Hz. These waves can travel long distances and originate from both natural and artificial sources. Natural sources include volcanic eruptions, earthquakes, and even some animals, such as elephants and whales, which use infrasound to communicate over vast distances. Artificial sources include nuclear and chemical explosions, as well as machinery like diesel engines and wind turbines. Devices like woofers and subwoofers can also produce low-frequency sound, including near-infrasound frequencies.

In this experiment, we used a speaker equipped with a woofer to generate low-frequency sounds. Our sensor successfully detected the pressure field created by these waves, demonstrating its functionality as an infrasound sensor. Practical usage of this sensor is discussed in the Applications section of this document.

# Design 
Parts: 
1. 9V Battery power 
2. SDP810-125 differential pressure 
3. BMP390 barometric pressure sensor 
4. XBee RF communication shield 
5. SD card writer/SD card 
6. BN-080 GPS module 
7. 3D printed case and ports 
8. Arduino UNO 
9. Arduino Nano


### Circuit design and Implementation: 
Our sensor system is divided into two subsystems that are controlled by independent Arduino controller boards, while sharing a common power source. This was done because both the GPS module and differential pressure sensor required an I2C connection. Although these devices have independent I2C addresses and could theoretically be connected to the same Arduino, the specific pressure sensor we used requirs pull-up resistors that interfere with the GPS module. 

The first subsystem includes the GPS module and BMP390 barometric pressure sensor. During initial testing, we configured this subcircuit to communicate its information via XBee RF communication to a local host. The second subsytem contained the Differential pressure sensor and SD card writer for data collection and storage. 

#### BMP 390 and GPS: 
This circuit employs an Arduino UNO to power and record data from the BMP390 barometric pressure sensor and BN-080 GPS module. Data from these components is transmitted using the XBee communication system. The diagram below illustrates the circuit design (without the XBee hat that simply slides onto the UNO), showing how each component is connected to the Arduino UNO.

For field deployment, a 9V battery powers the Arduino and the sensors. The battery is connected to a soldering board, which supplies power to both the BMP390 sensor and the Arduino UNO. The BMP390 sensor connects to pins 6, 7, 8, and 9 on the Arduino UNO.

The GPS module is connected to the Arduino UNO for power and ground. The GPS TX pin connects to Arduino pin 4, and the GPS RX pin connects to Arduino pin 3. SDA and SCL lines are connected to Arduino pins A3 and A4, respectively.

![circuits 001](https://github.com/user-attachments/assets/4f1112a3-0d4d-4847-9a9c-a6900fcfa5ad)


#### SDP810-125 Differential Pressure Sensor
The second circuit of the sensor system is the differential pressure sensor and SD writer. In this configuration, the same 9V battery provides a common power hookup to a second soldering board, which subsequently reroutes power to the Arduino Nano, the differential pressure sensor, and the SD card device.

Data recorded by the differential pressure sensor is transmitted directly to and stored on an SD card. To ensure proper communication between the differential pressure sensor and the Arduino Nano, 10 $K \omega$ resistors are added to the SDA and SCL as (poorly) described by the manufacturer. SDP810-25 SDA is connected to Ardunio Nano pin A5, while SCL is connected to A4. The SD card reader is also connected to the Arduino Nano through pins 13, 14, 15, and 16. 

![circuits 002](https://github.com/user-attachments/assets/8de210bf-c137-4f88-be97-989ec461876f)

# General Testing 
We performed first order testing with pulses generated by an acoustic source (JBL PartBox 1000). The signals were clearly identifiable even over a range of frequencies. We tested at a maximum distance of 5 meters from the source, with source amplitude slightly above speaking level. Rudimentary tests of air displacement from hand waving and blowing were also successfully captured. We then attempted to test the sensor design with a song, but SDP810-25 sampling was too coarse to appropriately reconstruct the high frequency content used in songs resulting in a severely distorted audio reconstruction. Further testing will use an ultra low chirped source at constant frequency with known perturbation and timing. We can then systematically adjust the frequency content of this chirp to test the sensors' frequency response. Controlled source experiments such as this will be vital when demonstrating gradiometry and seismic interferometry.  

# Aplication 
Infrasound monitoring is used for a wide range of applications, including nuclear monitoring and nonproliferation, earthquake event triangulation, and hazard monitoring. Earthquakes represent a unique source of infrasound waves as they originate in the subsurface and transmit into the atmosphere. Thus, it is possible to using balloon-based infrasound to detect infrasound events in hostile locations (e.g., the ocean). Garcia et al. (2022) and Krishnamoorthy et al. (2019) have shown that balloon-based infrasound sensors can be used to detect infrasound waves generated by earthquakes. In these experiments, a single infrasound sensor was attached to a balloon and launched into the atmosphere providing a single point measurement of the acoustic wavefield. However, simultaneous balloon deployment and balloons equipped with multiple infrasound sensors could provide a more comprehensive understanding of the infrasound wavefield. 

Single balloons with multiple sensors can be used to study subtle variations of the pressure field in the atmosphere. Wavefield gradiometry can be used to study the spatial gradients of the pressure field, allowing us to better probe understand ultra low frequency propagation. Separate balloons each equipped with an infrasound sensor can be used to study the spatial distribution of the pressure field, while also offering a unique opportunity to perform seismic interferometry (SI). In this configuration, one balloon can be treated as the infrasound source while the other acts as the receiver, thereby enabling us to estimate travel time between the balloons. This information can be used to estimate velocity perturbations in the atmosphere to study the atmospheric structure, and may also be capable of performing tomographic imaging of the near surface and air column for waves originally generated by subsurface sources. 

Balloon-based infrasounds sensors have also been proposed for studying the internal structure of planetary bodies, like Venus, as described by Garcia et al. (2005). Venus is particularly amenable to atmospheric studies because thick, hot, high pressure atmosphere. Landed instrumentation like seismometers can only survive for a short period before being crushed by the high pressure. Communication is also difficult due to the opaque atmosphere. However, balloon-based infrasound sensors could be used to probe the internal structure of Venus by detecting transmitted P-wave energy from subsurface activity. Because this transmitted energy contains information from the subsurface propagation, it can be used to study the internal structure of Venus.
Sánchez-Lavega et al. (2017) also indicate the presence of acoustic fields generated in the Venusian atmosphere. Averbuch (2024) suggests that the Venusian atmosphere may have pressures two orders of magnitude larger than Earth, thereby enabling significantly improved infrasound transmission across a range of frequencies. 

This project represents our first attempt to develop a low-cost infrasound sensor intended for testing seismic imaging of the near subsurface. While significant improvements are needed to create a sensor suitable for deployment on a balloon, our prototype successfully detected low-frequency sound waves generated by a speaker, demonstrating its potential for further development.

# Discussion 
Sensirion sucks. 

# Future Work
New differential pressure sensor. Test with 2 barometric sensors and see if they can be calibrated against each other to act as a differential pressure sensor. Test with some better sources. Deploy on CU balloon. 
