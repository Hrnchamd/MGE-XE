This directory contains post-processing shader mods.


Creating new shaders
--------------------

New shaders should have a single technique tagged with an MGEinterface annotation like this:

technique T0 < string MGEinterface = "MGE XE 0"; >


Shader ordering
---------------

Shaders (since v0.14) are auto-sorted by category when added to the active shader list. This allows adding shaders without having to follow an ordering guide, and also adding shaders at runtime without manual intervention. Existing shaders without a category stay in their assigned place.

The category is specified by name in the shader annotation. 

Category annotation example from a bloom shader:
technique T0 < string MGEinterface = "MGE XE 0"; string category = "sensor"; >


The category sort ordering is:
         scene - Additional objects rendered into the scene.
	atmosphere - Atmosphere effects that render over all objects, such as mist.
	      lens - Lens effects such as depth of field.
	    sensor - Sensor effects such as bloom.
	      tone - Tone mapping and color grading.
	     final - Any effects that need to run last.


Tuning relative ordering within a category is also possible with priorityAdjust.

An example from a SSAO shader, to avoid applying darkening on top of any other shader:
technique T0 < string MGEinterface = "MGE XE 0"; string category = "scene"; int priorityAdjust = -10000; >

Using these in your shaders is recommended to improve ease of use.


Shader scripting
----------------

Shaders can be loaded at runtime and have their variables modified using MWSE.

See MWSE docs:
https://mwse.github.io/MWSE/apis/mge.shaders/
https://mwse.github.io/MWSE/types/mgeShaderHandle/
