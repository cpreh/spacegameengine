#ifndef SGE_GUI_UTILITY_CHANNEL_ADDER_HPP_INCLUDED
#define SGE_GUI_UTILITY_CHANNEL_ADDER_HPP_INCLUDED

namespace sge
{
namespace gui
{
namespace utility
{
template<class Pixel0,class Pixel1,class PixelResult>
class channel_adder 
{
public:
	channel_adder(
		Pixel0 const &p0,
		Pixel1 const &p1,
		PixelResult &result);

	template<class T>
	void operator()(T &) const;
private:
	Pixel0 const &p0,
	Pixel1 const &p1;
	PixelResult &result;
};
}
}
}

template<class Pixel0,class Pixel1,class PixelResult>
sge::gui::utility::channel_adder<Pixel>::channel_adder(
	Pixel0 const &p0,
	Pixel1 const &p1,
	PixelResult &result)
: p0(p0),
  p1(p1),
	result(result)
{}

template<class Pixel>
template<class T>
void sge::gui::utility::channel_adder<Pixel>::operator()(T &t) const
{
	result[t] = p0[t]+p1[t];
}

#endif
