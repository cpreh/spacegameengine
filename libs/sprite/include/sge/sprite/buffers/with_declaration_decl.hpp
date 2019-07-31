//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_WITH_DECLARATION_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_WITH_DECLARATION_DECL_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters_fwd.hpp>
#include <sge/sprite/buffers/with_declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Buffers
>
class with_declaration
{
	FCPPT_NONCOPYABLE(
		with_declaration
	);
public:
	with_declaration(
		sge::renderer::device::core &,
		sge::sprite::buffers::option
	);

	~with_declaration();

	typedef
	Buffers
	buffers_type;

	typedef
	typename
	buffers_type::choices
	choices;

	typedef
	typename
	buffers_type::slice_type
	slice_type;

	slice_type
	allocate(
		sge::sprite::count
	);

	sge::sprite::buffers::parameters const &
	parameters() const;

	buffers_type &
	impl();

	buffers_type const &
	impl() const;
private:
	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration_;

	buffers_type buffers_;
};

}
}
}

#endif
