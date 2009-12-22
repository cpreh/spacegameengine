#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/container/field.hpp>
#include <sge/log/headers.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/window/parameters.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <sge/iconv.hpp>
#include <fcppt/lexical_cast.hpp>
#include <sge/assert.hpp>
#include <sge/exception.hpp>
#include <sge/optional_impl.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/foreach.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <exception>
#include <limits>
#include <string>
#include <algorithm>
#include <cstddef>
#include <cmath>

#include <mizuiro/color/for_each_channel.hpp>

#define FOREACH_BEGIN(channel, object)\
{\
	class applier {\
	public:\
		typedef void result_type;\
		\
		template<\
			typename channel\
		>\
		result_type \
		operator()(\
			channel &\
		) const {\

#define FOREACH_END()\
		}\
	};\
	\
	mizuiro::color::for_each_channel<\
		BOOST_TYPEOF(object)::layout\
	>(\
		applier()\
	);\
}

template<typename T>
T square(T const &t)
{
	return t*t;
}

template<typename T>
T cube(T const &t)
{
	return t*t*t;
}

// This applies a sigmoid function which satisfies:
// f(0)=0
// f(1)=1
// f'(0)=0
// f'(1)=0
template<typename T>
typename
boost::enable_if<
	boost::is_floating_point<T>,
	T>::type
sigmoid(T const &x)
{
	return static_cast<T>(3)*square(x)-static_cast<T>(2)*cube(x);
}

template<typename T>
typename
boost::enable_if<
	boost::is_floating_point<T>,
	T>::type
logistic(
	T const &x,
	T const &h)
{
	T const exponent =
		-((x*static_cast<T>(16))-static_cast<T>(8))/h;

	return
		static_cast<T>(1)/
		(static_cast<T>(1)+std::exp(exponent));
}

// TODO: replace these with mizuiro::color::(de)normalize!
template<typename Float,typename Input>
typename
boost::enable_if<
	boost::is_floating_point<Float>,
	Float>::type
normalize(Input const &x)
{
	Float const denominator =
		static_cast<Float>(
				std::numeric_limits<Input>::max())-
			static_cast<Float>(
				std::numeric_limits<Input>::min());

	return
		static_cast<Float>(x)/
		denominator;
}

template<typename Output,typename Float>
typename
boost::enable_if<
	boost::is_floating_point<Float>,
	Output>::type
denormalize(Float const &x)
{
	Float const factor =
		static_cast<Float>(
				std::numeric_limits<Output>::max())-
			static_cast<Float>(
				std::numeric_limits<Output>::min());

	return static_cast<Output>(
		x*
		factor);
}

template<
	typename Color
>
struct field_increase_contrast_channel {

	field_increase_contrast_channel(
		Color &c,
		double const coefficient
	)
	:
		c(c),
		coefficient(coefficient)
	{}

	typedef void result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T &
	) const
	{
		c. template set<T>(
			denormalize<typename Color::layout::channel_type>(
				fcppt::math::clamp(
					logistic<double>(
						normalize<double>(
							c. template get<T>()
						),
						coefficient
					),
					0.0,
					1.0
				)
			)
		);
	}
private:
	Color &c;
	double const coefficient;
};

template<typename T>
void field_increase_contrast(
	sge::container::field<T> &f,
	double const coefficient)
{
	typedef sge::container::field<T> field_type;
	typedef T color_type;
	typedef typename T::layout::channel_type channel_type;

	BOOST_FOREACH(T &c,f)
	{
		mizuiro::color::for_each_channel<
			typename T::layout
		>(
			field_increase_contrast_channel<
				color_type
			>(
				c,
				coefficient
			)
		);
	}
}

template<typename T>
typename
boost::enable_if<
	boost::is_floating_point<T>,
	T>::type
gauss_stddev(
	T const radius,
	T const range)
{
	// 2*log(1/range)
	T denom =
		static_cast<T>(2)*std::log(range);

	// little hack, just add 1
	//r = r + static_cast<U>(1);
	// sqrt(-r^2/(2*log(1/255)))
	return
		std::sqrt(
			-square(radius)/
			denom);
}

template<typename T>
typename
boost::enable_if<
	boost::is_floating_point<T>,
	T>::type
bell_curve(
	T const stddev,
	T const center,
	T const x)
{
	// 1/(stddev*sqrt(2*pi))
	T const prefix =
		static_cast<T>(1)/
		(stddev*std::sqrt(static_cast<T>(2)*fcppt::math::pi<T>()));

	// 1/(2*stddev^2)
	T const eprefix =
		-static_cast<T>(1)/
		(static_cast<T>(2)*square(stddev));

	T const pos = x - center;

	return
		prefix *
		std::exp(
			square(pos)*
			eprefix);
}

template<
	typename It>
typename
boost::enable_if<
	boost::is_floating_point<
		typename std::iterator_traits<It>::value_type>,
	void>::type
fill_with_gauss(
	It i,
	It const e)
{
	typedef typename std::iterator_traits<It>::difference_type difference_type;
	typedef typename std::iterator_traits<It>::value_type value_type;

	difference_type const span =
		std::distance(
			i,
			e);

	SGE_ASSERT((span - 1) % 2 == 0);

	value_type const r =
		static_cast<value_type>(
			span/2);

	value_type const stddev =
		gauss_stddev(
			r+
			static_cast<value_type>(1),
			static_cast<value_type>(1.0/255.0));

	difference_type x =
		0;

	for (;i != e; ++i)
	{
		*i =
			bell_curve(
				stddev,
				r,
				static_cast<value_type>(x));
		++x;
	}
}

template<
	typename T,
	typename U,
	typename Combine>
