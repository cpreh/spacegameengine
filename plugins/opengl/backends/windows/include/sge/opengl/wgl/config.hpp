//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WGL_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_WGL_CONFIG_HPP_INCLUDED

#include <sge/opengl/wgl/config_fwd.hpp>
#include <sge/opengl/wgl/visual/config.hpp>

namespace sge
{
namespace opengl
{
namespace wgl
{

class config
{
public:
  explicit config(sge::opengl::wgl::visual::config const &);

  sge::opengl::wgl::visual::config const &visual_config() const;

private:
  sge::opengl::wgl::visual::config visual_config_;
};

}
}
}

#endif
