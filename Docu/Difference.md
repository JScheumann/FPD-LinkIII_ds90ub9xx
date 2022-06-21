# Unterschiede in den Registern

| Adresse |  4k   | newDriver | Read/Write |                  Erklärung                  |
| :-----: | :---: | :-------: | :--------: | :-----------------------------------------: |
|  0x18   | 0x77  |   0x60    |            |                SAR ADC Dout                 |
|  0x37   | 0x7a  |   0x60    |            |               Deserializer ID               |
|  0x5c   | 0x00  |   0x01    |            |               CSI Error count               |
|  0x5d   | 0x00  |   0x10    |            | CSI Error Status (here a 2 bit sync error)  |
|  0x5e   | 0x11  |   0x31    |            |      Control Error in HS Request Mode       |
|  0x5f   | 0x11  |   0x40    |            |      Multi bit Error in SYNC Sequence       |
|  0x61   | 0x2b  |   0x00    |            |       Data ID from CSI Packet Header        |
|  0x62   | 0x60  |   0x00    |            | Payload count lower byte from CSI Pac. head |
|  0x63   | 0x09  |   0x00    |            |  Payl. count upper byte from CSI Pac. head  |
|  0x64   | 0x1d  |   0x00    |            |           line length && CSI ECC            |
|  0x65   | 0x88  |   0x99    |            |      SAR ADC REGISTER LINE FAULT TRESH      |
|  0x68   | 0xAA  |   0x00    |            |                      "                      |
|  0x6b   | 0x99  |   0xad    |            |                      "                      |
|  0x89   | 0xf8  |   0x00    |            |                     ???                     |
|  0x8a   | 0x0f  |   0x00    |            |                     ???                     |
|  0x8b   | 0xff  |   0x00    |            |                     ???                     |
|  0x8c   | 0x02  |   0x03    |            |                     ???                     |
|  0x9f   | 0x0a  |   0x0b    |            |            line fault threshold             |
|  0xa0   | 0x0f  |   0x00    |            |                      "                      |
|  0xa1   | 0x0a  |   0x0b    |            |                      "                      |
|  0xa2   | 0x09  |   0x0a    |            |                      "                      |
|  0xa3   | 0x08  |   0x09    |            |                      "                      |
|  0xa4   | 0x07  |   0x09    |            |                      "                      |
|         |       |           |            |
