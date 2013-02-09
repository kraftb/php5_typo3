
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_icebear.h"

/* If you declare any globals in php_icebear.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(icebear)
*/

/* True global resources - no need for thread safety here */
static int le_icebear;

/* {{{ icebear_functions[]
 *
 * Every user visible function must have an entry in icebear_functions[].
 */
const zend_function_entry icebear_functions[] = {
	PHP_FE(confirm_icebear_compiled,	NULL)		/* For testing, remove later. */
	{NULL, NULL, NULL}	/* Must be the last line in icebear_functions[] */
};
/* }}} */

/* {{{ icebear_module_entry
 */
zend_module_entry icebear_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"icebear",
	icebear_functions,
	PHP_MINIT(icebear),
	PHP_MSHUTDOWN(icebear),
	PHP_RINIT(icebear),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(icebear),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(icebear),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ICEBEAR
ZEND_GET_MODULE(icebear)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("icebear.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_icebear_globals, icebear_globals)
    STD_PHP_INI_ENTRY("icebear.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_icebear_globals, icebear_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_icebear_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_icebear_init_globals(zend_icebear_globals *icebear_globals)
{
	icebear_globals->global_value = 0;
	icebear_globals->global_string = NULL;
}
*/
/* }}} */


// A "zend_class_entry" has to be made for every class which should be available in script-space
static zend_class_entry *t3lib_div_class_entry;


/*
 * Parameters required for t3lib_div::trimExplode
 *
 * t3lib_div::trimExplode($delim, $string, $removeEmptyValues = false, $limit = 0);
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo__t3lib_div__trimExplode, 0, 0, 2)
	ZEND_ARG_INFO(0, delim)
	ZEND_ARG_INFO(0, string)
	ZEND_ARG_INFO(0, removeEmptyValues)
	ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()


/* {{{ t3lib_div_methods[]
 *
 * "t3lib_div" methods visible to PHP scripts must be registered in "t3lib_div_methods[]"
 */
const zend_function_entry t3lib_div_methods[] = {
	PHP_FE(trimExplode, arginfo__t3lib_div__trimExplode)
//	PHP_FE(intExplode, arginfo__t3lib_div__trimExplode)
	{NULL, NULL, NULL}
};
/* }}} */




/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(icebear)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/

		// Initialize "t3lib_div" class for usage by PHP scripts
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "t3lib_div", t3lib_div_methods);
//	ce.create_object = mysqli_objects_new;
	ce.create_object = NULL;
	t3lib_div_class_entry = zend_register_internal_class(&ce TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(icebear)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(icebear)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(icebear)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(icebear)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "icebear support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */

/* {{{ proto string confirm_icebear_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_icebear_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "icebear", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */


/* {{{ php_explode
 */
PHPAPI void t3lib_div__trimExplode__explode(zval *delim, zval *str, zval *return_value, long limit, zend_bool keepEmpty TSRMLS_DC)
{
	zval tmp;
	char *p1, *p2, *endp;

	endp = Z_STRVAL_P(str) + Z_STRLEN_P(str);

	p1 = Z_STRVAL_P(str);
	p2 = php_memnstr(Z_STRVAL_P(str), Z_STRVAL_P(delim), Z_STRLEN_P(delim), endp);

	if (p2 == NULL) {
		php_trim(p1, Z_STRLEN_P(str), NULL, 0, &tmp, 3 TSRMLS_CC);
		if (Z_STRLEN_P(&tmp) || keepEmpty) {
			add_next_index_stringl(return_value, Z_STRVAL_P(&tmp), Z_STRLEN_P(&tmp), 0);
		}
	} else {
		do {
			php_trim(p1, p2 - p1, NULL, 0, &tmp, 3 TSRMLS_CC);
			if (Z_STRLEN_P(&tmp) || keepEmpty) {
				add_next_index_stringl(return_value, Z_STRVAL_P(&tmp), Z_STRLEN_P(&tmp), 0);
				--limit;
			}
			p1 = p2 + Z_STRLEN_P(delim);
		} while ((p2 = php_memnstr(p1, Z_STRVAL_P(delim), Z_STRLEN_P(delim), endp)) != NULL && limit > 1);
		if (p1 <= endp) {
			php_trim(p1, endp - p1, NULL, 0, &tmp, 3 TSRMLS_CC);
			if (Z_STRLEN_P(&tmp) || keepEmpty) {
				add_next_index_stringl(return_value, Z_STRVAL_P(&tmp), Z_STRLEN_P(&tmp), 0);
			}
		}
	}
}
/* }}} */

/* {{{ t3lib_div__whitespace_charmask
 * Fills a 256-byte bytemask character mapping with whitespace characters
 */
static inline int t3lib_div__whitespace_charmask(unsigned char mask[])
{
	mask[' '] = 1;
	mask['\n'] = 1;
	mask['\r'] = 1;
	mask['\t'] = 1;
	mask['\v'] = 1;
	mask['\0'] = 1;
}
/* }}} */


/* {{{ php_explode_negative_limit
 */
PHPAPI void t3lib_div__trimExplode__explode_negative_limit(zval *delim, zval *str, zval *return_value, long limit, zend_bool keepEmpty TSRMLS_DC)
{
#define EXPLODE_ALLOC_STEP 64
	char *p1;
	char *p2, *p3, *endp;

	endp = Z_STRVAL_P(str) + Z_STRLEN_P(str);

	p1 = Z_STRVAL_P(str);
	p2 = php_memnstr(Z_STRVAL_P(str), Z_STRVAL_P(delim), Z_STRLEN_P(delim), endp);

	if (p2 == NULL) {
		/*
		do nothing since limit <= -1, thus if only one chunk - 1 + (limit) <= 0
		by doing nothing we return empty array
		*/
	} else {
		int allocated = EXPLODE_ALLOC_STEP, found = 0;
		long i, to_return;
		char **positions = emalloc(allocated * sizeof(char *));
		long *lengths = emalloc(allocated * sizeof(long));
		char mask[256];
		t3lib_div__whitespace_charmask(mask);

		do {
			p3 = p2;
			if (p1 == p2) {
					// This element is empty
				if (keepEmpty) {
					lengths[found] = 0;
					positions[found++] = p1;
				}
			} else {
					// Advance "p1" as long as the character it currently points to is a trim-whitespace character
				do {
					if (mask[(unsigned char)*p1]) {
						p1++;
					} else {
						break;
					}
				} while (p1 < p2);
			
				if (p1 < (p2 - 1)) {
						// If there is more than one character left recede "p2" as long as it points to a trim-whitespace character
					do {
						if (mask[(unsigned char)*p2]) {
							p2--;
						} else {
							break;
						}
					} while (p1 < p2 - 1);
					
					lengths[found] = p2 - p1;
					positions[found++] = p1;
				} else if (p1 == (p2 - 1)) {
						// If there is only one character left it must be a non-trim-whitespace character as else the above "Advance p1" loop would have looped over it.
					lengths[found] = 1;
					positions[found++] = p1;
				} else {
						// p1 > (p2 -1) means: p1 == p2
						// In this case this is an all trim-whitespace element. Act depending on "keepEmpty" flag
					if (keepEmpty) {
						lengths[found] = 0;
						positions[found++] = p1;
					}
				}
			}
			if (found >= allocated) {
				allocated = found + EXPLODE_ALLOC_STEP;/* make sure we have enough memory */
				positions = erealloc(positions, allocated*sizeof(char *));
				lengths = erealloc(lengths , allocated*sizeof(long));
			}
			p1 = p3 + Z_STRLEN_P(delim);
		} while ((p2 = php_memnstr(p1, Z_STRVAL_P(delim), Z_STRLEN_P(delim), endp)) != NULL);

		to_return = limit + found;
		/* limit is at least -1 therefore no need of bounds checking : i will be always less than found */
		for (i = 0;i < to_return;i++) { /* this checks also for to_return > 0 */
			add_next_index_stringl(return_value, positions[i], lengths[i], 1);
		}
		efree(positions);
		efree(lengths);
	}
#undef EXPLODE_ALLOC_STEP
}
/* }}} */




/* {{{ proto array trimExplode(string delim, string string, boolean removeEmptyValues, integeger limit)
   Explodes a string and trims all values for whitespace in the ends. If $onlyNonEmptyValues is set, then all blank ('') values are removed. */
PHP_FUNCTION(trimExplode)
{
	zval *tmp = NULL;
	zval zdelim, zstr;

	char *delim = NULL; int delim_len = 0;		// @param string $delim: Delimiter string to explode with
	char *str = NULL; int str_len = 0;		// @param string $string: The string to explode
	zend_bool removeEmptyValues = 0;		// @param boolean $removeEmptyValues: If set, all empty values will be removed in output
	long limit = 0;					// @param integer $limit: If positive, the result will contain a maximum of $limit elements, if negative, the first abs($limit) elements are returned.

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|bl", &delim, &delim_len, &str, &str_len, &removeEmptyValues, &limit) == FAILURE) {
		return;
	}

	if (delim_len == 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Empty delimiter");
		RETURN_FALSE;
	}

	array_init(return_value);			// @return array Exploded values

	if (str_len == 0) {
	  	if ((limit >= 0) && !removeEmptyValues) {
			add_next_index_stringl(return_value, "", sizeof("") - 1, 1);
		}
		return;
	}

	if (limit == 1) {
		php_trim(str, str_len, NULL, 0, tmp, 3 TSRMLS_CC);
		if (Z_STRLEN_P(tmp) || !removeEmptyValues) {
			add_index_stringl(return_value, 0, Z_STRVAL_P(tmp), Z_STRLEN_P(tmp), 0);
		}
	} else {
		ZVAL_STRINGL(&zstr, str, str_len, 0);
		ZVAL_STRINGL(&zdelim, delim, delim_len, 0);
		if (limit < 0) {
//			php_explode_negative_limit(&zdelim, &zstr, return_value, limit == 0 ? LONG_MAX : limit);
			t3lib_div__trimExplode__explode_negative_limit(&zdelim, &zstr, return_value, limit == 0 ? LONG_MAX : limit, !removeEmptyValues);
		} else {
			t3lib_div__trimExplode__explode(&zdelim, &zstr, return_value, limit == 0 ? LONG_MAX : limit, !removeEmptyValues);
		}
	}
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
