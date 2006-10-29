# Copyright 1999-2006 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit games

DESCRIPTION="A portable easy to use engine written in C++"
HOMEPAGE="http://spacegameengine.sourceforge.net/"
SRC_URI="http://spacegameengine.sourceforge.net/${P}.tar.bz2"

LICENSE="GPL"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE="opengl truetype devil xinput"

DEPEND="${RDEPEND}
        scons"
RDEPEND="!games-engines/spacegame
         dev-libs/boost
         x11-libs/libX11
		 virtual/libc
		 media-fonts/corefonts
		 opengl? (
		 	media-libs/glew
			x11-libs/libXxf86vm )
         devil? ( media-libs/devil )
		 truetype? ( media-libs/freetype )
		 xinput? ( x11-libs/libXxf86dga )"

pkg_setup() {
	if !(use opengl && use truetype && use devil && use xinput) ; then
		eerror "For now you have to enable all useflags to get a working engine!\nPlease do: \"games-engines/spacegameengine opengl truetype devil xinput\" > /etc/portage/package.use"
		die
	fi
}

src_compile() {
	scons ${MAKEOPTS} prefix=/usr workdir=${WORKDIR} libdir=$(get_libdir)
	flags=${CXXFLAGS} || die
}

src_install() {
	scons install prefix=/usr workdir=${WORKDIR} libdir=$(get_libdir) || die

	WU=${WORKDIR}/usr
	WI=${WU}/include/sge

	insinto /usr/include/sge
	doins ${WI}/*.hpp
	insinto /usr/include/sge/renderer
	doins ${WI}/renderer/*.hpp
	insinto /usr/include/sge/input
	doins ${WI}/input/*.hpp
	insinto /usr/include/sge/font
	doins ${WI}/font/*.hpp
	insinto /usr/include/sge/image
	doins ${WI}/image/*.hpp
	insinto /usr/include/sge/sprite
	doins ${WI}/sprite/*.hpp
	insinto /usr/include/sge/math
	doins ${WI}/math/*.hpp
	insinto /usr/include/sge/audio
	doins ${WI}/audio/*.hpp
	insinto /usr/include/sge/gui
	doins ${WI}/gui/*.hpp
	insinto /usr/include/sge/texture
	doins ${WI}/texture/*.hpp

	insinto /usr/share/games/sge/mainskin
	doins media/mainskin/*.png

	exeinto /usr/bin
	doexe sgetest

	insinto /usr/$(get_libdir)/sge/
	doins ${WU}/$(get_libdir)/sge/*.so

	insinto /usr/$(get_libdir)/
	doins ${WU}/$(get_libdir)/*.so
}
