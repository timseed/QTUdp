# UDP Broardcast

I was having some issues finding a Network device inside my network. Unsure of how the UDP broardcast should be working, I thought it was a good oppertunity to make sure I have got this correctly understood in my head, 


# Project 

There are 3 QT Projects - which seems rather excessive, but... there is some logic to my madness (I hope).

  - Library
   - Create a central Shared library. PLace all the real code in there.
  - Server
    - Uses the Library
  - Client
    - Also Uses the Library


## Ports/Data

There are amazingly simple methods to change this in Client/Server.

## Process Start order

There is None. The Client simply listens on the broardcast port... if there is no Server - there is no-data, the client still listens.

When the server starts, then the client will read and output the datagram.


# Issues

On the Mac, the command

    make install
  
Fails, as the **/usr/local/lib/** is protected (Despite chmod, and addgrp etc) - so this need a slight push of

    sudo make install 
    

## Dev Env

This was developed using

   - QT 6.3
   - Mac M1

I am however un-aware of any Hardware/Software specific calls which should limit this codes functionality on other HW/OS.