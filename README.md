# NXP Internship (`19.05.25` - `30.05.25`)

done mostly on the issued laptop (Latitude 5420 with the i5-1145G7 & 16 GB RAM) running (sadly) Windows 11, but as i noted in the text below, it _should_ work on Ubuntu with some small hurdles as well, tho it's probably best to verify this beforehand.

## """my""" project

0. prerequisites:
  - NXP's MCUXpresso IDE with all the recommended demo apps for the FRDM-K64F board, note that this only works natively on Ubuntu, i couldn't get the unofficial (& outdated) [flatpak](https://github.com/tinywrkb/flatpaks/tree/master/com.nxp.mcuxpressoide) to work on openSUSE Tumbleweed, because one of the files is no longer available, and i couldn't make it work with the recommended [extra-data caching method](https://github.com/tinywrkb/flatpaks?tab=readme-ov-file#extra-data-caching-and-avoiding-download), because of different versions & different checksums; i used Ubuntu 24.04 LTS
  - Termite RS232 3.4 (program only) with baud rate 115200 and the correct COM port (trial and error)
1. set up the .mex file (in MCUX: ConfigTools > Pins) and add all of the pins from the schematic; this is already done in this repo via the recommended .mex file sent to us - just note that it also includes a lot more other bs, which needed me to install 4 additional drivers (RMB the project folder in the Project Explorer > SDK Management > Manage SDK Components > Drivers > and here i had to select adc16, i2c, pit, and rtc)

## my thoughts (who asked?) on the internship

- the NXP corporate environment was very pleasant - and that includes people exploding head emoji

- the instructor was very likable and seemed very chill and passionate about things he cared about

- but clearly wasn't prepared enough for all the weird edge cases we could hit (which is understandable to some degree, but i also feel like we spent like 10 hours just making it "work" and installing everything) - this could be improved by sending us the required programs we will need with an up-to-date documentation on how to install them, with the clarification that we would look at the issues as the first thing at the internship

- wanted to explain GitHub to us without actually stuff beforehand, and even if that resulted in greated student participation, it also made us run into a ton of issues (thanks GitHub Desktop... for nothing)

- was very, _very_, fast at "explaining", or more accurately, explained stuff in a way, that only made sense if you already knew about it, which doesn't really benefit anyone; i would love if he tried to clarify things (especially the HW related things!) in an ELI5 way, rather than in a "what's up fellow PhD. coworker" way