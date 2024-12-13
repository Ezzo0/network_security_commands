# SSH (1st Lab)
- Change the name of a router or switch: 
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
RTA(config)# username ANY_USER privilege [15] secret ANY_PASSWORD
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
# OSPF (2nd Lab)
- Configure OSPF MD5 authentication for all the routers in an area.
```
R1(config)# router ospf 1
R1(config-router)# area 0 authentication message-digest
```
- Configure the MD5 key for all the routers in an area (**Note that** interface port is the one that is connected with the other router).
```
R1(config)# interface g0/0/0
R1(config-if)# ip ospf message-digest-key 1 md5 MD5pa55
```
# NTP (2nd Lab)
- Check the current NTP and clock settings.
```
R1# show ntp status
R1# show clock detail
```
- Configure R1 and R2 as NTP Clients. Use the ntp server command to specify an NTP server.
```
R1(config)# ntp server 209.165.200.225
```
# Syslog (2nd Lab)
- Send log events to the Syslog server ( `10.0.1.254` is syslog server ip).
```
R1(config)# logging 10.0.1.254
```
- Set the clock manually.
```
S1# clock set 11:47:00 July 10 2013
```
- Send timestamp with logs it sends to the Syslog server via the established SSH session.
```
S1(config)# service timestamps log datetime msec
```
# AAA (3rd Lab)
- Enable AAA services
```
R(config)# aaa new-model
```
##### Local AAA Authentication
- Specify the list name and the order to use.
```
R(config)# aaa authentication login LIST_NAME local group radius group tacacs+ local-case
```
##### Server-Based AAA Authentication
- Configure TACACS+ server
```
R(config)# tacacs server TAC_SERVER
R(config-server-tacacs)# address ipv4 192.168.1.101
R(config-server-tacacs)# single-connection
R(config-server-tacacs)# key TACACS-pa55w0rd
R(config-server-tacacs)# exit
```
- Configure RADIUS server
```
R(config)# radius server RAD_SERVER
R(config-radius-server)# address ipv4 192.168.1.100 auth-port 1812 acct-port 1813
R(config-radius-server)# key RADIUS-pa55w0rd
R(config-radius-server)# exit
```
- Apply TACACS+ authentication
```
R(config)# aaa authentication login TAC_SERVER group tacacs+ group radius local local-case
```
- Apply Radius authentication
```
R(config)# aaa authentication login RAD_SERVER group radius group tacacs+ local local-case
```
- Apply Authentication on Console Line
```
R(config)# line console 0
R(config-line)# login authentication LIST_NAME
```
- Apply Authentication on VTY Line (don the same previous steps in lab 1 for configuring ssh)
```
R(config)# line vty 0 4
R(config-line)# transport input ssh
R(config-line)# login authentication LIST_NAME
```
- Lock user accounts after failed attempts
```
R(config)# aaa local authentication attempts max-fail [NUMBER]
```
- Lock user account
```
R(config)# clear aaa local user lockout
```
# ACL (4th Lab)
- 