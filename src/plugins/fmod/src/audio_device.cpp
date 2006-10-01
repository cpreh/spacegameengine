#include <stdexcept>
#include "../audio_device.hpp"
#include "../music.hpp"
#include "../../../core/main/ptr_cast.hpp"

#ifdef SGE_WINDOWS_PLATFORM
#include "../../../core/main/win32_window.hpp"
#endif

sge::fmod::audio_device::audio_device(const unsigned num, const window_ptr w)
{
	if(w)
	{
#ifdef SGE_WINDOWS_PLATFORM
		win32_window* ww = ptr_cast<win32_window*>(w.get());
		if(FSOUND_SetHWND(ww->ge_hwnd()) == false)
			throw std::runtime_error("FSOUND_SetHWND() failed");
#endif
	}
	if(FSOUND_SetDriver(num) == false)
		throw std::runtime_error("Unable to set sound driver");
	if(FSOUND_Init(44100, 32, 0) == false)
		throw std::runtime_error("Unable to init fmod");
}

sge::fmod::audio_device::~audio_device()
{
	FSOUND_Close();
}

sge::music_ptr sge::fmod::audio_device::load_music(const std::string& file)
{
	return music_ptr(new music(file));
}
