//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_SINGLE_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SINGLE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/single_fwd.hpp>
#include <sge/sprite/buffers/slice_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Choices
>
class single
{
	FCPPT_NONCOPYABLE(
		single
	);
public:
	typedef
	Choices
	choices;

	single(
		sge::sprite::buffers::parameters const &,
		sge::sprite::buffers::option
	);

	~single();

	typedef
	sge::sprite::buffers::slice<
		Choices
	>
	slice_type;

	slice_type
	allocate(
		sge::sprite::count
	);

	sge::sprite::buffers::parameters const &
	parameters() const;
private:
	typedef
	sge::sprite::buffers::object<
		Choices
	>
	buffers_object;

	typedef
	fcppt::optional::object<
		buffers_object
	>
	optional_buffers_object;

	sge::sprite::buffers::parameters const parameters_;

	sge::sprite::buffers::option const buffers_option_;

	optional_buffers_object buffers_object_;
};

}
}
}

#endif
