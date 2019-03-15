---
layout: default
permalink: /server
---



# Installing Raspbian

Please consult an [outside source](https://www.raspberrypi.org/documentation/installation/installing-images/). Much has already been written about installing raspbian onto an sd card for use with raspberry pis. This process is called 'flashing' because you're writing onto a flash chip. Please note that you must complete the next section before you eject the SD card.

# Before you eject the sd card

Once you have your sd card with raspbian, open the sd card in the file explorer and add a file called 'wpa_supplicant.conf'. Copy and paste the following into it.
```
country=US
ctrl_interface=DIR=/var/run/wpa_supplicant 
network={
	ssid="MyWiFiNetwork"
	psk="aVeryStrongPassword"
	key_mgmt=WPA-PSK
}
```

Additionally, create a blank file called 'ssh' (with no file extension) so that you can access the device remotely and without a keyboard and monitor.

Next, go to the ```/boot/config.txt``` files and add this to the bottom:
```
dtoverlay=dwc2
```
Finally, open the ```cmdline.txt```  Each parameter is seperated by a single space, and it does not use newlines. Insert modules-load=dwc2,g_ether after rootwait.

Then, if you are on Windows install PuTTY. It allows you to talk to Unix/Linux computers. Once that is installed, you should be able to ssh into the hostname 'raspberry pi' using port '22' and the ssh protocol. The command is:

[Source](https://gist.github.com/gbaman/975e2db164b3ca2b51ae11e45e8fd40a)
 
# Connecting and First Time Setup

```
ssh pi@raspberrypi
```
Once you login with the default password of 'raspberry,' run

```
sudo raspi-config
```

This command runs a utility for configuring raspberry pis. The sudo part means you want to do it as administrator. On Linux, the administrator account is called 'root' or 'superuser'. ```sudo``` means 'do as superuser' or 'SuperUserDO'. First, change your root password. Then, change your hostname. In the advanced configuration menu, set the memory allocation to 256, expand the filesystem, and change the resolution to 1024 * 768.  

Reboot.

Once you've connected again, we're going to install some software. Here we'll use aptitude to install software. On Linux, there are a variety of ways to install software. This is the most reliable way for raspbian, the flavor of linux that our raspberry pi runs. The command is



```
sudo apt-get install ufw
```

That installs a firewall and below sets it up. Ports allow your computer to send traffic to individual applications. Please google these ports to see what each one is for.

```
sudo ufw default deny incoming
sudo ufw allow 80
sudo ufw allow 8080
sudo ufw allow 443
sudo ufw allow 587
sudo ufw allow 22
```

[Source](https://slippytrumpet.io/posts/raspberry-pi-zero-w-setup/)

Now that our pi is all set up, it's about time for a break. On linux, you have to update most software manually. It's a good idea to do the below before attempting to install anything using the ```apt``` command.

```
sudo apt update
sudo apt upgrade
sudo apt dist-upgrade
```

# Networking

Disable power management:
```
sudo touch /etc/pm/sleep.d/60_wpa_supplicant
sudo chmod 644 /etc/pm/sleep.d/60_wpa_supplicant # Instructions said no exec flag
```
Install dnsmasq, hostapd

```
sudo apt install dnsmasq hostapd
```

TODO: This section needs to be fleshed out

[Source](https://blog.thewalr.us/2017/09/26/raspberry-pi-zero-w-simultaneous-ap-and-managed-mode-wifi/)
===============================
This path
```
/etc/udev/rules.d/70-persistent-net.rules
```
The content
```
SUBSYSTEM=="ieee80211", ACTION=="add|change", ATTR{macaddress}=="b8:27:eb:ff:ff:ff", KERNEL=="phy0", $phy0 \
  RUN+="/sbin/iw phy phy0 interface add ap0 type __ap", \
  RUN+="/bin/ip link set ap0 address b8:27:eb:ff:ff:ff"
```
===============================
This path
```
/etc/dnsmasq.conf
```
The content
```
interface=lo,ap0
no-dhcp-interface=lo,wlan0
bind-interfaces
server=8.8.8.8
domain-needed
bogus-priv
dhcp-range=192.168.51.0,192.168.51.255,12h
```
===============================
This path
```
/etc/hostapd/hostapd.conf
```
The content
```
ctrl_interface=/var/run/hostapd
ctrl_interface_group=0
interface=ap0
driver=nl80211
ssid=sparks-net
channel=auto
wmm_enabled=0
macaddr_acl=0
auth_algs=1
wpa=2
wpa_passphrase=sciencerules!
wpa_key_mgmt=WPA-PSK
ignore_broadcast_ssid = 0
wpa_pairwise=TKIP CCMP
rsn_pairwise=CCMP
```
===============================
This path
```
/etc/default/hostapd
```
The content
```
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```
===============================

This path
```
/etc/wpa_supplicant/wpa_supplicant.conf
```
The content
```
country=US
ctrl_interface=DIR=/var/run/wpa_supplicant #GROUP=netdev
update_config=1

network={
    ssid="YourSSID1"
    psk="YourPassphrase1"
}
```

===============================

This path
```
/etc/network/interfaces
```
The content
```
# interfaces(5) file used by ifup(8) and ifdown(8)

# Please note that this file is written to be used with dhcpcd
# For static IP, consult /etc/dhcpcd.conf and 'man dhcpcd.conf'

# Include files from /etc/network/interfaces.d:
source-directory /etc/network/interfaces.d

auto lo
auto ap0
auto wlan0
iface lo inet loopback

allow-hotplug ap0
allow-hotplug wlan0


iface wlan0 inet dhcp
wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf

iface ap0 inet static
    address 192.168.51.1
    netmask 255.255.255.0
    hostapd /etc/hostapd/hostapd.conf

#next lines turns off wireless radio power management
#wireless-power off
```
===============================

--Routing?--

This section is deprecated.

```
$ sudo sysctl -w net.ipv4.ip_forward=1
$ sudo iptables -t nat -A POSTROUTING -s 192.168.50.0/24 ! -d 192.168.50.0/24 -j MASQUERADE
$ sudo systemctl restart dnsmasq
```

===============================

Janky Script

This section is deprecated

```
pi@raspberrypi:~$ cat ./start-ap-managed-wifi.sh
#!/bin/bash
sleep 30
sudo ifdown --force wlan0 && sudo ifdown --force ap0 && sudo ifup ap0 && sudo ifup wlan0
sudo sysctl -w net.ipv4.ip_forward=1
sudo iptables -t nat -A POSTROUTING -s 192.168.10.0/24 ! -d 192.168.10.0/24 -j MASQUERADE
sudo systemctl restart dnsmasq

sudo crontab -e

@reboot /home/pi/start-ap-managed-wifi.sh
```
