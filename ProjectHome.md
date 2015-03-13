<table><td valign='top'>The Last Express is an adventure game game created by Jordan Mechner and Smoking Car Productions, published in 1997. It takes place on the Orient Express, days before the start of World War I.<br>
<br>
Set on the Orient Express in 1914, the player takes on the role of Robert Cath, an American  doctor on the train's final journey from Paris to Constantinople (nowadays Istanbul) before World War I. Cath, already wanted by French police as he is suspected of the murder of an Irish police officer, is contacted urgently by his old friend Tyler Whitney, to join him on the Orient Express, gateway to the East, and a possible exit from all his troubles. Cath boards the train via a motorcycle and looks for Whitney, who is already on board. But as soon as he steps onto this luxurious train, Cath becomes involved in a maelstrom of treachery, lies, political conspiracies, personal interests, romance and murder.<br>
<br>
The game has 30 characters representing a cross-section of European forces at the time, including Serbian freedom fighters, a German  arms dealer, a Russian anarchist, a suspicious Austrian concert violinist, a Persian eunuch and his private harem, a mysterious art collector and others. As the train races east, the player must stay alive while interacting with these characters, which includes eavesdropping on conversations, sneaking into compartments and defusing a bomb. The story is non-linear, with the player's actions (and failures to act) determining the course of the story.<br>
<br>
<i>Game Information: <a href='http://en.wikipedia.org/wiki/The_Last_Express'>Wikipedia page on The Last Express</a></i>

<i>File Formats: <a href='http://wiki.xentax.com/index.php/Special:Search?search=The+Last+Express&go=Go'>Last Express data files on Xentax</a></i>

<i>Gamasutra article on The Last Express: <a href='http://www.gamasutra.com/view/feature/3862/the_last_express_revisiting_an_.php'>Revisiting An Unsung Classic</a></i>


</td>
<td valign='top'>
<wiki:gadget url="http://www.ohloh.net/p/lastexpress/widgets/project_basic_stats.xml" height="240" width="340" border="1" /><br>
</td>
</table>


## Current Progress ##

### October 18, 2010 ###

Goodbye GoogleCode!

The Last Express engine has been merged into the ScummVM main repository and work will continue there. This project will be kept as an archive.

![http://img375.imageshack.us/img375/3540/goldeagle.png](http://img375.imageshack.us/img375/3540/goldeagle.png)

### October 6, 2010 ###

Less than <s>100</s> <s>75</s> <s>50</s> 40 AI logic functions left to implement!

### September 27, 2010 ###

A year has gone by since the first check-in!

Here is a quick status of the engine:
  * Graphics/File handling is mostly done (except transitions)
  * Shared logic is also almost complete
  * Inventory handling still needs a bit of work (had been broken for a while)
  * Only 150 AI logic functions are left to implement!
  * Saved games are not implemented
  * Sound handling is missing a lot of functionality (filters, caching, etc.)

### July 17, 2010 ###

A lot of the shared entity logic is now implemented and there is some life starting to show up in the train cars :)

The menu code is in the process of being refactored to use the new scene manager and frame queue facilities.

On the AI code front, 429 functions are left to implement (all the large ones...).

![http://img412.imageshack.us/img412/2234/lastexpress071710.png](http://img412.imageshack.us/img412/2234/lastexpress071710.png)

### May 25, 2010 ###

Just a quick update to tell eveybody how things stands.

Lots has been happening behind the scenes and most of the game internal structures have been figured out. There is also a lot more logic code implemented now.

Once the last bits of logic have been understood, we should start seing more visible changes.

Stay tuned!

### February 8, 2010 ###

Time for a new update!

A lot has changed since last time:
  * The game entities (characters & environment) have been figured out and some logic code implemented. The basic framework is now in place but there are more than 850 functions left to implement...
  * Most hotspot actions have been implemented
  * Plus lots of small changes to sound, scene processing, savepoints & objects

Most of these changes are not yet visible and the changes related to event handling introduced some "regressions".

### November 18, 2009 ###

Lots of changes since last time! A lot more of the original engine internal structure has been figured out. A lot of hotspot actions have been implemented, and along with entities and objects, this allows more interaction with the game.

You can now go to your compartement, move around the corpse and pick items such as the jacket and scarf. Still no interaction with other characters (they don't even show up!), but that's next.

### November 4, 2009 ###

  * More has been figured out about scene handling: you can now start to travel through the train
  * Animations are now synchronized with sound
  * and a lot of other ameliorations

![http://img29.imageshack.us/img29/154/lastexpress041109.png](http://img29.imageshack.us/img29/154/lastexpress041109.png)

### October 26, 2009 ###

  * Graphics Manager overhaul is in progress (dirty rect support, cleaner separation between drawing and resource code, etc.)
  * Basic support for scenes hotspot has been added (you can now interact with elements on the main menu)
  * Basic inventory management is implemented (looking at items remains to be done)
  * Lots of memory leaks have been fixed

### October 10, 2009 ###

  * Very basic menu functionality is implemented. Scene loading is still not implemented, so background loading is hard-coded & there is no hotspot handling (ie. no highlight on mouse over and mouse clicks are not working).
  * Work is progressing on savegames, trying to understand the huge game state structures.

![http://img194.imageshack.us/img194/3448/lastexpressbackground10.png](http://img194.imageshack.us/img194/3448/lastexpressbackground10.png)

### October 5, 2009 ###

  * Merged with more advanced engine from Jordi (jvprat)
  * All file formats except from scenes are supported (some such as animations and sequences are not 100% done yet)

### September 29, 2009 ###

  * Archive and background resource loading are working.
  * Sound playing is there too but with some horrible distortion.
  * Subtitles are loaded fine, but strings are UTF-16 (which IIRC scummvm does not support yet) and there is no font support yet.
  * Work is being done on animations and sequences (NIS and SEQ files)

![http://img185.imageshack.us/img185/6904/lastexpressbackground09.png](http://img185.imageshack.us/img185/6904/lastexpressbackground09.png)