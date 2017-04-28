# Trading System - SCRY 

The main idea of this trading system is to create a cross-platform trading platform which is able to quickly backtest trading strategies against historical data to asses their potential as well as running strategies on live data. In terms of strategies, this platform will eventually allow the easy use of advanced machine learning techniques to outline entry and exit points. This platform will also eventually supply a REST API which will allow one to view their strategies performance and issue commands from anywhere. Since this is my first trading system, development is slow. 

# Debian Installation
```sh
$ cd TradingSystem-SCRY
$ mkidr build
$ cd build
$ cmake ..
$ make
```

# Windows Installation
#### Dependencies
    Qt 5
    Openssl 1.0.2k
Run the generateVSProject batch file to generate a windows build project via Cmake
Go to the windows_build folder and open the TradingSystem.sln
Build the solution and ensure that the PoloniexAPI.dll is next to the TradingSystem.exe
???
Profit

# Current Functionality
  - Create column-oriented dataset from JSON ✔
  - Render Candlestick chart of dataset ✔
  - Calculate and render multiple indicators over chart ✔

# Future Goals
  - Add update functionality for live data streams
  - Dataset sanitization. Handle missing values..etc
  - Indicator Events to be used as features( intersections..etc)
  - Create simple rule-based strategy system
  - Create complex feature-based timeseries strategies levering Dlib
  - Create system which can Backtest strategies to check performance
  - Create online system which enters and exits according to strategy events.
  - Create REST API which allows remote access to performance and overrides

# Implementation Overview 
//TODO:

