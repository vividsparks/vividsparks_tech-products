Running RacEr Examples on the PYNQ-Z2 Board

This guide describes how to run the RacEr sample applications on a PYNQ-Z2 development board.

1. Clone the Repository

Clone the RacEr example repository and navigate to the RacEr directory.

git clone https://github.com/vividsparks/vividsparks_tech.git
cd VividSparks-Products/cosim/RacEr-example/RacEr

2. Prepare the PYNQ-Z2 Board

Download the PYNQ 2.6 image and write it to an SD card: 
https://drive.google.com/file/d/1td0gJX4mvQTDALvSikxMVPfiG8jsaBgm/view


Insert the SD card into the PYNQ-Z2 board and boot the board.

Connect the PYNQ-Z2 board to the Internet. For instructions on setting up the board and connecting it to a network, refer to the PYNQ-Z2 setup documentation:

https://pynq.readthedocs.io/en/v2.3/getting_started/pynq_z2_setup.html

3. Connect to the Board via SSH

Once the board is connected to the network, determine its IP address and connect to it using SSH.

For example:

ssh xilinx@x.x.x.x


When prompted for the password, enter:

xilinx

4. Load the RacEr Bitstream

Navigate to the RacEr example directory:

cd /VividSparks-Products/cosim/RacEr-example/RacEr


Load the RacEr bitstream by running:

make load_bitstream


Loading the bitstream may take approximately one minute.

5. Run the Sample Application

After the bitstream has been loaded successfully, run the sample application:

make run


You should see the RacEr sample application running on the PYNQ-Z2 board.

6. Precompiled Sample Applications

The RacEr IP core is shipped with several sample applications that have been precompiled into .nbf files.

These applications are located in:

VividSparks-Products/cosim/RacEr-example/RacEr


The corresponding source code for these applications is available in:

VividSparks-Products/import/RacEr_manycore/software/spmd

7. Selecting a Different Sample Application

To run a different sample application, modify the NBF_FILE variable in:

VividSparks-Products/cosim/RacEr-example/Makefile.design


Specifically, update line 52:

NBF_FILE ?= <application.nbf>


Specify the desired .nbf application file and then run the appropriate build/run commands.
