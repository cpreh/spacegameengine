#ifndef SGE_SPRITE_INTRUSIVE_TAG_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_TAG_HPP_INCLUDED

namespace sge
{
namespace sprite
{
namespace intrusive
{

struct tag {
	template<
		typename T
	>
	struct apply
	{
		typedef majutsu::composite<
			boost::mpl::vector2<
				majutsu::role<
					primitives::order_type,
					roles::order
				>,
				majutsu::role<
					primitives::system,
					roles::system
				>
			>
		> type;
	};
};

}
}
}

#endif
