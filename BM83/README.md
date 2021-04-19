Repository for files related to BM83 boards by BurgessWorld Custom Electronics

Upload one of the example CONFIG HEX files, depending on your output configuration along with the DSP and GFP firmware files to configure the BM83 board.

Download the IS2083_TurnKey_1.2.0 zip file from the Microchip website:  https://ww1.microchip.com/downloads/en/DeviceDoc/IS2083_Turnkey_1.2.0.zip
Unzip the Turnkeu files into a folder
Download the CONFIG HEX files, DSP, and GFP firmware files into a folder

TO upload firmware and config via USB:

  Connect a USB-breakout board as shown in the configuration image from the configuration subfolder.
  
  Connect a USB cable to your computer.
  
  Open the USB isupdate.exe tool located in the IS2083_Turnkey_1.2.0 \package IS2083 Turnkey_1.2.0\Tools\isupdate\
  
  Make sure USB HID is shown in the Port selection and click the CONNECT button.  You will get a connect indication in the window below
  
  Set image num to 3
  
  Click the top BROWSE button next to the field marked Images
  
  Select a CONFIG HEX file along with the DPS and GFP firmware HEX files (total of 3 files selected) and click open
  
  Click the UPDATE button next to the BROWSE button
  
  When prompted, select yes or no to retain connected devices list or to discard
  
  Once the update is completed, click DISCONNECT
  
  The firmware update is complete
  
  
TO upload firmware and config via USB-Serial:

  Connect a USB-serial adapter board as shown in the configuration image from the configuration subfolder.
  
  Connect a USB cable to your computer.
  
  On the BM83 board, place jumper at JP4 (TEST) and click the RESET button.  The blue LED will light up to indicate TEST mode is active
  
  Open the USB isupdate.exe tool located in the IS2083_Turnkey_1.2.0 \package IS2083 Turnkey_1.2.0\Tools\isupdate\
  
  Select the USB port of your USB-Seria adapter in Port selection and click the CONNECT button.  You will get a connect indication in the window below
  
  Set image num to 3
  
  Click the top BROWSE button next to the field marked Images
  
  Select a CONFIG HEX file along with the DPS and GFP firmware HEX files (total of 3 files selected) and click open
  
  Click the UPDATE button next to the BROWSE button
  
  When prompted, select yes or no to retain connected devices list or to discard
  
  Once the update is completed, click DISCONNECT
  
  Remove the jumper at JP4 (TEST) and click the reset button to run the new firmware
  
  The firmware update is complete
