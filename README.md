# SSH (first lab)
- Change the name of a router: 
```
Router(config)# hostname RTA
RTA(config)#
```
- Configure IP addressing on RTA and enable an interface:
```
RTA(config)# interface g0/0/0 
RTA(config-if)# ip address 192.168.1.1 255.255.255.0
RTA(config-if)# no shutdown
```
- Encrypt all plaintext passwords.
```
RTA(config)# service password-encryption
```
-   Set the minimum password length to 10.
```
RTA(config)# security passwords min-length 10
```
- Set password for `enable`
```
RTA(config)# enable secret any_password
```
- Disable DNS lookup.
```
RTA(config)# no ip domain-lookup
```
- Set the domain name to netsec.com (case-sensitive for scoring in PT).
```
RTA(config)# ip domain-name netsec.com
```
-   Create a user of your choosing with a strong encrypted password.
```
RTA(config)# username any_user secret any_password
```
- Generate 1024-bit RSA keys.
```
RTA(config)# crypto key generate rsa
```
-  Block anyone for three minutes who fails to log in after four attempts within a two-minute period.
```
RTA(config)# login block-for 180 attempts 4 within 120
```
- Configure all VTY lines for SSH access and use the local user profiles for authentication (5 people can connect - maximum number of connections is 16).
```
RTA(config)# line vty 0 4
RTA(config-line)# transport input ssh
RTA(config-line)# login local
```
- Set the EXEC mode timeout to 6 minutes on the VTY lines.
```
RTA(config-line)# exec-timeout 6
```
- Save the configuration to NVRAM.
```
RTA# wr
```
- Connecting router from pc via ssh.
```
c:\> ssh -l user ip
```
- Set IP of a switch.
```
Switch(config)# interface vlan
Switch(config-if)# ip address 192.168.1.1 255.255.255.0
Switch(config-if)# no shutdown
```
- Making modifications to several ports at once.
```
SW1(config)# interface range F0/2-24, G0/2
SW1(config-if-range)# shutdown 
```
