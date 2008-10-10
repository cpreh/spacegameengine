#ifndef SGE_OPENAL_LISTENER_HPP_INCLUDED
#define SGE_OPENAL_LISTENER_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <sge/audio/listener.hpp>

namespace sge
{
namespace openal
{
class listener : public sge::audio::listener
{
	public:
	void pos(audio::point const &);
	audio::point const pos() const;
	void vel(audio::point const &);
	audio::point const vel() const;
	void direction(audio::angle const &);
	audio::angle const direction() const;
	private:
	audio::point pos_;
	audio::point vel_;
	audio::angle angle_;
};
}
}

#endif
