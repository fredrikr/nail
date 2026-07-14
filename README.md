# NAIL

*Not an Inform Library*

NAIL is similar to a standard library for the Inform 6 programming language.
It should allow authors to create text adventure games / interactive fiction 
using the Z-machine virtual machine, to be played on 8-bit computers as well as newer
platforms. It provides a parser, implementations of common verbs, as
well as a framework for writing text adventures.

NAIL is based on the PunyInform library, developed by Johan Berntsson and Fredrik Ramsberg.
PunyInform, in turn, is based on the Inform 6 standard library, developed by Graham Nelson. PunyInform is smaller and faster than the Inform 6 standard library. NAIL is smaller than PunyInform. It is also more limited, less well tested, less well documented, and all-around harder to work with than PunyInform.

Games using NAIL can only be compiled to z3 format.

To compile games using NAIL, you need the the official Inform 6
compiler maintained by David Kinder, at
https://github.com/DavidKinder/Inform6.  Binaries can be found at the
[IF-Archive](https://www.ifarchive.org/indexes/if-archive/infocom/compilers/inform6/executables/).
You should use at least Inform v6.44, and I recommended using the latest available version.

You can use [borogove.io](https://borogove.io/) to make your PunyInform
game playable online. Create an account, upload your game file, and choose whether
the game should be visible and playable for all visitors to the site, or
only to those who have the link to your game. Another option is to upload 
your game file (e.g. mygame.z3) to the 
[Parchment HTML Converter](https://iplayif.com/api/sitegen) and download a 
single-file HTML file, which can be uploaded to sites such as Itch.io.

## Motivation

The main goal of NAIL is to produce very small games, while still having access
to most of the convenient framework provided by PunyInform. Games should run well on
older architectures, such as the 8-bit computers of the 1980s.

To make disk images for Commodore and Acorn computers, you can use
[Ozmoo](https://github.com/johanberntsson/ozmoo/).


## Status

NAIL is fully working, but it probably has some rough edges.

If you are interested in this project, please star or follow the project
here on Github. Announcements are made on https://intfiction.org/c/authoring/inform-6/66

You can read the manual in the documentation folder.

## Learning NAIL

You should start by learning [PunyInform](https://github.com/johanberntsson/PunyInform). Then read the (short) documentation on NAIL, to see which parts of PunyInform are supported in NAIL.

## Tools

* To work with source code you may want a text editor which has a syntax
  colouring mode for Inform 6. Some popular choices include Visual Studio
  Code and Atom, both available for Windows, Mac and Linux. Notepad++ is
  another option, for Windows.

* To quickly build a game for play on Commodore 64, 128, Plus/4, MEGA65, Commander X16 or Acorn/BBC, you can use [Ozmoo Online](https://ozmooo.online/).

* To build a game for 20+ different platforms at once, you can use the
  [Puny BuildTools](https://github.com/ByteProject/Puny-BuildTools). This
  tool set can be installed on Linux. Windows users can create a virtual machine
  running Linux.

* The [Parchment HTML Converter](https://iplayif.com/api/sitegen) can convert
  your game file into an HTML file, making your game playable in a web browser.

## Community

If you want to discuss, or ask questions about NAIL, these are good places to go:

* **[intfiction.org forum, Inform 6 section](https://intfiction.org/c/authoring/inform-6/66).
  Please tag your posts with "punyinform".**

* **[PunyInform Discord server](https://discord.com/invite/y9anzKJTBa).
  You can talk about NAIL in the #inferior_systems channel. 
  Please note that you need to click checkmark in the Rules channel and
  wait a few minutes before you can post.**

There are also categories/channels in the above forums where you can
discuss plot, story, puzzles etc, and posts requests for beta-testers
for your game.

## Games that were built with NAIL

* [SchoolAdventure](https://github.com/fredrikr/schooladventure)

## Credits

NAIL borrows a lot of code and concepts from PunyInform, created and maintained by 
Johan Berntsson and Fredrik Ramsberg. PunyInform borrows a lot of code and concepts from the Inform 6 standard library, by Graham Nelson. 

Many thanks to David Kinder and Andrew Plotkin, for their hard work,
and generosity with their time and knowledge, regarding the Inform 6 compiler.

Huge thanks to Graham Nelson, without whom the Inform 6 compiler and library wouldn't exist.
