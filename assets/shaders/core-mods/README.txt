This directory contains core shader mods, which are mods applied to the core rendering of MGE XE rendering.

It is possible to copy shader files with names starting with "XE Mod" from the shaders/core directory to the shaders/core-mods directory, where you can edit and experiment with the shader files. They will be loaded as replacements for the corresponding core shader file.

Core mods that fail compilation due to version changes or mistakes will output an error into mgeXE.log. If any core mod fails to work, the game will continue with standard shaders.