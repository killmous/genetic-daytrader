[![Build Status](https://travis-ci.org/killmous/genetic-daytrader.svg?branch=master)](https://travis-ci.org/killmous/genetic-daytrader)
#genetic-daytrader

Cryptocurrency daytrader utilizing genetic strategies

##Chromosome structure

###Gene 1

Bit 1 <= Whether to invest in bitcoin  
Bit 2 <= Whether to invest in litecoin  
Bit 3 <= Whether to invest in dogecoin  

###Gene 2

Frequency

| Frequency | Bitstring |
| --------- | --------- |
| 1 min     | 001       |
| 5 mins    | 010       |
| 15 mins   | 011       |
| 30 mins   | 100       |
| 1 hour    | 101       |
| 2 hours   | 110       |
| 5 hours   | 111       |
| Daily     | 000       |

###Gene 3

Moving Average

Bit 1 <= MA type (0 = simple, 1 = exponential)

Bits 2-3 are short period

| Periods | Bitstring |
| ------- | --------- |
| 5       | 00        |
| 10      | 01        |
| 15      | 10        |
| 20      | 11        |

Bits 4-5 are long period

| Periods | Bitstring |
| ------- | --------- |
| 30      | 00        |
| 40      | 01        |
| 50      | 10        |
| 60      | 11        |

###Gene 4

Trailing Stop

| Trailing Stop % | Bitstring |
| --------------- | --------- |
| 1%              | 001       |
| 2%              | 010       |
| 3%              | 011       |
| 4%              | 100       |
| 5%              | 101       |
| 6%              | 110       |
| 7%              | 111       |
| 8%              | 000       |

---

Example: bitstring `10101110111001` would mean that we are investing in bitcoin and dogecoin, we are using a period of 15 minutes, we are using an exponential moving average with a short period of 10 periods, a long period of 60 periods, and a trailing stop of 1%.
