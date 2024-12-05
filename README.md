# Introduction
This GitHub repository documents the design of a low-cost infrasound sensor. We provide a description of the circuit design along with the relevant .ino code for data acquisition and storage. 

Infrasound waves are a type of acoustic (pressure) wave with frequencies below the human audible threshold-— typically under 20 Hz. These waves can travel long distances and originate from both natural and artificial sources. Natural sources include volcanic eruptions, earthquakes, and even some animals, such as elephants and whales, which use infrasound to communicate over vast distances. Artificial sources include nuclear and chemical explosions, as well as machinery like diesel engines and wind turbines. Acoustic devices (woofers and subwoofers) can also produce low-frequency sound, potentially including near-infrasound. Such controlled sources are useful for testing the sensitivity of infrasound sensors and signal-noise separation in post-processing. 

In this experiment, we used a woofer to generate low-frequency sounds that are recorded by the infrasound sensor. Our sensor successfully detected the pressure field created by several different sources, demonstrating its functionality as an infrasound sensor. Practical usage of this sensor is discussed in the Applications section of this document.

# Design 
Parts: 
1. [Standard 9V battery](https://www.amazon.com/PKCELL-Maximum-Long-Lasting-Leak-Proof-Detectors/dp/B00ZTS55Y4/ref=zg_bs_g_389576011_d_sccl_4/133-1758009-7153552?psc=1)
2. [SDP810-125 differential pressure sensor](https://www.digikey.com/en/products/detail/sensirion-ag/SDP810-125PA/6605488)
3. [BMP390 barometric pressure sensor](https://www.adafruit.com/product/4816)
4. [XBee RF communication shield](https://www.tinyosshop.com/Xbee%20Shield)
5. [SD card writer](https://www.digikey.com/en/products/detail/adafruit-industries-llc/254/5761230?gclsrc=aw.ds&&utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=Pmax_Shopping_DK%2B%20Supplier_ITECH&utm_term=&utm_content=&utm_id=go_cmp-21147141757_adg-_ad-__dev-c_ext-_prd-5761230_sig-Cj0KCQiAu8W6BhC-ARIsACEQoDDO7fIDbgui0jB24heOPZQb_AjEaTjcEO5iy__woYfIqouTcPxJ1OsaAuejEALw_wcB&gad_source=1&gclid=Cj0KCQiAu8W6BhC-ARIsACEQoDDO7fIDbgui0jB24heOPZQb_AjEaTjcEO5iy__woYfIqouTcPxJ1OsaAuejEALw_wcB&gclsrc=aw.ds)
6. [SD card](https://www.amazon.com/SanDisk-3-Pack-Ultra-Memory-3x32GB/dp/B08GY9575R/ref=sr_1_3?crid=1SOA0HEH90LZ5&dib=eyJ2IjoiMSJ9.hQqTZGlZd9V2GIrXprQC5JC6IXKaE6h6nwBd7TCHT-XGCipTIBl3iaMbFFl6avG5aZiAp_pmK2QUqku2RxFShHqdRTCFh3Hx1LKa6YvmcwuXIm3XLu7t5do5F8pC6bFwvu0tqlNCkEQFp3xbSA8kQlux9nHHgxIZuqM7dYQV5u8hki33DO0ODvmRBQ5flP9zVQr8HxfOCCWMw0Goa4PduhBMO5WV55EcW0XanZqfGfo.7_flmoYglnLs9RA4CDwW3aTVpN7HWKLhQH7jVxFNcDA&dib_tag=se&keywords=32+GB+sd+card&qid=1733416760&sprefix=32+gb+sd+card%2Caps%2C147&sr=8-3)
7. [BN-280 GPS module](https://store.beitian.com/products/beitian-gps-module-with-antenna-ubx-m10050-gnss-chip-ultra-low-power-gnss-receiver-for-track-be-280?variant=44373885616415&srsltid=AfmBOooMkOwoqqiY4GBIr7OxF1UAmp9Qw3sXnslK-Ptm95SI2oD-UdiK)
8. [Arduino Nano](https://www.digikey.com/en/products/detail/arduino/A000005/2638989?gclsrc=aw.ds&&utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20243063506_adg-_ad-__dev-c_ext-_prd-2638989_sig-Cj0KCQiAu8W6BhC-ARIsACEQoDBTD2_9hd4dZnQ7dMdN0KglQeLHIxiTRR5XjcEkNcvqNSMsdOB7FM0aArCiEALw_wcB&gad_source=1&gclid=Cj0KCQiAu8W6BhC-ARIsACEQoDBTD2_9hd4dZnQ7dMdN0KglQeLHIxiTRR5XjcEkNcvqNSMsdOB7FM0aArCiEALw_wcB&gclsrc=aw.ds)
9. [Arduino UNO](https://www.digikey.com/en/products/detail/arduino/A000066/2784006?gclsrc=aw.ds&&utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20243063506_adg-_ad-__dev-c_ext-_prd-2784006_sig-Cj0KCQiAu8W6BhC-ARIsACEQoDB-5zRvcEcZCzNVXZGHN11ImdkSehHEJr5OruJRdEUuLezWGa85VUMaAq3JEALw_wcB&gad_source=1&gclid=Cj0KCQiAu8W6BhC-ARIsACEQoDB-5zRvcEcZCzNVXZGHN11ImdkSehHEJr5OruJRdEUuLezWGa85VUMaAq3JEALw_wcB&gclsrc=aw.ds) 
10. [3D printed case and ports](https://formlabs.com/3d-printers/form-3/?srsltid=AfmBOopFRAd2Nutp5a-4NDmB9jMAnkUhlHDc3qHuftNpa3CwsTDpFNEM) 

### Circuit design and Implementation: 
Our sensor system is divided into two subsystems that are controlled by independent Arduino controller boards, while sharing a common power source. This was done because both the GPS module and differential pressure sensor required an I2C connection. Although these devices have independent I2C addresses and could theoretically be connected to the same Arduino, the specific pressure sensor we used requires pull-up resistors that interfere with the GPS module. 

The first subsystem includes the GPS module and BMP390 barometric pressure sensor. During initial testing, we configured this subcircuit to communicate its information via XBee RF communication to a local host. The second subsytem contained the Differential pressure sensor and SD card writer for data collection and storage. 

#### BMP 390 and GPS: 
This circuit employs an Arduino UNO to power and record data from the BMP390 barometric pressure sensor and BN-080 GPS module. Data from these components is transmitted using the XBee communication system. The diagram below illustrates the circuit design (without the XBee hat that simply slides onto the UNO), showing how each component is connected to the Arduino UNO.

For field deployment, a 9V battery powers the Arduino and the sensors. The battery is connected to a soldering board, which supplies power to both the BMP390 sensor and the Arduino UNO. The BMP390 sensor connects to pins 6, 7, 8, and 9 on the Arduino UNO.

The GPS module is connected to the Arduino UNO for power and ground. The GPS TX pin connects to Arduino pin 4, and the GPS RX pin connects to Arduino pin 3. SDA and SCL lines are connected to Arduino pins A3 and A4, respectively.

![circuits 001](https://github.com/user-attachments/assets/4f1112a3-0d4d-4847-9a9c-a6900fcfa5ad)


#### SDP810-125 Differential Pressure Sensor
The second circuit of the sensor system is the differential pressure sensor and SD writer. In this configuration, the same 9V battery provides a common power hookup to a second soldering board, which subsequently reroutes power to the Arduino Nano, the differential pressure sensor, and the SD card device.

Data recorded by the differential pressure sensor is transmitted directly to and stored on an SD card. To ensure proper communication between the differential pressure sensor and the Arduino Nano, 10 $K \omega$ resistors are added to the SDA and SCL as (poorly) described by the manufacturer. SDP810-25 SDA is connected to Ardunio Nano pin A5, while SCL is connected to A4. The SD card reader is also connected to the Arduino Nano through pins 13, 14, 15, and 16. 

![circuits 002](https://github.com/user-attachments/assets/2b3a5c44-fdde-4ee2-83b2-a39a9620616e)


# General Testing 
We performed first order testing with pulses generated by an acoustic source (JBL PartBox 1000). The signals were clearly identifiable even over a range of frequencies. We tested at a maximum distance of 5 meters from the source, with source amplitude slightly above speaking level. Rudimentary tests of air displacement from hand waving and blowing were also successfully captured. We then attempted to test the sensor design with a song, but SDP810-25 sampling was too coarse to appropriately reconstruct the high frequency content used in songs resulting in a severely distorted audio reconstruction. Further testing will use an ultra low chirped source at constant frequency with known perturbation and timing. We can then systematically adjust the frequency content of this chirp to test the sensors' frequency response. Controlled source experiments such as this will be vital when demonstrating gradiometry and seismic interferometry.  

# Application  
Infrasound monitoring is used for a wide range of applications, including nuclear monitoring and nonproliferation, earthquake event triangulation, and hazard monitoring. Earthquakes represent a unique source of infrasound waves as they originate in the subsurface and transmit into the atmosphere. Thus, it is possible to using balloon-based infrasound to detect infrasound events in hostile locations (e.g., the ocean). Garcia et al. (2022) and Krishnamoorthy et al. (2019) have shown that balloon-based infrasound sensors can be used to detect infrasound waves generated by earthquakes. In these experiments, a single infrasound sensor was attached to a balloon and launched into the atmosphere providing a single point measurement of the acoustic wavefield. However, simultaneous balloon deployment and balloons equipped with multiple infrasound sensors could provide a more comprehensive understanding of the infrasound wavefield. 

Single balloons with multiple sensors can be used to study subtle variations of the pressure field in the atmosphere. Wavefield gradiometry can be used to study the spatial gradients of the pressure field, allowing us to better probe understand ultra low frequency propagation. Separate balloons each equipped with an infrasound sensor can be used to study the spatial distribution of the pressure field, while also offering a unique opportunity to perform seismic interferometry (SI). In this configuration, one balloon can be treated as the infrasound source while the other acts as the receiver, thereby enabling us to estimate travel time between the balloons. This information can be used to estimate velocity perturbations in the atmosphere to study the atmospheric structure, and may also be capable of performing tomographic imaging of the near surface and air column for waves originally generated by subsurface sources. 

Balloon-based infrasounds sensors have also been proposed for studying the internal structure of planetary bodies, like Venus, as described by Garcia et al. (2005). Venus is particularly amenable to atmospheric studies because thick, hot, high pressure atmosphere. Landed instrumentation like seismometers can only survive for a short period before being crushed by the high pressure. Communication is also difficult due to the opaque atmosphere. However, balloon-based infrasound sensors could be used to probe the internal structure of Venus by detecting transmitted P-wave energy from subsurface activity. Because this transmitted energy contains information from the subsurface propagation, it can be used to study the internal structure of Venus.
Sánchez-Lavega et al. (2017) also indicate the presence of acoustic fields generated in the Venusian atmosphere. Averbuch (2024) suggests that the Venusian atmosphere may have pressures two orders of magnitude larger than Earth, thereby enabling significantly improved infrasound transmission across a range of frequencies. 

This project represents our first attempt to develop a low-cost infrasound sensor intended for testing seismic imaging of the near subsurface. While significant improvements are needed to create a sensor suitable for deployment on a balloon, our prototype successfully detected low-frequency sound waves generated by a speaker, demonstrating its potential for further development.

# Discussion 
Balloon-based infrasound detection systems offer a new source of data for studying the atmosphere and subsurface of the Earth and other planetary bodies. The sensor system we developed is a first step toward creating a low-cost, portable infrasound sensor that can be deployed on a balloon. We hope to continue developing this sensor suite to perform testing with a source capable of producing the low frequency, low amplitude events that we anticipate. More advanced testing could enable a demonstration of seismic interferometry and gradiometry coupled with modelling to demonstrate the potential of such sensors for directly investigating the atmosphere and subsurface. With low cost, simple designs such as the one proposed here, we can also begin to study the effect of transient pressure waves caused by wind, better understanding the sources of noise that may contaminate data. 

Our sensor system successfully detected low-frequency sound waves generated by a speaker, demonstrating its potential for further development. Future work will focus on improving the sensor’s reliability and accuracy, as well as exploring the possibility of using dual barometers to employ seismic interferometry. We intend to deploy the sensor on near-surface balloons with known source signals before deploying the suite on a high-altitude balloon to test its performance in realistic field conditions. Ultimately, we hope to use balloon-based infrasound sensors to study the internal structure of planetary bodies like Venus, as well as to improve our understanding of the Earth’s atmosphere and subsurface. This project represents our first step toward achieving these goals. 

# Future Work
After conducting this experiment and testing our sensor, we identified several areas for improvement. First, the Sensirion differential pressure sensor proved problematic due to its need for capacitor discharge after each use and its overall unreliability during testing, making it unsuitable for potential field deployment. A priority for future iterations will be to identify and integrate a more reliable differential pressure sensor. Additionally, we plan to add a second barometric pressure sensor and calibrate them against each other to explore the possibility of using dual barometers as a differential pressure system, potentially enhancing both accuracy and reliability. Looking ahead, once the sensor’s reliability is improved, we aim to deploy it using a high-altitude balloon. Programs like the University of Colorado Boulder’s DemoSat, which provides students access to high-altitude balloon flights for scientific payloads, offer an excellent platform for testing the sensor in realistic field conditions. Furthermore, we envision deploying multiple sensors in future experiments to enable advanced signal processing techniques such as interferometry.
