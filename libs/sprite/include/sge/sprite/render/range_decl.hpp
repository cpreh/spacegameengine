//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_RENDER_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/detail/render/range_object.hpp>
#include <sge/sprite/render/range_fwd.hpp>
#include <sge/sprite/render/range_part_decl.hpp>
#include <sge/sprite/render/range_part_vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices
>
class range
{
	FCPPT_NONCOPYABLE(
		range
	);
public:
	typedef
	sge::sprite::detail::render::range_object<
		Choices
	>
	range_object;

	typedef
	sge::sprite::render::range_part<
		Choices
	>
	range_part_type;

	typedef
	sge::sprite::render::range_part_vector<
		Choices
	>
	range_part_vector;

	range();

	range(
		range_object const &,
		range_part_vector &&
	);

	range(
		range &&
	);

	range &
	operator=(
		range &&
	);

	~range();

	typedef
	fcppt::optional::reference<
		range_object const
	>
	optional_object;

	optional_object const &
	object() const;

	range_part_vector const &
	parts() const;
private:
	optional_object object_;

	range_part_vector range_parts_;
};

}
}
}

#endif
