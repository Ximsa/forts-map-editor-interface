# forts-terrain-compiler

This Project aims to let you make Forts Terrain Files by feeding it with a formated text file.

## Terrain File
You can (and should) specify header info (m), polygon info (p) and terrain object info (t).<br/>
Header:<br/>
``m [enironmentString]``<br/>
i.e: ``m environment/alpine``<br/>

Polygon:<br/>
``p [x] [y] [hasSurface] [surfaceString]``<br/>
i.e: ``p 0 -1000 1 rocks01``<br/>

Terrain:<br/>
``t [groundString] [surfaceString] [team] [hasSurface] [foundation] [mine] [windfloor] [viewfloor] [nodraw]``<br/>
i.e: ``t environment/alpine/ground/ground1.dds rocks01 1 0 1 1 1 0 0``<br/>

Note that the Terrain gets defined by the preceding polygon list.<br/>
Also it doesn't matter how many header lines you write, the last one will get applyed
