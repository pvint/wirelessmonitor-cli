AC_PREREQ([2.65])
AC_INIT([wirelessmonitor],
        [0.5],
        [http://vint.ca/wirelessmonitor])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_SRCDIR([wirelessmonitor.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_LANG([C])
AC_PROG_CXX
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG

# Checks for libraries.
#PKG_CHECK_MODULES([GTK2], [gtk+-2.0])
#AC_SUBST(GTK2_CFLAGS)
#AC_SUBST(GTK2_LIBS)

# Checks for header files.
AC_CHECK_HEADERS([stdio.h \
                  string.h \
		  unistd.h \
		  getopt.h ])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([daemon \
                system])

# Flags
AM_CFLAGS="-Wall"
AM_LDFLAGS="-Wl,--as-needed"
AC_SUBST(AM_CFLAGS)
AC_SUBST(AM_LDFLAGS)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
