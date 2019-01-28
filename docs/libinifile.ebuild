inherit eutils libtool

DESCRIPTION="C/C++ library with syntax validator for parsing ini-files"
HOMEPAGE="https://nowise.se/oss/libinifile/"
SRC_URI="https://github.com/nowisesys/libinifile/archive/release-${P}.tar.gz"

LICENSE="GPL"
KEYWORDS="~amd64 ~x86"
SLOT="0"
IUSE="cxx"

src_compile() {
        econf $(use_enable cxx) || die "configure failed"
        emake || die "make failed"
}
	
src_install () {
        make DESTDIR="${D}" install || die "install failed"
	dodoc AUTHORS COPYING README
}
