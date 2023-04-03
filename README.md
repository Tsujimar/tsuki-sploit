# tsuki-sploit [EDUCATIONAL PURPOSES ONLY]
A full CLI tool for penetration testing, and exploit related tools.

# current folder structure and definitions
^tsuki-sploit:<br>
    ^phantom-intrusion <br>
		^keystroke-listener (detect where use at and log based on current window location(login browser) and log)<br>
			./initiator (waits for active windows of login portals/chat boxes)<br>
			./main (starts the keystroke listener and pushes data [active window + text]to a db)<br>
		^browser-watch (cookes, sessions, history active listener)<br>
			./initiator (starts a count so every 24 it calls the main file, if db already exists it checks to duplicates, if no duplicates found it will auto update em)<br>
			./main (once called, it collect all the data [passed from initiator] and pushes to db)<br>
		>user-harvest (hardware/device user info)<br>
		>fs-scrape (files and folders)<br>
		>network-info (sens netw data)<br>
		>infect-await (worm based on device-plug/inject self with message such as (email/chat windows...) + delete footprint)<br>
	^shadow-breach<br>
		./avDisruptor<br>
		./fwNeutralizer<br>
	./darkEngine<br>
	./gitignore<br>
	./LICENCE<br>
	./README.md<br>
