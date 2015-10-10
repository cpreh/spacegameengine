/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_IMAGE_COLOR_PREDEF_HPP_INCLUDED
#define SGE_IMAGE_COLOR_PREDEF_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/image/color/detail/symbol.hpp>


namespace sge
{
namespace image
{
namespace color
{

#define SGE_IMAGE_COLOR_DECLARE_PREDEF(\
	name\
)\
SGE_IMAGE_COLOR_DETAIL_SYMBOL \
sge::image::color::any::object \
name();

namespace predef
{
	SGE_IMAGE_COLOR_DECLARE_PREDEF(aliceblue            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(antiquewhite         )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(aqua                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(aquamarine           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(azure                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(beige                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(bisque               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(black                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(blanchedalmond       )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(blue                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(blueviolet           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(brown                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(burlywood            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(cadetblue            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(chartreuse           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(chocolate            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(coral                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(cornflowerblue       )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(cornsilk             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(crimson              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(cyan                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkblue             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkcyan             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkgoldenrod        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkgray             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkgreen            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkgrey             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkkhaki            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkmagenta          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkolivegreen       )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkorange           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkorchid           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkred              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darksalmon           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkseagreen         )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkslateblue        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkslategray        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkslategrey        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkturquoise        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(darkviolet           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(deeppink             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(deepskyblue          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(dimgray              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(dimgrey              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(dodgerblue           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(firebrick            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(floralwhite          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(forestgreen          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(fuchsia              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(gainsboro            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(ghostwhite           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(gold                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(goldenrod            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(gray                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(green                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(greenyellow          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(grey                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(honeydew             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(hotpink              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(indianred            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(indigo               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(ivory                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(khaki                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lavender             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lavenderblush        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lawngreen            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lemonchiffon         )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightblue            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightcoral           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightcyan            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightgoldenrodyellow )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightgray            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightgreen           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightgrey            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightpink            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightsalmon          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightseagreen        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightskyblue         )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightslategray       )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightslategrey       )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightsteelblue       )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lightyellow          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(lime                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(limegreen            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(linen                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(magenta              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(maroon               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumaquamarine     )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumblue           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumorchid         )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumpurple         )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumseagreen       )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumslateblue      )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumspringgreen    )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumturquoise      )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mediumvioletred      )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(midnightblue         )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mintcream            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(mistyrose            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(moccasin             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(navajowhite          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(navy                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(oldlace              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(olive                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(olivedrab            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(orange               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(orangered            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(orchid               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(palegoldenrod        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(palegreen            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(paleturquoise        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(palevioletred        )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(papayawhip           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(peachpuff            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(peru                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(pink                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(plum                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(powderblue           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(purple               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(red                  )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(rosybrown            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(royalblue            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(saplebrown           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(salmon               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(sandybrown           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(seagreen             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(seashell             )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(sienna               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(silver               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(skyblue              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(slateblue            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(slategray            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(slategrey            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(snow                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(springgreen          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(steelblue            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(tan                  )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(teal                 )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(thistle              )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(tomato               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(turquoise            )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(violet               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(wheat                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(white                )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(whitesmoke           )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(yellow               )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(yellowgreen          )
	SGE_IMAGE_COLOR_DECLARE_PREDEF(transparent          )
}

}
}
}

#undef SGE_IMAGE_COLOR_DECLARE_PREDEF

#endif
