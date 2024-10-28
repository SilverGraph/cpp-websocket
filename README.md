## Required libraries to install before running the server.cpp file

```
sudo apt-get install libboost-all-dev
sudo apt-get install libssl-dev
sudo apt install libwebsocketpp-dev
```

## Run the following commands to start the web-socket
```
cd cpp-websocket/
g++ -o ./streaming_deribit server.cpp -lssl -lcrypto -pthread
./streaming_deribit
```
