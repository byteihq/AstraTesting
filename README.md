## Build
```sh
cmake -H. -B_build
```
```sh
cmake --build B_build
```
## Install
```sh
cmake -H. -B_build
```
```sh
sudo cmake --build _build --target install
```
## Params
### Ping
- **ping_ip** - IP (192.168.0.2 - by default)
- **ping_i** - Interval (0.1 - by default)
- **ping_s** - Packet's size (1400 - by default)
- **ping_n** - Number of packets sent (10 - by default)
### IPERF
- **iperf_c** - Server's IP (192.168.0.2 - by default)
- **iperf_p** - Threads number (50 - by default)
- **iperf_t** - Connection time (300 - by default)

## Example
```sh
AstraTesting --ping_ip="ya.ru" --ping_n=10 --ping_i=1 --iperf_t=1
```
