Aion Grind Meter - Aion XP/hr + AP/hr meter

##Overview

Aion Grind Meter contains various grinding meters for Aion: 
* XP gains and XP/hour (Experience gained per hour) 
* AP gain/loss and AP/hour (Abyss Points gained per hour).
* Gathering and/or crafting success/failure/cancellation/procs, successes per hour
* Gathering and/or crafting level ups per hour, estimated XP bars

It uses the chat log file (Chat.log) to obtain gameplay information. It does not interact or modify the Aion client in any way.

Aion Grind Meter is written in C++ with wxWidgets library powering the Graphical User Interface (GUI).



##Prerequisites

Aion chat log file (Chat.log) must be enabled and present for Grind Meter to work.

Client must be in English language (Developed and tested on North American servers. Not tested on European service.)

####Enabling Chat Log
You can use Aion RainMeter (ARM) to enable chat log. 
It can be downloaded from http://rainy.ws/

Once you have enabled chat log using ARM, log into Aion with any one of your characters, and the Chat.log file will be created.



##Setup

Extract the executable to anywhere. 
You will be prompted to browse for your Aion folder when you run it for the first time.

You do not need to browse for your Aion folder if you extracted it into your Aion folder.



##Initialization

![Initialization](http://maxxperiod.com/aiongrindmeter/images/init.png)

When you launch Grind Meter, you will be given three input fields that needs to be manually inputted: 
* Level
* Current XP
* Current AP

For best results, fill in these fields correctly.
You can leave any of these fields blank if you do not want to bother with any or all of them.



##XP Mode

![XP Mode](http://maxxperiod.com/aiongrindmeter/images/exp-hr.png)

* XP Gained: Net experience gain of your character for this session.

* XP / Hour: Your net XP gain divided by number of hours elapsed this session. This value represents how fast you are gaining XP over time.

* Last Change: Amount of XP gained in your last kill or quest reward (if positive), or amount of XP lost from your last death (if negative).


If you have entered both your starting level and XP during initialization, you can see your XP percentage toward the next level, as well as a compact XP bar.


###PvE Death

![PvE Death](http://maxxperiod.com/aiongrindmeter/images/death.png)

You lose a small amount of XP whenever you die, but the exact amount of XP lost is not indicated in the chat log. 

Grind Meter's window will be replaced with a prompt that tells you to receive Soul Healing.
XP you lost on death can be calculated when you recover XP by Soul Healing, as doing so always recovers 2/3 of your XP lost due to the death.

If you had entered your starting level and XP during initialization, you will also have the option of manually inputting of your after-death XP manually, useful if a Soul healer is not readily accessible.



##AP Mode


![AP Mode](http://maxxperiod.com/aiongrindmeter/images/ap-hr.png)

* AP Gained: Your net income of Abyss Points. 
AP values of Abyss Relics and Blood Marks not included in this total - they are indicated separately in [square brackets] if you have obtained any.

* AP / Hour: Your net AP gain divided by number of hours elapsed this session. This value represents how fast you are gaining AP over time. AP/hour from Abyss Relics and Blood Marks values are indicated separately in [square brackets].

* Last Change: Amount of AP gained in your last kill or quest reward (if positive), or amount of AP lost from the lost time you got PKed by an opposing faction player (if negative).


If you have entered both your starting AP during initialization, you can see your AP percentage toward the next abyss rank (up to 1st kyu), as well as the progress bar toward next rank.


###Getting PKed by the opposite faction

![PK](http://maxxperiod.com/aiongrindmeter/images/pk.png)

You lose Abyss Points whenever you get PKed by the opposing faction, but the exact amount of AP lost is not indicated in the chat log. 
Amount of AP lost is influenced by many factors, and is impossible to calculate without user's manual update.

If your character's starting AP value was entered during initialization, you will be asked to manually enter your remaining AP after the death.
Grind Meter will use this information to calculate AP you have lost from this death.

If your initial AP was not entered during initialization, there is no way Grind Meter can determine exactly how many AP you lost whenever you get PKed by the opposing faction.

There is no AP loss in instance server (Dredgion, Crucible arenas, Kamar Battlefields, etc.), and you will not be prompted for manual AP update in these PvP instances.



##Kinah / Repose Mode

![Kinah Mode](http://maxxperiod.com/aiongrindmeter/images/kinah.png)

####Kinah-related fields:

* Cash Flow In: Amount of Kinah you have gained from all sources.

* Cash Flow Out: Amount of Kinah you have spent.

* Net Change: The net increase (if positive) or net decrease (if negative) of your kinah.
 
* Sales to NPCs: Amount of Kinah you received by selling vendor trash to NPCs.

* Last Transaction: The amount of your last Kinah transaction.

####Repose/Salvation fields


* Repose Used: Energy of Repose (Rested XP) you have consumed this session.

* Salvtn Used: Energy of Salvation you have consumed this session.
 


##Gathering / Crafting Mode

![Kinah Mode](http://maxxperiod.com/aiongrindmeter/images/gathercraft.png)

* Success: Number and percentage of successful gathering / crafting attempts.
 
* Failure: Number and percentage of failed gathering / crafting attempts due to the failure bar being filled up.
 
* Cancel: Number and percentage of gathering / crafting attempts forcibly cancelled due to various rasons, such as enemy attack, flight time running out, or manually cancelled by player.
 
* Number / h: Average speed of successful gathering / crafting attempts per hour.

##Gather/Craft Leveling Mode

![Kinah Mode](http://maxxperiod.com/aiongrindmeter/images/gathercraftlvl.png)

* Gather/Craft Lvl Ups: Number of times you have leveled up a profession this session.
 
* Lvl Ups / Hour: Average speed of gather/craft leveling this session.

* This Level: Number of gathers/crafts elapsed since last time you have leveled the profession up. 
 
* Last Level: Number of gathers/crafts actually taken for your most recent profession level up.
 
* G XPe and C Xpe: Estimated XP bar for gathering and crafting respectively. The estimation calculation is (This Level) / (Last Level), and if (This Level) > (Last Level), then (This Level) / (this Level + 1) instead.
