# SSH (1st Lab)
- Change the name of a router or switch: 
```
Router(config)# hostname RTA
RTA(config)#
```
- Configure IP addressing on RTA and enable an interface:
```
RTA(config)# interface g0/0/0 
RTA(config-if)# ip address [IPAddress] [subnetMask]
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
RTA(config)# enable secret [any_password]
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
RTA(config)# username [ANY_USER] privilege [15] secret [ANY_PASSWORD]
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
Switch(config-if)# ip address [IPAddress] [subnetMask]
Switch(config-if)# no shutdown
```
- Making modifications to several ports at once.
```
SW1(config)# interface range F0/2-24, G0/2-4
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
R1(config-if)# ip ospf message-digest-key 1 md5 [key]
```
# NTP (2nd Lab)
- Check the current NTP and clock settings.
```
R1# show ntp status
R1# show clock detail
```
- Configure R1 and R2 as NTP Clients. Use the ntp server command to specify an NTP server.
```
R1(config)# ntp server [NTPServerIP]
```
# Syslog (2nd Lab)
- Send log events to the Syslog server
```
R1(config)# logging [syslogServerIP]
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
### Local AAA Authentication
- Specify the list name and the order to use.
```
R(config)# aaa authentication login [LIST_NAME] local group radius group tacacs+ local-case
```
### Server-Based AAA Authentication
- Configure TACACS+ server
```
R(config)# tacacs server TAC_SERVER
R(config-server-tacacs)# address ipv4 [tacacsServerIP]
R(config-server-tacacs)# single-connection
R(config-server-tacacs)# key TACACS-pa55w0rd
R(config-server-tacacs)# exit
```
- Configure RADIUS server
```
R(config)# radius server RAD_SERVER
R(config-radius-server)# address ipv4 [radiusServerIP] auth-port 1812 acct-port 1813
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
R(config-line)# login authentication [LIST_NAME]
```
- Apply Authentication on VTY Line (don the same previous steps in lab 1 for configuring ssh)
```
R(config)# line vty 0 4
R(config-line)# transport input ssh
R(config-line)# login authentication [LIST_NAME]
```
- Lock user accounts after number of failed attempts
```
R(config)# aaa local authentication attempts max-fail [NUMBER]
```
- Unlock user account
```
R(config)# clear aaa local user lockout
```
# ACL (4th Lab)
- To view the current ACLs
```
R1# show access-lists

OR

R1# show run | include interface | access
```
- Remove an ACL from a router (`no access-list` command without arguments deletes all ACLs)
```
R1(config)# no access-list 11
```
- Removing an ACL from a router **doesn't** Remove ACL on an interface, so to Remove from an interface use the following: (`no access-list` command without arguments deletes all ACLs)
```
R1(config)# interface s0/0/0
R1(config-if)# no ip access-group 11 out
```
### Numbered Standard ACL
-  Create an ACL
```
R(config)# access-list [ACLNumber] deny||permit [sourceIP] [WildcardMask]
```
- Allow a specific device with IP address 192.168.1.10:
```
R(config)# access-list 10 permit 192.168.1.10 0.0.0.255
```
- Apply the ACL to an interface:
```
R(config)# interface g0/0/0
R(config-if)# ip access-group [ACLNumber] in||out
```
### Named Standard ACL 
- Configure a named standard ACL (Note that `host` keyword is an alternative for `WildcardMask`)
```
R1(config)# ip access-list standard [ACLName]
R1(config-std-nacl)# permit host [sourceIP]
R1(config-std-nacl)# deny host [sourceIP]
R1(config-std-nacl)# deny any
R1(config-std-nacl)# exit
```
- Apply the ACL outbound on an interface
```
R1(config)# interface f0/1
R1(config-if)# ip access-group [ACLName] in||out
```
### Numbered Extended ACL
-  Create an ACL && Permit or deny specific source and destination ips
```
R(config)# access-list [ACLNumber] permit||deny [protocol] [sourceIP] [wildcardMask] [destinationIP] [wildcardMask] eq [portNumber]
R(config)# access-list permit||deny any any
```
- Protocols are:
	- `ahp` Authentication Header Protocol
	- `eigrp` Cisco's EIGRP routing protocol
	- `esp` Encapsulation Security Payload
	- `gre` Cisco's GRE tunneling
	- `icmp` Internet Control Message Protocol
	- `ip` Any Internet Protocol
	- `ospf` OSPF routing protocol
	- `tcp` Transmission Control Protocol
	- `udp` User Datagram Protocol
- Ports are:
	- `<0-65535>` Port number
	- `ftp` File Transfer Protocol (21)
	- `pop3` Post Office Protocol v3 (110)
	- `smtp` Simple Mail Transport Protocol (25)
	- `telnet` Telnet (23)
	- `www` World Wide Web (HTTP, 80)
	- `https` HTTPS
- Apply ACL to an interface
```
R(config)# interface g0/0/0
R(config-if)# ip access-group [ACLNumber] in||out
```
### Named Extended ACL
- Configure named extended ACLs
```
R(config)# ip access-list extended [ACLName]
```
- Permit or deny specific source and destination ips
```
R(config-ext-nacl)# permit||deny [protocol] [sourceIP] [wildcardMask] [destinationIP] [wildcardMask] eq [portNumber]
```
- Apply ACL to an interface
```
R(config)# interface g0/0/0
R(config-if)# ip access-group [ACLName] in||out
```
