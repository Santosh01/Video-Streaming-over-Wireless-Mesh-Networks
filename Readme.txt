********************************************************************************
*				    Project On                                    *
*				    ==========                                    *
*   Performance Evaluation of Video Streaming in Multihop Wireless Mesh Networks  *
*      			    Author : Santosh Kumar dubey                          *
*				Person # 5009 7059                                *
*			      Date : 16th - May - 2014                            *
********************************************************************************

			+++++++++++++++++++++++++++++++++++++++++++++++++
			+	Readme File contains :			+
			+	======================			+
			+		-> System Requirements		+
			+               -> Compilation of the program	+
			+               -> Step to run the project	+
			+               -> Streaming videos		+
			+++++++++++++++++++++++++++++++++++++++++++++++++

1> System Requirements :
   ====================
   i) Any operating system to run this project.
   ii) Vlc player which will be used as wireless device for streaming purpose.
   iii) GCC to compile the project source code (C).
   iv) Any video which will be used for the streaming.
			
2> Compilation of the program :
   ==========================
   i) You need GCC to run this project.
   ii) The 'Makefile' have been created in order to compile project code.
   iii) You need to type " Make all" or "Make" (without quote) this will create compile and create and object file.
   you can see this process "gcc -o stream_general stream_general.c -lpthread"
   iv) In order to clean the object file you only need to type "Make clean".
3> Step to run this project :
   ========================
				
    i) Let's start with the VLC player first , 
    This player is our wireless device and it is getting all the data from the server but in 
    order to get the data and successfully play into VLC we need to connect it with our server, in order to do that 
    we need to go to the menu of the VLC -> Select “Open Network Stream” -> type “udp://@:8000” -> hit "play" , Now
    our UDP socket is open.
    8000 is the port number on which your server listening and sending the data you need to connect on this port, 
    similarly we can connect any number of VLC with our server and those connected player can receive the packets 
    from the server.
    ii) For all incorrect command there is help options given to the user,
    if somehow user passed any wrong arguments then help/error message will be displayed so that user can check his/her 
    typed command in order to run this project. The details of all commands have been mentioned in the message box
    which can either seen in the project report or can be verified from the terminal.
    iii) Once all the command have been cross checked then user can run the server with the particular
    file name which he wants to stream but before he starts the server he should make sure that VLC UDP sockets are open 
    else the packet will be lost whatever server will sent.

4> Streaming Videos :
   ================
    i)  Now it’s time to start the server/process, the image shown in the report is the server the server process, as you can 
    see the server is sending 1024 bytes of the data in every 1sec because this size is given by user. Also the encrypted 
    data which have been show it is for the video chunks which are been transmitted. This is the binary format of the data
    which is getting into the process.
			   
    The below is the full command which can be given to start the streaming process.

    "./stream_general 1 0 1 1 5678 1024 vande/ matram  192.168.2.4" 
				
	-> 1024 is the packet size, this can given by the user based on their need.
	-> "Vande/ matram" is the video file name which is in the process of streaming.
	-> "192.168.2.4" is the IP address on which you are starting server.

==================================================================================================================


