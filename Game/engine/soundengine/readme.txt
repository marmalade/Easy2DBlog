SoundEngine
-----------

Sound engine provides a wrapper around Marmalade System's sound API, allowing it
to interact with Marmalade Studio's IwResManager resource management system.

It also uses a sound generation callback to provide ADPCM compressed sound that
is decompressed on the fly.

SoundEngine.mkf cannot be built directly, it must be included in a project mkb
using the subproject directive.

This is a modified version of the original soundengie that is shipped with the 
Marmalade SDK. It supports play back of sound effects directly from WAV files 
without the need to go through the resource manager.
