<B>Repository for files related to BM83 boards by BurgessWorld Custom Electronics</B>

Upload one of the example CONFIG HEX files, depending on your output configuration along with the DSP and GFP firmware files to configure the BM83 board.

Download the IS2083_TurnKey_1.2.0 zip file from the Microchip website:  https://ww1.microchip.com/downloads/en/DeviceDoc/IS2083_Turnkey_1.2.0.zip
Unzip the Turnkeu files into a folder

Download the CONFIG HEX files, DSP, and GFP firmware files into a folder

<B>TO UPDATE FIRMWARE AND CONFIG VIA NATIVE USB:</B>
<ul>
<li>Connect a USB-breakout board as shown in the configuration image from the configuration subfolder
<li>Connect a USB cable to your computer
<li>Open the USB isupdate.exe tool located in the IS2083_Turnkey_1.2.0 \package IS2083 Turnkey_1.2.0\Tools\isupdate\
<li>Make sure USB HID is shown in the Port selection and click the CONNECT button.  You will get a connect indication in the window below
<li>Set image num to 3
<li>Click the top BROWSE button next to the field marked Images
<li>Select a CONFIG HEX file along with the DPS and GFP firmware HEX files (total of 3 files selected) and click open
<li>Click the UPDATE button next to the BROWSE button
<li>When prompted, select yes or no to retain connected devices list or to discard
<li>Once the update is completed, click DISCONNECT
<li>The firmware update is complete
</ul>
  
<B>TO TO UPDATE FIRMWARE VIA USB-SERIAL ADAPTER:</B>
<ul>
<li>Connect a USB-serial adapter board as shown in the configuration image from the configuration subfolder.
<li>Connect a USB cable to your computer.
<li>On the BM83 board, place jumper at JP4 (TEST) and click the RESET button.  The blue LED will light up to indicate TEST mode is active
<li>Open the USB isupdate.exe tool located in the IS2083_Turnkey_1.2.0 \package IS2083 Turnkey_1.2.0\Tools\isupdate\
<li>Select the USB port of your USB-Seria adapter in Port selection and click the CONNECT button.  You will get a connect indication in the window below
<li>Set image num to 3
<li>Click the top BROWSE button next to the field marked Images
<li>Select a CONFIG HEX file along with the DPS and GFP firmware HEX files (total of 3 files selected) and click open
<li>Click the UPDATE button next to the BROWSE button
<li>When prompted, select yes or no to retain connected devices list or to discard
<li>Once the update is completed, click DISCONNECT
<li>Remove the jumper at JP4 (TEST) and click the reset button to run the new firmware
<li>The firmware update is complete
</ul>

<B>Design Considerations</B>
<ul>
<li>Keep wires short when connecting I2S devices<br>
I2S is susceptable to interferrance when using long wires.  Keep your connections as short as possible and you may have to seperate the wires or use shielded wires to prevent interferrence.  If you are experiencing cracling/static/hum in the output of an I2S DAC, it might be because of the wires.
</ul>
