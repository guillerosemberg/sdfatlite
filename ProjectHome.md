This project improves the "FAT Lite" library developed by Freescale and published in the DEMOFLEXISJMSD\_DataLogger\_V2 example. SDFatLite is an Freescale library that supports FAT16 file systems on standard and high capacity SD cards.

Characteristics:

- Only supports short 8.3 file names, but doesn't crash if there are long file names the card.

- Supports file creation, deletion, read, write and overwrite.

- Doesn't supports access to subdirectories, creation, and deletion of subdirectories (can only deal with files in the root/home directory).

- It is designed for 8/32 bits (ColdFire v1) Freescale MCUs.

Use of SDFatLite is illustrated by the example provided in the SDFatLite/examples directory, made for the Freescale MCF51JM128 MCU.