
MGE XE 0.11.0

Released 2019-05-01

Licensed under GPL v2, source available at https://github.com/Hrnchamd/MGE-XE


Summary
-------

A graphics improvement add-on to Morrowind, for longer viewing distances, great sunsets, fine shaders and better lighting. MWSE 2.1 beta is included so that the newest gameplay mods work straight away.


Requirements
------------

Morrowind GOTY or Bloodmoon fully patched.
Any graphics card made since 2008 or so.


Install
-------
1. Update to DirectX 9.0c June 2010 at http://www.microsoft.com/download/en/details.aspx?id=35 (This is a required update for all Windows, and won't conflict with DX10+.).
2. If you've just installed Morrowind, run Morrowind to the title screen once, to generate Morrowind's first time settings.
3. Install MGE XE by extracting the archive to the Morrowind directory.
4. Run the new MGEXEgui. Read the instructions page.
5. If you use Steam, you should turn off the Steam overlay (in Steam, right click Morrowind > Properties). If you use Crossfire/SLI, turn off "Responsive menu caching" in the In-game tab, to avoid performance reductions, as this feature is SLI unfriendly.
6. There is an optional mod, 'XE Sky Variations', that will randomize the sky colour and sunrise/sunset every day. It requires high quality sky scattering enabled, and MWSE enabled.


Upgrading
---------
From a previous MGE XE:
Extract the archive to the Morrowind directory. Run MGEXEgui and regenerate distant land.

Morrowind has a different resolution setting per user, which this version tries to be compatible with. If you're running Morrowind as an administrator, you need to set MGEXEgui to run as administrator. If you're running Morrowind normally, run MGEXEgui normally. After you've set that correctly, run MGEXEgui to configure new settings.

From MGE 3.8:
You should regenerate distant land with 150 minimum static size. If you were using HUD mods made for standard MGE, you should deselect them from your load order. MGE XE requires its own HUD mods to fix design problems with older mods.


Uninstall
---------
Delete MGEXEgui.exe, d3d8.dll, dinput8.dll and the mge3 directory.


You might want to know
----------------------

MGE XE includes an updated MWSE 2.1 by NullCascade. MWSE mods are therefore supported while you are using MGE XE, the MWSE launcher is not required. MWSE is upgradable by running MWSE-Update in the Morrowind directory.

Standard MGE (3.8) shaders and HUD mods are not compatible due to design differences. You will not be able to use them with MGE XE without modification. Incompatible shaders will be detected and will not load.


Problems?
---------
If you get a message in game "MGE XE serious error condition. Check mgeXE.log for details.", you can see the log file by clicking the "Show mgeXE.log" button in the Config tab of MGEXEgui. You may be able to discover what's wrong from the error message.

Questions and support thread at #troubleshooting channel on discord https://discord.me/mwmods

Reporting in game crashes: Open MGEXEgui, on the Config tab click "Show last mgeXE.log". Add it to your report.

Reporting distant land generator crashes: Open MGEXEgui, on the Config tab click "Show DL generator log". Add it to your report.


Credits
-------
Many people have worked on MGE over the years, and the sum of their ideas and hard work implementing them has improved Morrowind by a huge amount. MGE XE is based on the MGE code.

MGE was written by Timeslip, LizTail, Krzymar, and Phal. MGE XE is currently being developed by Hrnchamd.
Thanks to the Morrowind community for all the inspiration and feedback.


Changelog (newest first)
---------
0.11.0
- 4GB patch applied to MGEXEgui.
- Fixed slow mouse movement and dropped inputs when frame rate was too high (e.g. in small interiors).
- Distant statics generator handles incorrect NIFs better and most hangs are solved.
- Distant statics generator displays current processing NIF to help find bad NIFs.
- Rendering improved to avoid cracks in some modded skinned meshes.
- Dynamic ripples wave border artifacts fixed. Ripple simulation pauses in menu mode.
- Shaders like SSAO/DoF no longer glitch when equipping inventory items in the menu.
- HDR shader has a slightly wider range of brightness adaptation.
- SSAO shaders behave better in fog, and no longer have artifacts on more distant objects.
- Sunshafts shader now has a more consistent sun disc size and brightness.
- Distant land generator texture size limit increased to 8192. Only recommended when using mods with added landmass.
- Changed FPS limiter range limit back to 240.
- No longer gives a renderer error when using 2x or higher vsync in windowed mode.
- Distant land and FFE shaders can be live reloaded by toggling distant land, post shaders can be live reloaded by toggling shaders.
- Multiple component buildings like Vivec cantons will now appear in one piece once in distant land view range, instead of the component parts appearing separately.

