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

<B>Editing BM83 Configuration</B>
<ul>
<li>The IS2083_Turnkey_1.2.0.zip archive contains a configuration editor tool located in the \tools\Config Tool\ folder.  This tool can be used to create custom configurations for the BM83 module.<br>
<li>Using the tool, open the default configuration file or one of the pre-configured files to make changes to the behavoir of the BM83.
<li>Referrence the documents found on the Microchip website when configuring BM83 options:  https://www.microchip.com/wwwproducts/en/BM83
<li>Save the configuration when you are done and then upload it to the BM83 using one of the methods described above.
</ul>

<B>Design Considerations</B>
<ul>
<li>Keep wires short when connecting I2S devices<br>
I2S is susceptable to interferrance when using long wires.  Keep your connections as short as possible and you may have to seperate the wires or use shielded wires to prevent interferrence.  If you are experiencing cracling/static/hum in the output of an I2S DAC, it might be because of the wires.
<li>Consider your power source when selecting an amplifier<br>
If powering your amplifier from the BATT OUT connection, keep in mind that the MAX output current is 2A.  Attempting to power a high-power amp from this connection could result in damage to the board.<br>
Also consider that the voltage at BATT OUT is the battery voltage which is <4.2v and typically between 3.4-3.9V.  Ensure that any device you power from this connector can work from that voltage.
<li>Match your amplifier and speakers to your project<br>
A small amplifier like the one linked here:  https://www.amazon.com/gp/product/B081YSYGLS/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1  is good for powering 3-5W speakers.  If can also be powered by the BATT OUT connector and provides a nice volume level.<br>
<li>You don't need a big LiPo battery<br>
The BM83 is extrememly energy-efficient.  Most of your power usage will go into the amplifier so keep it small if yo are going portable.  I use a 500mah battery in my 5W+5W portable speaker and it can last 10+ hours and charges quickly.
<li>Avoid ground loops in your audio circuit<br>
Powering an amplifier and the BM83 from the same power source can introduce ground loops, resulting in a HUM in the audio output.  Keep audio grounds separate from the digital ground of the BM83 board if possible.<br>
When using speakers without an amplifier in capless mode, the speaker gnd connections both go to the AOHPM pin, not the board ground.<br>
When using an amplifier, the gnd pin of the amplifier connects to one of the gnd pins on the BM83 board and should provide an analog ground for the speakers.
<li>If using an amplifier without an external DAC, select one with a shutdown or mute function<br>
To avoid popping or static in audio output when powering up and shutting down the BM83, use an amplifier with a shutdown or mute pin and connect it to pin P26.  Closing the solder jumper on the bottom of the BM83 Breakout board connects P26 to gnd via a resistor, provding pull-down.  This pin can be toggled on in the config when the MB83 starts up, avoiding audio noise.  This can cut off the startup and shutdown tones somewhat, so it is a tradoff.  If your amplifier has a built-in pulldown, don't close the solder jumper.
<li>Consider using an external I2S DAC for clean audio output<br>
External I2S DACs can be had for a few dollars and are easily connected via 3-4 wires to the I2S pins of the BM83 Breakout Board.  This will provide the cleanest audio signal but will likely also require an external amplifier unless you buy one with an amplifier built-in.
Using an external I2S DAC is almost a requirement when using the multispeaker functionality of the BM83 to chain multiple speakers via BLE to avoid introducing digital noise in the audio output<br>
This I2S DAC is ready to go out of the box and has been tested with the BM83 Breakout Board.  It is also supported by the I2S CONFIG HEX file so it is easy to setup:  https://www.amazon.com/gp/product/B0781D3VQB/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1<br><p>
<B>I don't recommend using this I2S DAC:</B>  https://www.amazon.com/gp/product/B07W97D2YC/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1.  It needs to be configured vis solder jumpers prior to use and can destroy your BM83.  There are hookup guides online that tell you to ground the SCK pin to put it into slave mode - DO NOT DO THIS AS IT WILL SHORT THE BM83 AND DESTROY IT.  If you decided to use this DAC, ONLY CONNECT THE BCK, DIN, and LCK pins.  You will also need to close the solder jumpers on the back of the module:  2=L, 1=L, 4=L, 3=H.  DO NOT SHORT SCK TO GROUND.<br><p>
<li>Using the Microchip Bluetooth Audio App<br>
Ensure location services are enabled on your phone and the application has permission to use it or you will not be able to locate speakers.<br>
If you have trouble locating speakers in the app, try setting the speaker to Master mode in the configuration.<br>
The application is included in the Turnkey software bundle for side-loading on devices that can't install it from the app store.<br>
</ul>
