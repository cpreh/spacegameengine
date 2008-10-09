#ifndef SGE_OPENAL_POOL_HPP_INCLUDED
#define SGE_OPENAL_POOL_HPP_INCLUDED

#include <sge/audio/pool.hpp>
#include <sge/audio/sound_fwd.hpp>
#include <utility>
#include <list>

namespace sge
{
namespace openal
{
class pool : public audio::pool
{
	public:
	void add(audio::sound_ptr,bool continue_playing);
	void update();
	bool sounds_finished() const;
	private:
	typedef std::pair<audio::sound_ptr,bool> sound_type;
	typedef std::list<sound_type> container_type;

	container_type sounds;
};
}
}

#endif
