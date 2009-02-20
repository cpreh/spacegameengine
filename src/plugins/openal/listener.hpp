#ifndef SGE_OPENAL_LISTENER_HPP_INCLUDED
#define SGE_OPENAL_LISTENER_HPP_INCLUDED

#include <sge/audio/listener.hpp>
#include <sge/audio/angle.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sge
{
namespace openal
{
class listener : public sge::audio::listener
{
	public:
	listener();
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
