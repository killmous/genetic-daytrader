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
| 5 hours   | 110       |
| Daily     | 111       |

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

###TODO: FINISH
