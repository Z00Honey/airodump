# My-airodump
airodump의 일부 기능 구현
<br><br>
## Implementation
Point : 구조체를 활용하여 데이터를 쉽게 다루자!
<br><br>
#### (1) Radiotap 구조체
~~Power(신호세기) 추출~~

#### (2) Beacon frame 구조체
Beacon frame Check  
BSSID 추출

#### (3) ESSID 구조체
ESSID 추출  
<br><br>  

## Testing
[gilgil's Tcpreplay](https://github.com/snoopspy/g)
: Ubuntu 20.04에서 안 됨 (Trouble Shooting Fail)

[bittwist](https://bittwist.sourceforge.net/)
: Similar Tcpreplay Program

    sudo bittwist -v -i <interface> <pcap_file>
<br><br>

## Result

- airodump
![image](https://user-images.githubusercontent.com/80230097/211672517-3ad1c351-8bc1-46aa-bdb9-768a34be3f0d.png)

- my-airodump
![image](https://user-images.githubusercontent.com/80230097/211672856-a1df8d0e-a4af-4a5d-8606-9c12255f14a8.png)
<br><br>

## Reference
[Tcpreplay similar Program](https://kthan.tistory.com/33)  
[IEEE 802.11 C Source](https://libtins.github.io/docs/latest/d8/de9/structTins_1_1Dot11_1_1dot11__header.html)