void field_combine(
	sge::container::field<T> &left,
	sge::container::field<U> const &right,
	Combine c)
{
	SGE_ASSERT(left.dim() == right.dim());

	typename sge::container::field<T>::iterator li = left.begin();
	typename sge::container::field<U>::const_iterator ri = right.begin();

	while (li != left.end() && ri != right.end())
	{
		for (unsigned i = 0; i <= 3; ++i)
			(*li)[i] = c((*li)[i],(*ri)[i]);

		++li;
		++ri;
	}
}

template<typename T>
void field_gaussian_blur(
	sge::container::field<T> &f,
	typename sge::container::field<T>::dim_type const radii)
{
	typedef T value_type;
	typedef sge::container::field<T> field_type;
	typedef typename field_type::size_type size_type;
	typedef typename field_type::iterator iterator;
	typedef typename T::layout::channel_type channel_type;

	typedef std::vector<T> color_container;
	typedef typename color_container::size_type color_size_type;

	typedef std::vector<double> value_container;
	typedef typename value_container::size_type value_size_type;

	value_size_type const
		xd = static_cast<value_size_type>(2*radii.w()+1),
	  yd = static_cast<value_size_type>(2*radii.h()+1);
	value_container
		gx(xd),
		gy(yd);
	fill_with_gauss(
		gx.begin(),
		gx.end());
	fill_with_gauss(
		gy.begin(),
		gy.end());

	color_container
		row(f.dim().w()),
		col(f.dim().h());

	for (size_type y = 0; y < f.dim().h(); ++y)
	{
		// save row
		iterator b = f.position_it(
			typename field_type::vector_type(0,y));
		std::copy(
			b,
			b+f.dim().w(),
			row.begin());

		for (size_type x = 0; x < f.dim().w(); ++x)
		{
			size_type const hw = xd/2;

			size_type const cxb = (x < hw) ? (hw-x) : 0,
			                cxe = (x >= f.dim().w()-hw) ? xd-(x-(f.dim().w()-hw)+1) : xd;

			T &cur_pixel =
				f.pos(typename field_type::vector_type(x,y));
			for (unsigned i = 0; i <= 3; ++i)
			{
				channel_type const cur = row[x][i];
				channel_type sum = static_cast<channel_type>(0);

				for (size_type cx = 0; cx < xd; ++cx)
				{
					if (cx < cxb || cx >= cxe)
						sum += cur * gx[cx];
					else
						sum += row[x-hw+cx][i] * gx[cx];
				}

				cur_pixel[i] = sum;
			}
		}
	}

	for (size_type x = 0; x < f.dim().w(); ++x)
	{
		// save column
		for (size_type y = 0; y < f.dim().h(); ++y)
			col[y] = f.pos(typename field_type::vector_type(x,y));

		for (size_type y = 0; y < f.dim().h(); ++y)
		{
			const size_type hh = yd/2;

			const size_type cyb = (y < hh) ? (hh-y) : 0,
			                cye = (y >= f.dim().h()-hh) ? yd-(y-(f.dim().w()-hh)+1) : yd;

			T &cur_pixel =
				f.pos(typename field_type::vector_type(x,y));

			for (unsigned i = 0; i <= 3; ++i)
			{
				const channel_type cur = col[y][i];
				channel_type sum = static_cast<channel_type>(0);
				for (size_type cy = 0; cy < yd; ++cy)
				{
					if (cy < cyb || cy >= cye)
						sum += cur * gy[cy];
					else
						sum += col[y-hh+cy][i] * gy[cy];
				}

				cur_pixel[i] = sum;
			}
		}
	}
}

template<typename T>
T clamping_adder(T const &left,T const &right)
{
	//return left+right;
	return static_cast<T>(
		fcppt::math::clamp(
			left+right,
			std::numeric_limits<T>::min()+left-left,
			std::numeric_limits<T>::max()+left-left));
}

int main(int argc,char *argv[])
try
{
#if 0
	if (argc < 2)
	{
		sge::cerr << FCPPT_TEXT("please specify an input file\n");
		return EXIT_FAILURE;
	}

	unsigned blur_radius =
		argc == 3
		? sge::lexical_cast<unsigned>(std::string(argv[2]))
		: 16;

	sge::log::global().activate_hierarchy(
		sge::log::level::debug);
	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::image));

	sge::image::file_ptr const
		bg(
			sys.image_loader()->load(
				sge::iconv(argv[1]
			)
		)
	);

	typedef sge::image::color::rgba8 color_type;
	typedef sge::container::field<color_type> color_field;

	color_field f(
		fcppt::math::dim::structure_cast<color_field::dim_type>(
			bg->dim()
		)
	);

	sge::image::view::object const view(
		sge::image::view::make(
			reinterpret_cast<unsigned char *>(
				&(*f.begin())
			),
			fcppt::math::dim::structure_cast<
				sge::image::dim_type
			>(
				f.dim()
			),
			sge::image::color::format::rgba8,
			sge::image::view::optional_pitch()
		)
	);

	sge::image::algorithm::copy_and_convert(
		bg->view(),
		view
	);

	color_field original = f;

	field_increase_contrast(
		f,
		0.8);

	field_gaussian_blur(
		f,
		color_field::dim_type(
			blur_radius,
			blur_radius));

	field_combine(
		f,
		original,
		&clamping_adder<
			color_field::value_type::layout::channel_type
		>
	);

	sys.image_loader()->create(
		sge::image::view::make_const(
			view
		)
	)->save(
		FCPPT_TEXT("output.jpg")
	);
#endif
}
catch(sge::exception const &e)
{
	sge::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
