# NOTE

## 简单使用 easy to use

演示了简单的服务端和客户端之间互相通信。以及客户端通过控制台输入字符串，发送给服务端。

It demonstrates the communication between simple server and client. And the client enters a string through the console and sends it to the server.

```
test_input_msg_client.cpp
test_input_msg_server.cpp
```

## 大量数据多线程测试 Mass data multi-threaded testing

主要是测试多线程情况下的通信数据是否具有原子性写入，以及是否支持大量数据传输。

It is mainly to test whether the communication data in the case of multi-threading has atomic writing, and whether it supports a large amount of data transmission.

客户端多线程写入，服务端接收到数据后写入到文件。

The client writes in multiple threads, and the server writes to the file after receiving the data.

```
test_multithreading_bigdata_client.cpp
test_multithreading_bigdata_server.cpp
```

check.cpp是为了测试服务端接收到的数据是否具有线程安全（原子性写入），以及数据是否完整无误。

check.cpp is to test whether the data received by the server is thread-safe (atomic writing), and whether the data is complete and error-free.

```
test_multithreading_bigdata_check.cpp
```