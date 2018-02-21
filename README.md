# The Perfect Hack! - IEEE NITK Edify Workshop

The perfect hack! hands-on workshop at Main Seminar Hall on Feb 22nd 2018 , Thursday

What is this workshop about:
This workshop is a hands-on workshop and we will demonstrate a live-server hack .
Even you will be able to hack into the server at the end of the workshop.

Pre-requisites:

 1. A linux machine.
  Students who are not running linux machine can do this.
     a.  Download and install Oracle [VirtualBox](https://www.virtualbox.org/) 
          

    b.  After installing it , download the [ubuntu-linux](https://www.ubuntu.com/download/desktop) ISO image:
         
   

    c.  Run ubuntu on virtualbox.
    
2. This repository. To download this repository ,
    $git clone <URL to be added>
    
3. PEDA for gdb. PEDA - Python Exploit Development Assitance
      
  Install gdb-peda
  `$ git clone https://github.com/longld/peda.git ~/peda`
  `$ echo “source ~/peda/peda.py” >> ~/.gdbinit`

You are ready now!

What does this repository have?
 
  a. **Introduction** : This has a C program which will be used to explain the program execution internals before we get started with 
      attacking the server.
  
b. **server_dir**   : This directory consists all the programs to successfully run the server. This is part of Phase1 of the hack. 
  
c. **ret2libc**     : This directory consists the programs for the Phase2 of the hack.
  d. attacker_dir : This directory consists all the tools to exploit the the server application.
   

 Structure of the workshop:
 
 1. *Introduction*: We will be explaining program execution internals , how a function call works .
  To get started with this , you can go through the following blog-posts.
      a.  https://ieeenitk.org/blog/introduction-to-reverse-engineering/
      b.  https://ieeenitk.org/blog/a-step-ahead-in-reverse-engineering/
      
 2. *Phase1*: This is first part of the  hack.
     a. We create what is known as the "backdoor" to that server.
     b. At the end of this phase , we have access to the server.
 
 3. *Phase2*: Second part of the hack.
     a. Now that we have the backdoor , the objective of this phase is get the root shell.
     b. Search for a buggy application and exploit it using our tools.
 
 4. Some real examples of these vulnerabilities , and how they were exploited.
 
 5. Doubts 
 
 6. Feedback
 
  
 At the end of the workshop: We will have root access(or god access :P) to the server.
 All the tools used are written by us from scratch. We hope this is a motivation for you guys to develope your own tools and exploits.
 
 Attend the workshop , witness and try out what actual hacking looks and feels like!
 
 PS:  After downloading the repository , please do not make any changes in the source code because it might not run properly on your machine. Main objective is to give you guys a feel of what actual hacking is.

 
 










