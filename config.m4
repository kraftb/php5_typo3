dnl

$

Id$


PHP_ARG_ENABLE(icebear, whether to enable icebear support,
[  --enable-icebear           Enable icebear support])

dnl *** Check if icebear is enabled
if test "$PHP_ICEBEAR" != "no"; then
	dnl *** Tell build system about this extension and configure it
  PHP_NEW_EXTENSION(icebear, icebear.c, $ext_shared)

	dnl *** Enable shared builds of icebear
  PHP_SUBST(ICEBEAR_SHARED_LIBADD)

fi

