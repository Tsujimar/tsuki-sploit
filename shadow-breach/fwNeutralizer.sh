#!/bin/bash

wf_service="mpssvc"
bash_path="C:\\Windows\\System32\\bash"
$bash_path -c "sc config $wf_service start=disabled && exit"