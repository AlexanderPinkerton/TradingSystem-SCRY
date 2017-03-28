::Run this file via VSDevelopmentConsole to generate windows project and build

mkdir build_windows
cd build_windows
cmake .. -G "Visual Studio 14 Win64"

msbuild TradingSystem.sln
copy PoloniexAPI\Debug\PoloniexAPI.dll Debug\