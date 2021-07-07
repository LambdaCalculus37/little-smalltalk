# Little Smalltalk
A source mirror for all five major releases of the Little Smalltalk programming environment

This repo is to collect and archive the source code for all five major releases of the Little
Smalltalk programming environment.

**What the heck is Little Smalltalk?**

Little Smalltalk is a non-standard dialect of the [Smalltalk](https://en.wikipedia.org/wiki/Smalltalk) programming language invented by Timothy Budd. It was originally described in the book *A Little Smalltalk*.

Even though it is a non-standard dialect, it's still a fun little dialect to play around with.

I created this repo as a means of keeping the source code of Little Smalltalk alive and available through easy means, as its original website is no longer up, and it would be a shame to have the source lost to the sands of time.

**Repo Layout**

As there are 5 (or rather, 5.1, if you count the 4.1 folder) major releases of Little Smalltalk, I have mirrored the source for all of them here. The versions included are as follows:

1. Version 1 (lst1) - The original release as described in Budd's book!
2. Version 2 (lst2) - The second release; according to the READ_ME included in the source folder, this is a beta release originally posted to comp.sources.unix way back in the day.
3. Version 3 (lst3) - The third release; this is public domain, cross-platform, and compiles on nearly anything with the right toolchains. It even compiles on modern Linux without issue! This version has patches contributed by Charles Childers (crc).
4. Version 3.1.5 (lst-mac) - A release of Little Smalltalk 3.1.5 for Classic Mac OS; this is the source code for that release.
5. Version 4 (lst4) - The fourth release; this version was the last one worked on by Timothy Budd and picked up by Danny Reinhold.
6. Version 4.1 (lst4.1) - Same as above, but can compile in Windows.
7. Version 5 (lst5) - The fifth release; this version never made it past its 7th alpha release.


**Compiling**

For the most part, most of these versions of Little Smalltalk should easily compile in any Linux, as well as macOS, Windows, or BSD, as well as BeOS, Haiku, or even other unique OSes like AmigaOS, MorphOS, and AROS. Historically, Solaris, IRIX, HP-UX, and NeXTSTEP should all work as well (I haven't tested on many other OSes so feedback of any sort in that regard would be great!)

To compile, simply switch to the folder of the version you want to use and run 'make'. The README files in each folder will give advice and guidance on what to do as well.

**Using Little Smalltalk**

The book, *A Little Smalltalk*, is available to read [here](http://sdmeta.gforge.inria.fr/FreeBooks/LittleSmalltalk/ALittleSmalltalk.pdf), and gives a good overview of the commands and workings.

**License**

This is a little compilcated, because GitHub only really allows for one license to be displayed and used, and the 5 versions are under different licenses. Thus, even though the repo says "MIT License", this doesn't apply to all versions.

Here are the licenses for each version:

1. v1 used a license that asked users to attribute source and kept a copyright notice in the source files.
2. v2 and v3 are public domain. Go nuts with them.
3. v4 and v4.1 are freeware with a non-commercial usage clause.
4. v5 is licensed under the MIT license.

**More Information**

The original Little Smalltalk homepage (where I culled all of these source archives from) is no longer up, but luckily it is available for viewing via the [Wayback Machine](https://web.archive.org/web/20071005060831/http://www.littlesmalltalk.org/index.php?page=home).

As Little Smalltalk got around quite well and was very cross-platform, this wiki page has more information about LST releases on other platforms, like OS/2 and Amiga; [check it out](http://www.edm2.com/index.php/Little_Smalltalk)!