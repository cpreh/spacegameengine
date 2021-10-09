//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED
#define SGE_D3D9_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/program/object_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace cg
{
namespace program
{

class loaded_object : public sge::renderer::cg::loaded_program
{
  FCPPT_NONCOPYABLE(loaded_object);

public:
  loaded_object(IDirect3DDevice9 &, sge::cg::program::object &);

  ~loaded_object();

  void activate() const;

  void deactivate() const;

private:
  IDirect3DDevice9 &device_;

  sge::cg::program::object &program_;
};

}
}
}
}

#endif
