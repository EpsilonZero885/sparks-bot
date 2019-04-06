---
layout: default
permalink: /index.html
---


# Getting Started

## Example

Sparks-bot is modelled after the adafruit open-source esp8266 robot that can be found [here](https://learn.adafruit.com/build-an-esp8266-mobile-robot/introduction)

## Feather Line

Adafuit maintains a bunch of open-source and free libraries you can use because they are a hardware/education company. For this project, we will be using mostly products available on the Feather line, which allows for a huge catalog of supported devices and guaranteed support.

## Esp8266 Docs

Adafruit maintains libraries, tutorials, and the actual hardware schematics [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/downloads)

## Digital Logic

Most pins on this device are digital at 3.3V.

## Analog Logic
There is a single analog pin.

## Databases and Data Storage

### MongoDB
MongoDB is very useful for partitioned networks.

### MQTT
Two way data-broker, aysynchronous.

### JSON
Universal language of applications on the internet


## Networking
The ssid is 'sparks-net'.  
The password is 'sciencerules!'

# Robot Control Software

Adafruit has a variety of boards with the 'Feather' name. These are boards that play nice with each other by easily sharing data, power, and control pins where appropriate. In many cases, these board stack on top of each other. There are also cheap adapters  that connect these boards side-by-side, supporting up to 3 boards. However, you will have to do a power budget to ensure that you have enough current (measured in mA) to power everything you want to do. If you're very clever, you can power your sensors on at different times and conserve power.

## esp8266-robot

This is the software to build a web-controlled robot using the esp8266. It supports the current configuration of the esp-8266 board driving the Feather DC motor board

## mqtt_esp8266

MQTT is a protocol for exchanging data between a bunch of clients (the esp_8266) and your central server (the raspberry pi).

where the ```&``` allows you to continue to use that terminal even though it has an open, running process (Firefox).


# Data Server Software [link](/server/)

## interface [link](/dashboard/)

This folder contains the html, css, and javascript code that makes a website in a browser that can control your robot. It currently supports, up, down, left, and right, buttons that then send json requests to the hard-coded ip address in the script.js document. Currently, it is set to 192.168.50.221. This can be run on any computer that is connected to the same network as the robot. Style.css is the stylesheet, and demo.html is the webpage that you open in the browser. Either double-click that file or open it in firefox using the command line
```
firefox demo.html &
```


TODO:
## MQTT Broker

## VLC

## MySQL

## Anaconda Server

## Multi-Threading
