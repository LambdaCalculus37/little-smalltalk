LittleSmalltalk
---------------

LittleSmalltalk is a minimalistic programming language and
development environment based on Smalltalk.

It is not a Smalltalk-80 nor an ANSI Smalltalk system.
So please don't report incompatibilities.
It is not intended to be compatible.

LittleSmalltalk has originally been developed by Timothy A. Budd
and is now continued by Danny Reinhold / Reinhold Software Services.
Of course I would be happy if you would like to contribute
something to the project!

This is a source only package for now - well, it is an early
alpha release...
The full system currently only works on Windows.
But there are already some ports to other systems like
Linux, Mac OS/X, SUN Solaris, IBM AIX, HP-UX and SGI Irix.
Currently LittleSmalltalk is somewhat limited on some of
these platforms. But I think it is just a matter of time
to get the system running there much more stable and complete.

Compilation
===========

Windows
-------
Simply open the Visual Studio 2005 Express Edition, load the
LittleSmalltalk solution file (LittleSmalltalk.sln), compile
the system and enjoy it.


Other systems
-------------
cd into the littleSmalltalk directory.
Change the Makefile and the build.make file if neccessary
for your platform.
Then type make.

The Makefile based build process currently compiles a version
of LittleSmalltalk without GUI support.
If you want to have GUI support, please do this:

(I will simplify this process in future releases...)

Change -DLST_USE_GUI=0 in the definition of the CFLAGS macro
to -DLST_USE_GUI=1.
Download the libraries IUP, CD and IM from the tecgraf site.
Attention: Please be careful to really download the correct
version for your platform and compiler.
Change the LIBS macro definition to contain something like:
LIBS=-ldl -L<theiuplibdir> -L<thecdlibdir> -L<theimlibdir>
 -L/usr/X11R6/lib -liupcontrols -liupimglib -liupim -liup -lim -lcd -lcdiup -lXm -lXmu -lXp -lXext -lXt -lX11 -lSM -lICE -lstdc++ -lm -lpthread

Open a shell and type
uname -s
uname -r
Then verify if there is a file named lst_os_`uname -s`_`uname -r`.h.
If not please copy the lst_os_....h and the lst_os_....c files that best
match your platform.

Then compile with: make clean; make
Then the system should compile with GUI support...


If you successfully do anything or port it to another
compiler or operating system please let me now!
Please also inform me if you have serious problems.

And now: Have fun!

  - Danny Reinhold / Reinhold Software Services

--
Reinhold Software Services
  -- littleSmalltalk --
Weizenkampstr. 154
28199 Bremen
Germany

Web: http://www.littlesmalltalk.org

