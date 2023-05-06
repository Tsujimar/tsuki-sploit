#!/bin/bash

if [[ "${0:0:2}" == "/D" || "${0:0:2}" == "/d" ]]; then
  :
  else
    ./main.exe
fi