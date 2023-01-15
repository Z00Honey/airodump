sudo ifconfig wlx588694f3aca6 down
sudo ip link set wlx588694f3aca6 name mon0
sudo iwconfig mon0 mode monitor
sudo ifconfig mon0 up
iwconfig
