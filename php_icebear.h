
#ifndef PHP_ICEBEAR_H
#define PHP_ICEBEAR_H

extern zend_module_entry icebear_module_entry;
#define phpext_icebear_ptr &icebear_module_entry

#ifdef PHP_WIN32
#	define PHP_ICEBEAR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_ICEBEAR_API __attribute__ ((visibility("default")))
#else
#	define PHP_ICEBEAR_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(icebear);
PHP_MSHUTDOWN_FUNCTION(icebear);
PHP_RINIT_FUNCTION(icebear);
PHP_RSHUTDOWN_FUNCTION(icebear);
PHP_MINFO_FUNCTION(icebear);

PHP_FUNCTION(confirm_icebear_compiled);	/* For testing, remove later. */
PHP_FUNCTION(trimExplode);	

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(icebear)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(icebear)
*/

/* In every utility function you add that needs to use variables 
   in php_icebear_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as ICEBEAR_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define ICEBEAR_G(v) TSRMG(icebear_globals_id, zend_icebear_globals *, v)
#else
#define ICEBEAR_G(v) (icebear_globals.v)
#endif

#endif	/* PHP_ICEBEAR_H */

