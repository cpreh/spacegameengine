//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_TEXTURE_MANAGER_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/texture/fragmented_unique_ptr.hpp>
#include <sge/texture/manager_fwd.hpp>
#include <sge/texture/on_alloc_callback.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sge::texture
{

class manager
{
  FCPPT_NONMOVABLE(manager);

public:
  SGE_TEXTURE_DETAIL_SYMBOL
  explicit manager(sge::texture::on_alloc_callback &&);

  SGE_TEXTURE_DETAIL_SYMBOL
  ~manager();

  [[nodiscard]] SGE_TEXTURE_DETAIL_SYMBOL sge::texture::part_unique_ptr
  add(sge::image2d::view::const_object const &);

  SGE_TEXTURE_DETAIL_SYMBOL
  void on_alloc(sge::texture::on_alloc_callback const &);

  SGE_TEXTURE_DETAIL_SYMBOL
  void free_empty_textures();

private:
  sge::texture::on_alloc_callback on_alloc_;

  using fragmented_map =
      std::multimap<sge::image::color::format, sge::texture::fragmented_unique_ptr>;

  sge::texture::manager::fragmented_map textures_;
};

}

#endif
