#!/bin/bash
og_path="D:/tsuki-sploit/"
origin_path_encode=("$og_path/phantom-intrusion" "$og_path/shadow-breach" "$og_path/darkEngine" "$og_path/launch-with-admin.bat") # "$og_path/autorun.inf"
for source in "${origin_path_encode[@]}"
do
  random_enc_src=$(openssl rand -hex 4)
  tar -cz "$source" | base64 > "${random_enc_src}_encoded.tar.b64"
done