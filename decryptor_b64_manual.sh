#!/bin/bash
og_path="D:/tsuki-sploit/*"
for source in $og_path/.b64
do
  base64 -d "$source" | tar -xz
done