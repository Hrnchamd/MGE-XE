
MGE XE 0.14.1
-------------
Released 2022-06-12

Source available at https://github.com/Hrnchamd/MGE-XE
Licensed under GPL v2 https://github.com/Hrnchamd/MGE-XE/blob/master/license.txt


Summary
-------

A graphics improvement add-on to the Morrowind engine, for longer viewing distances, great sunsets, fine shaders and better lighting. Supports MWSE 2.1, included as part of the installer, so that the newest Lua gameplay mods work straight away. As an engine mod, this is not compatible with OpenMW.


Requirements
------------

Morrowind GOTY or Bloodmoon fully patched.
Any graphics card made since 2009 or so.
Windows Vista SP2 or later (Windows XP is not supported since MGE XE 0.11.2).
Morrowind Code Patch, if you want to use MWSE.


Major features
----------------

MGE XE provides:

- Resolution and FoV configuration.
- MWSE 2.1 support. Amazing new mods have full access to customize Morrowind's UI and gameplay mechanics.
- Distant world rendering. As long or short a viewing distance as you want, with spectacular atmospheric colourations.
- New water rendering, with simulated ripples from the player and from raindrops.
- Solar shadows, that smoothly update with the time of day.
- Shaders like SSAO, Sunshafts, and HDR.
- Per-pixel lighting. For better performing graphics cards, it improves the rendering of lights and and fixes colour shifts caused by the old engine.

The main feature is the distant world. The MGE XE program takes your mod list, and builds a lower detail version that can be used to render the distant world in-game. It's built by the "Distant land generator wizard" on the Distant land tab. You'll need to re-run the generator if you add or remove any mods that change the world, otherwise the distant world will appear out of date compared to your mods.

The new water, shadows, and lighting are integrated into distant land. They are all dependent on the distant world data to know about the world beyond the area near the player. So, generate distant land and all these features will be available.


