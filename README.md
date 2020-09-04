# CrowdAlertM5StackMatrix

This Arduino sketch shows one possible way to use an [M5Stack Matrix](https://www.amazon.com/gp/product/B078NQNXHD/ref=as_li_qf_asin_il_tl?ie=UTF8&tag=abodit01-20&creative=9325&linkCode=as2&creativeASIN=B078NQNXHD&linkId=b9f18c210db906837a7755bda3b51fb9) as a display for [Crowd Alert](https://github.com/ianmercer/pi-sniffer).

This dimunitive display is a fully-functional ESP32 in a case with a 5x5 RGB LED for around $20.

Crowd Alert sends a regular UDP message containing the number of people present in an area times 10 times a configurable scale factor. The ideal range for this value is 0.0 to 3.0 representing not-crowded through to crowded. Using the data in these UDP messages, thi code maps the number sent onto one of three colors (with a slight blend between them) and gradually transitions the display to the desired color.

On startup the display cycles through a range of colors to show that it is working.

By placing one M5Stack Matrix by each door to a conference room or lab and using Crowd Alert sensing in the lab you can build a system that encourages people to socially distance thus helping reduce the spread of airborne viruses.

![M5StackMatrixCrowdAlert](https://user-images.githubusercontent.com/347540/92250911-eeedae00-ee80-11ea-9795-c7508de6df0a.jpg)
