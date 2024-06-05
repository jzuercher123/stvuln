# STVuln (ScanToVuln)


## Project Description: 
This program lets you simply type in a host or ip address and from one command, 
both scan the ports and also find *working* exploits from exploitdb for the given services.


### Dependencies:
- Nmap (https://nmap.org/download)
- Searchsploit (https://www.exploit-db.com/searchsploit)
- A terminal or command line


### Install:

clone repository
```bash
    git clone https://github.com/jzuercher123/stvuln
```
open repository in terminal
```bash
    cd stvuln
```
(for linux users) given executable permissions to the main exe file (stvuln)
```bash
    chmod +x stvuln
```


### Usage
```bash
./stvuln <domain or ip> <flags> -sV 
```