Install
-------
1. If you are using the CD version of Morrowind, please install Morrowind to a directory outside of Program Files to avoid issues. If you are interested in MWSE 2.1 and Lua mods, you must first install Morrowind Code Patch (https://www.nexusmods.com/morrowind/mods/19510/). The bugfixes it provides are required for MWSE.

2. Run the MGE XE installer. It will add a new configuration program, MGE XE, to your Morrowind directory and to the Morrowind section of your start menu. All Visual C++ and DirectX updates are now included in the installer.

You will be given the choice to update MWSE in the installer, which requires internet access. For a manual installation, extract the archive files to your Morrowind directory and run MWSE-Update.

3. Run the main MGE XE program, which sets all the graphics configuration. If you're using Mod Organizer 2, you need to run MGEXEgui from within MO2, as it generates files inside Morrowind's Data Files directory.

Configure your graphics setting in the 'Graphics' tab, and generate distant land in the 'Distant Land' tab. There is an instruction tab for further details. If later on you add world-changing mods to your mod list, you will need to re-run the generator to see the changes in the distant world.

(NEW) Many settings can be adjusted within the game, where you will be able to see the effect of your changes in real-time. This requires MWSE. Press Esc, click on 'Mod Options', then select MGE XE from the mods list. You can then open the settings window with the button, which will hide all other windows to show a full preview of the world. There are several tabs in the window, and the configuration can be loaded and saved.

4. If you use Steam, you should turn off the Steam overlay (in Steam, right click Morrowind > Properties). If you use Crossfire/SLI, turn off "Pause world rendering in menus" in the In-game tab, to avoid performance reductions, as this feature is SLI unfriendly.

5. There is an optional mod, 'XE Sky Variations', that will randomize the sky colour and sunrise/sunset every day. It requires "High quality atmosphere" enabled in distant land, and MWSE installed and enabled.

As a complement to the UI scaling, you may also want to use Better Dialogue Font for sharper menu text.
Download at: https://www.nexusmods.com/morrowind/mods/36873


Upgrading
---------
When upgrading from a previous MGE XE: Run the installer, or manually extract the archive to the Morrowind directory. Run MGEXEgui and regenerate distant land. Run MWSE-Update if you installed manually.

Custom modded shaders you've installed may or may not be compatible, so you should check with the authors for an update, test it yourself by checking mgeXE.log after the game for error messages, or stick to the default shaders.


Uninstall
---------
Uninstall from Control Panel or by running uninstall_MGEXE.exe. If you installed manually, delete MGEXEgui.exe, d3d8.dll, dinput8.dll and the mge3 directory.


You might want to know
----------------------

MGE XE includes an install option for MWSE 2.1 beta by NullCascade. ( https://github.com/MWSE/MWSE/ ) MWSE mods are therefore supported while you are using MGE XE; the MWSE launcher is not required. MWSE is receiving regular fixes and improves, and can be updated by running MWSE-Update.exe in the Morrowind directory. For MWSE mod support you should contact the mod author.

Many rendering settings can be changed in-game using the MGE XE mod options window, which is new in v0.14. A lot of settings are now dynamically adjustable.

Post-processing shaders now auto-sort into the correct order, when the file is tagged with a category. You will see the category when you add the shader to the active list. The standard shaders are already categorized, but other shaders will need an update. Further details on this system are in the readme in Data Files/shaders/XEshaders.

Shader core mods. It's possible to edit MGE XE rendering if you know HLSL. This mod system replaces the previous strategy of replacing the core shaders, that ensured problems on upgrade. If a shader mod does not compile, the game continues with standard shaders, and you get a visible warning.

To start modding, examine the shaders in Data Files/shaders/core/; any file that starts with "XE Mod" can be copied to the Data Files/shaders/core-mods/ directory. Shaders in core-mods will override the standard rendering when present. They can be distributed in your mods safely, and can be simply deleted once they are no longer needed.


Problems?
---------
If you get a message in game "MGE XE serious error condition. Exit Morrowind and check mgeXE.log for details.", you can see the log file by clicking the "Show mgeXE.log" button in the Config tab of MGEXEgui. You may be able to discover what's wrong from the error message.

Questions and support thread at #troubleshooting channel on discord. https://discord.me/mwmods

Reporting in game crashes: Open MGEXEgui, on the Config tab click "Show last mgeXE.log". Add it to your report.

Reporting distant land generator crashes: Open MGEXEgui, on the Config tab click "Show DL generator log". Add it to your report.


Credits
-------
Many people have worked on MGE over the years, and the sum of their ideas and hard work implementing them has improved Morrowind by a huge amount. MGE XE is based on the MGE code.

MGE was written by Timeslip, LizTail, Krzymar, and Phal. MGE XE is currently being developed by Hrnchamd.
Thanks to the Morrowind community for all the inspiration and feedback.


Changelog (newest first)
---------
0.14.1
- Fix main menu video background mods failing to play.
- Updated French localization, thanks to Redondepremière.
- Help button now points to nexusmods.

0.14.0
- Distant land loads before the main menu, instead of the first time you load a game. This allows earlier script access to MGE XE functions.
- MGE XE settings can now be controlled in-game through MWSE. It's available on the Mod Config options page, and opens a separate window. The rendering will update in real-time as you change options, so that you can compare the difference.
- Shaders can now have category annotations which are designed to help sort shaders into the correct rendering order. If the shader has a category specific within it, the category name will appear when a shader is added to the active list, and that shader will auto-sort into place.
- Added an API interface to allow MWSE to control MGE XE, including runtime shader loading and variables support. See MWSE docs for details.
- The very far static distance no longer rounds to the nearest integer on load/save.

0.13.7
- Distant land generator now selects the LOD detail at 1 cell distance from models that contain LOD nodes.
- Fix distant land generator crash when handling some configurations of LOD nodes.

0.13.6
- Distant land generator has improved compatibility with systems using languages with multi-byte character encodings (such as Shift-JIS). For these systems, it should be much less likely to fail generation or to generate corrupted distant land.
- Distant land generator now selects the lowest detail LOD from models that contain LOD nodes (mods like Morrowind Optimization Patch).
- Prevented special wireframe and stencil effects from affecting shaders and other effects rendering.
- Fixed a rendering issue with some texture decals generating incorrect lighting and extra shadows on the object they are applied to.

0.13.5
- Small change to distant land generation to avoid distant rendering issues in end game interior cells.
- Distant land generator should no longer generate toolbar related exception pop-ups.
- Updated GUI resolution selector. Largest resolutions appear first. It should display the intended warning if the resolution could not be changed.

0.13.4
- Fixed some distant interiors cells not rendering as distant. An issue with the distant generator output could cause the game to fail to load some distant interiors in some cases. Regenerate distant land for this fix.
- Minor fix to per-pixel lighting. Checks how many UV sets are actually used before failing with purple rendering output and a warning. Some models have >4 UV sets for no reason.

0.13.3
- Fixed excessive heavy fog in storms, blizzards, and foggy weather, particularly if using short draw distances. Storms now have a minimum visibility distance comparable to vanilla.
- Minor fix to per-pixel lighting. Supports up to 4 UV sets in NIFs, and logs a warning if there are more than it can handle.

0.13.2
- Fixed an issue with exponential fog which caused near rendering to be all black, when the effective draw distance is high (clear weather, draw distance > 16 or high custom fog start distance).
- The lantern of the chargen boat no longer appears in reflections when the boat is gone.
- Tuned sunrise/sunset slightly to reduce banding from over-saturation.

0.13.1
- Actually updated French localization, thanks to Redondepremière. Accidentally did not get included in 0.13.0.
- Fixed nearly all distant landscape heightfield artifacts, which were appearing as terrain glitches. Land bias changes are no longer required.
- Reworked HDR shader to functionally brighten dark scenes, while having minimal effects on bright scenes. Adapts to brightness quickly, but dark vision takes more time to adapt to. Should make dark areas of the game more playable.
- Changed sky scattering to transition from sunrise colours to a blue sky more quickly after sunrise. Updated distant land fog to blend better with near fog, which was noticable with shorter view distances.
- Changed automatically set distant statics distances to a minimum of 4 cells, to minimize near pop-in.
- Disable exponential fog if distant land is initially off. Makes sure the water shader has the correct fog mode when distant land is intended to be off.

0.13.0
- Adjusted high quality sky scattering to create an overall brighter sky. Aims for a bright and vibrant blue during the day, and a more intense sunrise/sunset.
- Rendering bias for distant land and water improved. Unfortunately this means water shader mods have to be updated to render correctly.
- Exponential fog now uses an auto distance multiplier that fades exactly to the fog colour at fog end distance. Tthe multiplier has been removed from configuration. The auto distance function for near fog is tuned for better near visibility while retaining atmosphere.
- Capture screenshots with or without UI, depending on shift key. Using shift always captures UI.
- Correct issue with SSAO making fogged objects slightly lighter, in good weather with sky scattering, where draw distance was <8 cells.
- Updated grass shader stomp effect to fade out if the player is high above. A little generous on height difference to account for different grass mods.
- Updated French localization, thanks to Redondepremière.

0.12.1
- Shader core-mods support added. Instead of overwriting core shaders, shader mod fragments can be placed into the Data Files\shaders\core-mods directory. The game will integrate them into rendering, and if they don't work, will fall back to un-modded rendering instead of breaking.
- Fixed single frame of incorrect fog when changing cells, or after loading a game.
- Distant statics generator is less likely to hang on statics generation.
- Fixed a crash that occurred when the game produced a large amount of particles in a single particle system, and MGE XE wasn't handling it properly.
- Visual C++ 2010 runtime is properly packaged with the installer.

0.12.0
- Nearly all crashes related to Alt-Tabbing and changing resolution in-game are fixed.
- Distant landscape texture quality has been improved by a more accurate simulation of Morrowind land rendering. The distant land texture now aligns perfectly with Morrowind land texturing.
- Distant landscape should now be less likely to clip through near statics and appear blocky.
- Distant landscape texture is atlased, so that widely separated landmass mods don't cause distant world detail loss.
- Distant land generator can now detect and generate distant interiors for large interior cells (on by default). Previously you have to manually add interiors to a statics override file.
- Distant land generator now selects at least Very High mesh quality when automatically calculated settings are used.
- Distant interiors rendering improvements. Distant interior "sunlight" matches Morrowind's more closely. Interior fog changes fixes pop-in occurring in interiors without water. For large cells the fog uses the distant interiors setting, for small cells it uses the default Morrowind fog.
- During statics generation, NiCollisionSwitch nodes are handled correctly and won't produce niflib errors.
- Distant land generator minor stability improvements.
- Per-pixel lighting eliminates extra dark shadow rendering artifacts on the joints of characters. With normal lighting, artifacts are reduced but still present. This is ideally addressed by mesh fixes.
- Per-pixel lighting has improved support for effects. Added rendering support for alpha vertex colours used with alpha textures, dark map alpha channel, and projective texturing with NiTextureEffect (maximum 1 projective texture effect).
- Some GUI usability improvements.
- Morrowind icon will no longer randomly disappear from the taskbar when minimized.
- Updated Polish and Russian localizations.

0.11.6
- Fixed possible crash when saving PNG screenshots.
- Sunshafts sun disc has its sharpness reduced slightly.
- MWSE will be loaded if not specifically disabled, even when MGE is disabled. This is returning to how it behaved in 0.10.

0.11.5
- Neutralized nearly all performance loss caused by changes to rendering since 0.10.1, mainly in dense environments like cities. The frame rate in cities is a significant improvement over 0.11.4, and within -4 to +1% of 0.10.1.
- Saving PNG screenshots now take around 0.1 seconds instead of 1 to 2 seconds.
- Possibly fixed random and rare pixelated rendering appearing in screenshots.
- Fixed frame rate display possibly stuck on 0.

0.11.4
- Fixed broken replacement water rendering when distant land is off. It also now receives fog correctly.
- Fixed "Unable to sort..." exception in the Distant Land generator.
- Fixed system-specific possibility of hanging on the first frame of loading the game.
- Added MWSE weather commands for fog and PPL lighting.

0.11.3
- Fixed being unable to start MGEXEgui on a fresh install.

0.11.2
- Distant land texture generation stability fixes. Outdated two-stage option removed.
- Dynamic lighting coefficients reset button is now aware of per-pixel lighting defaults.
- MGEXEgui handles modifying morrowind.ini correctly, not writing a BOM when running latest .NET versions.
- Some code quality upgrades. May slightly lower the chance of crashes in-game.

0.11.1
- Forgot to include XE Sky Variations.

0.11.0
- Installer added. Optionally downloads MWSE 2.1. Sets registry so that Morrowind settings will not randomly reset.
- 4GB patch applied to MGEXEgui.
- Fixed engine bug which caused slow mouse movement and dropped inputs when frame rate was too high (e.g. in small interiors).
- Fog blending with distant land in fog, rain and storms greatly improved.
- Distant water fogging improved.
- Distant statics generator handles incorrect NIFs better and most hangs are solved, making generation faster.
- Distant statics generator displays current processing NIF to help find bad NIFs.
- Rendering improved to avoid cracks in some modded skinned meshes.
- Distant water horizon blends well at all view distances.
- Dynamic ripples wave border artifacts fixed. Ripple simulation pauses in menu mode.
- Shaders like SSAO/DoF no longer glitch when equipping inventory items in the menu.
- HDR shader has a slightly wider range of brightness adaptation.
- SSAO shaders behave better in fog, and no longer have artifacts on more distant objects.
- Sunshafts shader now has a more consistent sun disc size and brightness.
- Distant land generator texture size limit increased to 8192. Only recommended when using mods with added landmass.
- Multiple component buildings like Vivec cantons will now appear in one piece once in distant land view range, instead of the component parts appearing separately.
- Changed FPS limiter range limit back to 240.
- Auto FOV is now a mode toggle, and on by default.
- No longer gives a renderer error when using 2x or higher vsync in windowed mode.
- Distant land and FFE shaders can be live reloaded by toggling distant land, post shaders can be live reloaded by toggling shaders.

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
- Fixed sunflare over-brightness with per-pixel lighting.
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
GetWeatherScattering
SetWeatherScattering
SetWeatherGlare
SetWeatherCloudSpeed
SetWeatherWindSpeed
GetWeatherDLFog
SetWeatherDLFog
GetWeatherPPLLight
SetWeatherPPLLight

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
Sets the current owner of a reference. This function will fail if the reference does not already have extra data, e.g. an existing owner or a script, or if the string is not an NPC ID. Returns 1 if successful, 0 if failed.

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

xGetWeatherScattering
Returns: <float outscatter_red> <float outscatter_green> <float outscatter_blue> <float inscatter_red> <float inscatter_geen> <float inscatter_blue>
Gets distant land atmospheric scattering colours.

xSetWeatherScattering <float outscatter_red> <float outscatter_green> <float outscatter_blue> <float inscatter_red> <float inscatter_geen> <float inscatter_blue>
Sets distant land atmospheric scattering colours.

xSetWeatherGlare <byte weatherID> <float glare>
Sets glare view for a weather type. See morrowind.ini for standard values.

xSetWeatherCloudSpeed <byte weatherID> <float speed>
Sets cloud speed for a weather type. See morrowind.ini for standard values.

xSetWeatherWindSpeed <byte weatherID> <float speed>
Sets wind speed for a weather type. See morrowind.ini for standard values.

MGEGetWeatherDLFog <byte weatherID>
Returns: <float fogDistMultiplier> <float fogOffsetPercent>
Gets distant land fog parameters for a specific weather. See MGESetWeatherDLFog.

MGESetWeatherDLFog <byte weatherID> <float fogDistMultiplier> <float fogOffsetPercent>
Sets distant land fog parameters for a specific weather. fogDistMultiplier is multiplied by the "Above water fog" distance to get the fog distance for that weather. It has a range of [0, 2]. fogOffsetPercent is the percentage of fog applied at zero distance from the camera. It has a range of [0, 90].

MGEGetWeatherPPLLight <byte weatherID> -> <float sunMultiplier> <float ambientMultiplier>
Gets per-pixel lighting parameters for a specific weather. See MGESetWeatherPPLLight.

MGESetWeatherPPLLight <byte weatherID> <float sunMultiplier> <float ambientMultiplier>
Sets light multipliers used in per-pixel lighting for a specific weather. sunMultiplier affects sunlight, ambientMultiplier affects ambient lighting.

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
