#include <sge/audio/pool.hpp>
#include <sge/audio/sound.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

sge::audio::pool::pool()
{}

void sge::audio::pool::add(
	audio::sound_ptr const s,
	stop_mode::type const pm)
{
	sounds.push_back(value_type(s,pm));
}

void sge::audio::pool::update()
{
	for (container_type::iterator s = sounds.begin();
	     s != sounds.end();)
	{
		// sound's not dead yet?
		if (!s->first.unique())
		{
			s->first->update();
			s++;
			continue;
		}

		switch (s->second)
		{
			case stop_mode::stop_playing:
			break;
			case stop_mode::continue_playing:
				SGE_ASSERT_MESSAGE(
					s->first->status() != audio::sound_status::paused,
					SGE_TEXT("a paused sound was destroyed but kept alive by the sound pool"));

				if (s->first->status() != audio::sound_status::stopped)
				{
					s++;
					continue;
				}
			break;
			case stop_mode::play_once:
				SGE_ASSERT_MESSAGE(
					s->first->status() != audio::sound_status::paused,
					SGE_TEXT("a paused sound was destroyed but kept alive by the sound pool"));
				
				if (s->first->status() != audio::sound_status::stopped)
				{
					if (s->first->play_mode() != play_mode::once)
					{
						sge::cerr << "got a looping sound, setting to play only once\n";
						s->first->play(play_mode::once);
					}
					s++;
					continue;
				}
			break;
		}

		s = sounds.erase(s);
	}
}

bool sge::audio::pool::sounds_finished() const
{
	BOOST_FOREACH(value_type const &s,sounds)
		if (s.first->status() != audio::sound_status::stopped)
			return false;
	return true;
}
