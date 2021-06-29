PHP_ARG_ENABLE(vartypes, Whether to enable the vartypes extension, [ --enable-vartypes Enable vartypes])

if test "$PHP_VARTYPES" != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(VARTYPES_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, VARTYPES_SHARED_LIBADD)
    PHP_ADD_INCLUDE(../../include)
    AC_DEFINE(HAVE_VARTYPES, 1, [Whether you have vartypes])
    PHP_NEW_EXTENSION(vartypes, vartypes.cpp, $ext_shared)
fi
