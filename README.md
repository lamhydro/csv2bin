# csv2bin
## Overview
This piece of sotfware:
1. `readCSVFile()` read a `*.csv` file formed by rows and columns into a struct.
2. `writeCsv2Bin()` save the struct into a `*.bin` file.
2. `readBINFile()` read the just saved `*.bin` file (optional)

The case presented here is for a CSV file containing a time series. The code need to be adapted depending of CSV data structure, in particular, the structre in `csv2bin.h`.

## Execution
### Compile
`make`. To clean `make clean`
### Execute
`make test`. This will read `ts.csv` and produce `ts.bin` within `/test` dir.



