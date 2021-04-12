# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([scanpf], [0.0.1], [brian8181@gmail.com])
# Safety check - list a source file that wouldn't be in other directories:
AC_CONFIG_SRCDIR([src/scanpf.cpp])
# Put configuration results here, so we can easily #include them:
AC_CONFIG_HEADERS([config.h])
# Put autotools auxiliary files in a subdir, so they don't clutter top dir:
AC_CONFIG_AUX_DIR([build-aux])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Put autotools auxiliary files in a subdir, so they don't clutter top dir:
#AC_CONFIG_AUX_DIR([build-aux])

# ======================================
# Check for various headers and settings
# ======================================
#AC_CHECK_HEADERS([netinet/in.h])

#AC_CHECK_FUNCS([memset])
#AC_CHECK_HEADERS([netinet/in.h])
#AC_CHECK_HEADER_STDBOOL
#AC_PROG_INSTALL

# Checks for libraries.
# LT_INIT
# AC_ENABLE_SHARED
# AC_DISABLE_STATIC
# AC_PROG_LIBTOOL(libtool)

# Checks for typedefs, structures, and compiler characteristics.
# AC_HEADER_STDBOOL
# AC_C_INLINE
# AC_TYPE_SIZE_T

# Checks for typedefs, structures, and compiler characteristics.
# AC_HEADER_STDBOOL
# AC_C_INLINE
# AC_TYPE_SIZE_T

# Output Makefile files.
# AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile examples/Makefile man/Makefile scripts/Makefile])
# AC_OUTPUT

#AM_INIT_AUTOMAKE
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Output Makefile files.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile examples/Makefile man/Makefile scripts/Makefile])
# AC_OUTPUT
