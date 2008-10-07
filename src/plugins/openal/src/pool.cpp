#include "../pool.hpp"
#include "../log.hpp"
#include <boost/foreach.hpp>
#include <sge/audio/sound.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

void sge::openal::pool::add(audio::sound_ptr s,bool continue_playing)
{
	sounds.push_back(std::make_pair(s,continue_playing));
}

void sge::openal::pool::update()
{
	for (container_type::iterator s = sounds.begin();
	     s != sounds.end();)
	{
		s->first->update();

		if (!s->first.unique())
		{
			++s;
			continue;
		}

		// do not continue playing after it's gone
		if (!s->second)
		{
			s = sounds.erase(s);
			continue;
		}

		// continue playing
		SGE_ASSERT_MESSAGE(
			s->first->status() != audio::sound_status::paused,
			SGE_TEXT("a paused sound was destroyed but kept alive by the sound pool"));

		if (s->first->status() != audio::sound_status::stopped)
		{
			s++;
			continue;
		}

		SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("deleting stopped sound from pool"));
		s = sounds.erase(s);
	}
}

bool sge::openal::pool::sounds_finished() const
{
	BOOST_FOREACH(sound_type const &s,sounds)
		if (s.first->status() != audio::sound_status::stopped)
			return false;
	return true;
}
