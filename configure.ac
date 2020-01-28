AC_PREREQ([2.69])
AC_INIT

m4_ifndef([AC_PROG_AR],[dnl
AN_MAKEVAR([AR], [AC_PROG_AR])
AN_PROGRAM([ar], [AC_PROG_AR])
AC_DEFUN([AC_PROG_AR],
[AC_CHECK_TOOL(AR, ar, :)])
])

AC_PREFIX_DEFAULT([/opt/n64/mips64/n64-sysroot/usr])

AC_SUBST([CFLAGS])
AC_SUBST([CXXFLAGS])
CFLAGS="-g -ffunction-sections -fdata-sections $CFLAGS"
CXXFLAGS="-g -ffunction-sections -fdata-sections $CFLAGS"

AC_ARG_ENABLE([lto],
    [AS_HELP_STRING]([--enable-lto],
        [compile library with lto support])],
    [
        CFLAGS="-O3 -flto -ffat-lto-objects $CFLAGS"
        CXXFLAGS="-O3 -flto -ffat-lto-objects $CXXFLAGS"
    ],
    [
        CFLAGS="-Os $CFLAGS"
        CXXFLAGS="-Os $CXXFLAGS"
    ])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_AR
AC_PROG_INSTALL
AC_PROG_MKDIR_P

AC_CHECK_HEADERS([list/list.h])
AC_CHECK_HEADERS([vector/vector.c])
AC_CHECK_HEADERS([n64/gbi.h])
AC_CHECK_HEADERS([grc.h])

AC_CONFIG_FILES([makefile])
AC_OUTPUT