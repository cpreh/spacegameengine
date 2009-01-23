#ifndef SGE_AUDIO_POOL_HPP_INCLUDED
#define SGE_AUDIO_POOL_HPP_INCLUDED

#include "stop_mode.hpp"
#include "sound_fwd.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace audio
{
class SGE_CLASS_SYMBOL pool : public boost::noncopyable
{
	public:
	SGE_SYMBOL void add(sound_ptr,stop_mode::type);
	SGE_SYMBOL void update();
	SGE_SYMBOL bool sounds_finished() const;
	private:
	typedef std::pair<sound_ptr,stop_mode::type> value_type;
	typedef std::vector<value_type> container_type;

	container_type sounds;
};

}
}

#endif
