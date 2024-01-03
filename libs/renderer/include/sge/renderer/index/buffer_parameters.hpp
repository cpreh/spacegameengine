//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_BUFFER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/dynamic/format.hpp>

namespace sge::renderer::index
{

class buffer_parameters
{
public:
  /**
	\brief Parameters that describe an index buffer

	\param format The format of the indices
	\param count The number of indices the buffer will hold
	\param flags The capabilitiies of the buffer
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  buffer_parameters(
      sge::renderer::index::dynamic::format format,
      sge::renderer::index::count count,
      sge::renderer::resource_flags_field const &flags);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::index::dynamic::format format() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::index::count count() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::resource_flags_field const &flags() const;

private:
  sge::renderer::index::dynamic::format format_;

  sge::renderer::index::count count_;

  sge::renderer::resource_flags_field flags_;
};

}

#endif
