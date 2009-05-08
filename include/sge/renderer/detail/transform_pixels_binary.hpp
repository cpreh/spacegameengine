#ifndef SGE_RENDERER_DETAIL_TRANSFORM_PIXELS_BINARY_HPP_INCLUDED
#define SGE_RENDERER_DETAIL_TRANSFORM_PIXELS_BINARY_HPP_INCLUDED

#include <cstddef>

namespace sge
{
namespace renderer
{
namespace detail
{

template<
	typename Op
>
class transform_pixels_binary {
public:
	typedef void result_type;

	explicit transform_pixels_binary(
		Op const &op)
	:
		op(op)
	{}

	template<
		typename Src1,
		typename Src2,
		typename Dest
	>
	result_type
	operator()(
		Src1 const &src1,
		Src2 const &src2,
		Dest const &dest) const
	{

		for (std::ptrdiff_t y = 0; y < dest.height(); ++y)
		{
			typename Src1::x_iterator const src1_it = src1.row_begin(y);
			typename Src2::x_iterator const src2_it = src2.row_begin(y);
			typename Dest::x_iterator const dest_it = dest.row_begin(y);
			for (std::ptrdiff_t x = 0; x < dest.width(); ++x)
				op(src1_it[x], src2_it[x], dest_it[x]);
		}
	}
private:
	Op const op;
};

}
}
}

#endif
