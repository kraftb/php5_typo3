dnl $Id$
dnl config.m4 for extension icebear

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(icebear, for icebear support,
dnl Make sure that the comment is aligned:
dnl [  --with-icebear             Include icebear support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(icebear, whether to enable icebear support, [  --enable-icebear           Enable icebear support])

if test "$PHP_ICEBEAR" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-icebear -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/icebear.h"  # you most likely want to change this
  dnl if test -r $PHP_ICEBEAR/$SEARCH_FOR; then # path given as parameter
  dnl   ICEBEAR_DIR=$PHP_ICEBEAR
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for icebear files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ICEBEAR_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ICEBEAR_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the icebear distribution])
  dnl fi

  dnl # --with-icebear -> add include path
  dnl PHP_ADD_INCLUDE($ICEBEAR_DIR/include)

  dnl # --with-icebear -> check for lib and symbol presence
  dnl LIBNAME=icebear # you may want to change this
  dnl LIBSYMBOL=icebear # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ICEBEAR_DIR/lib, ICEBEAR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ICEBEARLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong icebear lib version or lib not found])
  dnl ],[
  dnl   -L$ICEBEAR_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ICEBEAR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(icebear, icebear.c, $ext_shared)
fi
