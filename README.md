Aion Grind Meter - Aion XP/hr + AP/hr meter

<h2>Overview</h2>

Aion Grind Meter is an XP/hour (Experience gained per hour) and/or AP/hour (Abyss Points gained per hour) meter for Aion.
It is useful for determining how fast or slow you are leveling up, and/or gaining Abyss Points. 

It uses the chat log file (Chat.log) for data input, and does not modify the Aion client in any way.



<h2>Prerequisites</h2>

Aion chat log file (Chat.log) must be enabled and present for Grind Meter to work.

<h4>Enabling Chat Log</h4>
You can use Aion RainMeter (ARM) to enable chat log. 
It can be downloaded from http://rainy.ws/

Once you have enabled chat log using ARM, log into Aion with any one of your characters, and the Chat.log file will be created.



<h2>Setup</h2>

Extract the executable to anywhere. 
You will be prompted to browse for your Aion folder when you run it for the first time.

You do not need to browse for your Aion folder if you extracted it into your Aion folder.



<h2>Initialization</h2>

For best results, enter your current character level, experience, and Abyss Points when you launch Grind Meter.

You can leave any of these fields blank if you do not want to bother with any or all of them.



<h2>XP Mode</h2>

<ul>
<li>XP Gained: Net experience gain of your character for this session.</li>

<li>XP / Hour: Your net XP gain divided by number of hours elapsed this session. This value represents how fast you are gaining XP over time.</li>

<li>Last Change: Amount of XP gained in your last kill or quest reward (if positive), or amount of XP lost from your last death (if negative).</li>
</ul>

If you have entered both your starting level and XP during initialization, you can see your XP percentage toward the next level, as well as a compact XP bar.


<h3>PvE Death</h3>

You lose a small amount of XP whenever you die, but the exact amount of XP lost is not indicated in the chat log. 
Grind Meter can determine how much XP you lost when you recover XP by Soul Healing, as doing so always recovers 2/3 of your XP lost due to the death.

If you had entered your starting level and XP during initialization, you can also update your after-death XP manually if a Soul healer is not readily accessible.



<h2>AP Mode</h2>

<ul>
<li>AP Gained: Your net income of Abyss Points. 
AP values of Abyss Relics and Blood Marks not included in this total - they are indicated separately in [square brackets] if you have obtained any.</li>

<li>AP / Hour: Your net AP gain divided by number of hours elapsed this session. This value represents how fast you are gaining AP over time. AP/hour from Abyss Relics and Blood Marks values are indicated separately in [square brackets].</li>

<li>Last Change: Amount of AP gained in your last kill or quest reward (if positive), or amount of AP lost from the lost time you got PKed by an opposing faction player (if negative).</li>
</ul>

If you have entered both your starting AP during initialization, you can see your AP percentage toward the next abyss rank (up to 1st kyu), as well as the progress bar toward next rank.


<h3>Getting PKed by the opposite faction</h3>

You lose Abyss Points whenever you get PKed by the opposing faction, but the exact amount of AP lost is not indicated in the chat log. 
Amount of AP lost is influenced by many factors, and is impossible to calculate without user's manual update.

If your character's starting AP value was entered during initialization, you will be asked to manually enter your current AP (after the death).
Grind Meter will use this information to calculate AP you have lost from this death.

If your initial AP was not entered during initialization, there is no way Grind Meter can determine exactly how many AP you lost whenever you get PKed by the opposing faction.

There is no AP loss in instance server (Dredgion, Crucible arenas, Kamar Battlefields, etc.), and you will not be prompted for manual AP update in these PvP instances.




<h2>Kinah / Repose Mode</h2>

<h4>Kinah-related fields:</h4>
<ul>
<li>Cash Flow In: Amount of Kinah you have gained from all sources.</li>

<li>Cash Flow Out: Amount of Kinah you have spent.</li>

<li>Net Change: The net increase (if positive) or net decrease (if negative) of your kinah.</li>

<li>Last Transaction: </li>
</ul>

<h4>Repose/Salvation fields</h4>

<ul>
<li>Repose Used: Energy of Repose (Rested XP) you have consumed this session.</li>

<li>Salvtn Used: Energy of Salvation you have consumed this session.</li>
</ul>