0.10.1
- Updated distant land generator to fix crashes on certain meshes, and to handle NiSwitchNode.

0.10.0
- Added MWSE weather commands to set glare view, cloud speed and wind speed for each weather type.
- Re-introduced some MWSE camera rotation commands.
- Added MWSE switch node command xModelSwitch.
- Distant land plugin parsing errors and memory leak fixed.
- Added various entity utility functions. See documentation below.
- Added MWSE raycast and physics functions, plus a demonstration object placement mod.
- Re-introduced MWSE camera shake functions.
- Grass lighting improved to work with two-sided meshes better.
- MWSE HUD functions added to set HUD effect parameters.
- MGE HUD now renders behind Morrowind HUD unless Z-writes are on.
- MGEXEgui will now run without needing Morrowind to create registry keys first.
- Moved all input config settings into MGE.ini, MGEXEgui will auto upgrade existing configs.
- Re-introduced MWSE key input functions.
- New screenshot filename formats.
- Distant land setup "container modification" crash fixed.
- Shader reloading when shaders are toggled on/off.
- MGEXEgui DPI awareness improvements.
- Sun shadow improved stabilization.
- Fixed sunflare overbrightness with per-pixel lighting.
- UI scaling now works even when MGE is set to disabled.
- Fixed WINE-specific shader rendering issue.
- Issue with frame rate meter showing doubled framerate when another shader injector is loaded.
- Fixed emulation of alpha textures with bump maps on top.
- User friendly shader options.
- Fixes MWSE crashing issues.
- Mouse sensitivity adjusts to zoom level.
- Per-pixel lighting improvements.
- Variable shadow resolution config.


MWSE support
------------

Supported functions from MGE:

WipeAll
OutputDebugString
OutputVersionString
GetVersion
GetScreenWidth
GetScreenHeight
GetEyeVec

WipeHUDElements
WithHUD
CancelWithHUD
LoadHUD
PositionHUD
ScaleHUD
FullscreenHUD
EnableHUD
DisableHUD
ChangeHUDTexture
ChangeHUDEffect
FreeHUD
NIDLoadHUD
NIDPositionHUD
NIDScaleHUD
NIDFullscreenHUD
NIDEnableHUD
NIDDisableHUD
NIDChangeHUDTexture
NIDChangeHUDEffect
NIDFreeHUD

TapKey
PushKey
ReleaseKey
HammerKey
UnhammerKey
AHammerKey
AUnhammerKey
DisallowKey
AllowKey

EnableCameraShake
DisableCameraShake
SetCameraShakeMagnitude
CameraShakeAccel
StopCameraShakeAccel
RotateScreenBy
SetScreenRotation
ScreenSpin
StopSpinSpin
GetScreenRotation

EnableZoom
DisableZoom
ToggleZoom
ZoomIn
ZoomOut
ZoomInBy
ZoomOutBy
SetZoom
Zoom
StopZoom
GetZoom

New functions in MGE XE:
GetGS
SetGS
GetBaseHealth
GetBaseMagicka
GetBaseFatigue
IsScripted
LastActorHit
SetEntityName
SetOwner
UIShow
UIHide

SetSkyColour
SetFogColour
SetAmbientColour
SetSunColour
SetSunriseSunset
SetScattering
SetWeatherGlare
SetWeatherCloudSpeed
SetWeatherWindSpeed
    
EnableShader
DisableShader
SetShaderFloat
SetShaderLong
SetShaderVector

RayTest
RayHitPosition
RayHitNormal
RayHitRef
ModelBounds

New function reference:

xGetGS <long GMST_index>
Returns: <long/float value>
Returns the value of a game setting. The index number can be looked up in a separate text file available at the MGE XE beta page.

xSetGSlong <long GMST_index> <long value>
xSetGSfloat <long GMST_index> <float value>
Sets the value of a game setting, allowing editing mechanics during play. This setting is temporary and does not save with a savegame, nor does it reset on loading a savegame. Therefore it is necessary to reset any changed settings in start script. The index number can be looked up in a separate text file available at the MGE XE beta page.

[ref] xGetBaseHealth
[ref] xGetBaseMagicka
[ref] xGetBaseFatigue
Returns: <float value>
Returns the maximum health, magicka and fatigue of a reference. If the reference is not an actor it returns 0.

[ref] xIsScripted
Returns: <long>
Returns if a referenced entity has a local script. Useful if you want to filter scripted items.

[ref] xLastActorHit
Returns: <ref>
Returns the reference of the actor last hit by the player. Works with melee, ranged and spell attacks. The reference updates after every hit.

