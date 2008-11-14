/** 
\page tut_sound Sound
\section abstract Abstract
In this tutorial we create a small sound testing application which plays a
streaming sound (an example of background music for a game) and some non
streaming sounds. We'll not involve any graphical components here and we'll
load just the sound system.

\section sound_nonpos Nonpositional sounds

\subsection sound_single A single sound
In sge the process of loading a sound and playing it is logically separated. 

To <em>load</em> the sound we will create a <em>multi loader</em> which, given a path,
tries all available sound loaders (currently wave, mp1 to mp3 and ogg vorbis) to
load the sound. It'll not load the complete thing into memory unless told to do
so, so don't worry about RAM usage.

To <em>play</em> the sound a system derived from <em>sge::audio::player</em>
must be loaded. To play a sound you first have to decide if this sound should be
a streaming sound or a nonstreaming sound. A nonstreaming sound will be loaded
and kept completely in memory, so it's not appropriate for large sound files
like music. That's what streaming sounds are for.

So here's a small example of an application which uses sound:

\include sound_01.cpp

The code should be pretty self-explanatory. We open the audio file, create a
nonstreaming sound and play it in a loop. Note that for every sound you
create, you have to call 'update' so the sound is updated. In most player
implementations, update does nothing for nonstreaming sounds. For streaming
sounds it updates the buffers and loads more samples.

\subsection sound_multi Multiple sounds

Now suppose you want to load more than one sound file. You'd have to call
<em>update</em> for each sound, which is tedious. So we invented
sge::audio::pool, which is basically just a container for
sge::audio::sound_ptrs, but it can do some more interesting stuff. Let's create
a program which loads two sounds, plays them once and then exits:

\include sound_02.cpp

As you can see, we load two sounds now and, just for the fun of it, one is
created as a streaming sound. The only difference you'll notice is the call to
<em>create_stream_sound</em> instead of <em>create_nonstream_sound</em>.  

Then we add these sounds to the sound pool and play them (this time, only once).
Note that we create the sound_ptrs locally. When the inner block in
<em>main</em> ends, only the pool has ownership of the sounds. The second
argument to sge::audio::pool::add specifies that the sound should continue
playing until it's finished after it's deleted in the main program. This way you
don't have to write extra code for, say, an enemy which is dying and has to
finish its dying sound until it can be deleted. Just <em>play</em> the sound,
put it in the pool and delete the enemy object. The sound will be deleted when
it's finished playing.

Also note the call to <em>sounds_finished</em>. This returns true if all sounds
have finished playing. 

\section sound_pos Spacialization

One thing you might need if you design a 3D application is spacialization so a
sound-emitting object which is far away isn't as well audible as a sound which
is directly in front of you. Spacialization also involves using all available
speakers to indicate sound locations and to create more immersion.

\note In sge, spacialization (currently) only works with <em>mono</em> sound
sources! It does not matter, however, if the sound is streaming or not.

Each sge::audio::player you create has exactly one sge::audio::listener attached
to it. You can get a reference to the listener with the
sge::audio::player::listener method. This object has functions like <em>pos</em>
to change the position and <em>angle</em> to change the listener angle. 

\note Angles in sge::audio are denoted by two vectors, a forward vector and an
up vector. Both vectors form the struct sge::audio::angle.

Each sound not only has a position and an angle but also a <em>cone</em>
attached to it so you can narrow the sound's propagation (a ). But before those
values are taken into consideration, you have to set the sound to be a
"positional" sound with the sge::audio::sound::positional method.

Another important source parameter is the "rolloff factor". To understand this
parameter, you have to know that sge::audio currently uses the "inverse distance
rolloff attenuation model". Sounds complicated, but it's rather easy to
describe. The volume of a sound is calculated using this formula:

\f[
v = \frac{1}{1+r(d-1)}
\f]

Where \f$v\f$ is the volume (also called <em>gain</em>), \f$r\f$ is the rolloff
factor and \f$d\f$ is the sound distance from the listener. The default rolloff
factor is 1 for every source, so a sound which is 3 "units" away has about 33%
of it's original volume.

Here's a small application which uses spacialization to rotate the sound in a
circle round the listener.

\include sound_03.cpp

\note The default listener angle is (0,0,1) forward and (0,1,0) up, so facing
down the positive Z axis. Its default position ist (0,0,0). Same goes for each
sound source (a source is non-positional by default).

Lastly, each sound and the listener have an attribute <em>velocity</em> which is
used for doppler effect calculations. To modify the doppler behaviour the
sge::audio::player has a method sge::audio::player::speed_of_sound which is
about 343 by default -- according to the real speed of sound in normal air at a
temperature around 20 degrees celsius.
*/
