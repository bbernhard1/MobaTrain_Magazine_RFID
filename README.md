# MobaTrain Depot with RFID
This is a iTrain support project which can detect train showcase tubes by RFID stickers. Then forward the information to iTrain. <br>
Inside iTrain the information is used to set the train magazine object to the correct position and enable/disabe the assigend block. <br>

To read RFID stickes a RC522 based Arduino sheeld with a Arduino based uC board is used. My example uses a Arduino mega, but for sure a Uno or Micro board will do the job as well. <br>
A problem is that iTrain do not offer a API or other option to receive information from 3rd party hardware. Therefore can only use dummy feedbacks and missuse them as interface.
Means once the RFID is decoded the Arduino triggers a PIO pin which is connected to a feedback which is assigend to that tube.
Then inside iTrain the feedback triggers a action which does the block enable/disable stuff. 