[ref] xSetEntityName <string name>
A working replacement for xSetName which allows you to set the base name of any object, meaning all copies of that object will have their names changed. All types of objects are supported. It avoids the problem of crashing on exit that xSetName causes. Changes to names are not saved with a savegame, but do persist through reloads until the game is exited.

[ref] xSetOwner <string npc_id>
Returns: <long>
Sets the current owner of a reference. This function will fail if the reference does not already have extra data, e.g. an existing owner or a script, or if the string is not an NPC ID. Returns 1 if succesful, 0 if failed.

MGEUIShow <long index>
MGEUIHide <long index>
Shows and hides Morrowind HUD elements. Certain elements are turned on automatically in menumode, these are marked with *.

Index  | Element
0        Entire bottom row of HUD
1 *      Health, magic and fatigue cluster
2        NPC health bar (not confirmed working)
3 *      Weapon icon and durability bar
4 *      Magic icon and cast chance bar
5        Active spell effects
6 *      Minimap panel

xSetWeatherSky <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
xSetWeatherFog <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
xSetWeatherAmbient <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
xSetWeatherSun <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
Sets characteristic weather colours.

xSetSunriseSunset <float rise_time> <float rise_duration> <float set_time> <float set_duration>
Sets the daylight cycle. All times are in hours.

xSetWeatherScattering <float outscatter_red> <float outscatter_green> <float outscatter_blue> <float inscatter_red> <float inscatter_geen> <float inscatter_blue>
Sets distant land atmospheric scattering colours.

xSetWeatherGlare <byte weatherID> <float glare>
Sets glare view for a weather type. See morrowind.ini for standard values.

xSetWeatherCloudSpeed <byte weatherID> <float speed>
Sets cloud speed for a weather type. See morrowind.ini for standard values.

xSetWeatherWindSpeed <byte weatherID> <float speed>
Sets wind speed for a weather type. See morrowind.ini for standard values.

MGEEnableShader <string shader_name>
MGEDisableShader <string shader_name>
Enables and disables loaded post-processing shaders. Only shaders set in MGEXEgui will work. <shader_name> should be the shader filename without the file extension.

MGESetShaderFloat <string shader_name> <string var_name> <float value>
MGESetShaderLong <string shader_name> <string var_name> <long value>
MGESetShaderVector <string shader_name> <string var_name> <float x> <float y> <float z> <float w>
Sets shader variables in loaded post-processing shaders. Only shaders set in MGEXEgui will work. <shader_name> should be the shader filename without the file extension.

[ref] xRayTest <float dir.x> <float dir.y> <float dir.z>
Returns: <long hit> <float hit_t>
Performs a raycast from the centre of the target reference in the direction <dir.xyz>. It has two return values: hit will return 1 if it hits anything, or 0 if nothing is in that direction (either sky or void). hit_t will be a ray t-value on a hit, otherwise it will be a large positive floating point value. The t-value is distance relative to the length of <dir.xyz>. hit_t is equal to the distance to the hit if <dir.xyz> is normalized. If the length of <dir.xyz> represents the max search distance, then hit_t <= 1 represents points closer than the length of that search distance. More information about a hit can be retrieved from other functions. The reference is required, as often a ray starting near a model will immediately intersect with the mesh. The function turns off the reference's model temporarily to make sure it does not interfere.

xRayHitPosition
Returns: <float x> <float y> <float z>
Returns the precise calculated hit position on a mesh surface that the last ray hit. For skinned meshes, this is less precise and the mesh is modelled as a cylinder.

xRayHitNormal
Returns: <float nx> <float ny> <float nz>
Returns the precise normal of the triangle that the last ray hit. For skinned meshes, this is less precise and the mesh is modelled as a cylinder.

xRayHitRef
Returns: <ref r>
Returns the reference the last ray hit. Returns 0 if the reference could not be resolved.

[ref] xModelBounds
Returns: <float min.x> <float min.y> <float min.z> <float max.x> <float max.y> <float max.z>
Returns the bounding box extents relative to the centre point of a model, as long as the model is currently loaded and visible in the cell somewhere. The extents are in model local space. Returns all zeroes if the model isn't loaded.

[ref] xTransformVec <float x> <float y> <float z>
Returns: <float x> <float y> <float z>
Returns the position vector transformed to world space using the reference's transform.

[ref] xModelSwitch <string node_name> <long index>
Sets the active child to <index> in a NiSwitchNode with the name <node_name>. <index> is the index of the child in the children array of the node, starting at 0. If <index> is -1, no children are displayed. This command only works on a reference with a loaded model. The game does not save any changes to NiSwitchNode state.
