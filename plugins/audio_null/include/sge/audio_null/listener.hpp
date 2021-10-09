//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_NULL_LISTENER_HPP_INCLUDED
#define SGE_AUDIO_NULL_LISTENER_HPP_INCLUDED

#include <sge/audio/listener.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/direction/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::audio_null
{

class listener : public sge::audio::listener
{
  FCPPT_NONMOVABLE(listener);

public:
  listener();

  ~listener() override;

private:
  void position(sge::audio::vector const &) override;

  void linear_velocity(sge::audio::vector const &) override;

  void direction(sge::audio::direction::object const &) override;
};

}

#endif
