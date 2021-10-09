//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/buffer_base.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::index
{

/**
\brief A buffer for storing indices

An index buffer can hold a fixed amount of indices in a given index format, of
which there are currently two of:

<ul>
<li>16 bit indices</li>
<li>32 bit indices</li>
</ul>

After an index buffer has been created, its size cannot be changed. To store
data in it, it has to be locked first, which will return a view for accessing
the data. Unlocking the buffer will make the update actually take place.

\see sge::renderer::device::create_index_buffer
\see sge::renderer::device::render_indexed
\see sge::renderer::index::const_scoped_lock
\see sge::renderer::index::scoped_lock
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL buffer : public sge::renderer::index::buffer_base
{
  FCPPT_NONMOVABLE(buffer);

protected:
  SGE_RENDERER_DETAIL_SYMBOL
  buffer();

public:
  /**
	\brief Returns the resource flags the buffer has been created with
	*/
  [[nodiscard]] virtual sge::renderer::resource_flags_field resource_flags() const = 0;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::size_type linear_size() const;

  SGE_RENDERER_DETAIL_SYMBOL
  ~buffer() override;
};

}

#endif
