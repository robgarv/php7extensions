#ifndef _PHP_VARTYPES_H
#define _PHP_VARTYPES_H

#ifdef __cplusplus
extern "C" {
#endif
  #include "php.h"
#ifdef __cplusplus
}
#endif

// we define Module constants
#define PHP_VARTYPES_EXTNAME "vartypes"
#define PHP_VARTYPES_VERSION "0.0.1"

// then we declare the function to be exported
PHP_FUNCTION(vtsquare);
PHP_FUNCTION(vtadd2square);
PHP_FUNCTION(vtgetpid);

ZEND_BEGIN_ARG_INFO_EX(arginfo_vtsquare, 0, 0, 1)
  ZEND_ARG_INFO(0, x) /* ARRAY_INFO(1, stack, 0) */
ZEND_END_ARG_INFO()


extern zend_module_entry vartypes_module_entry;
#define phpext_vartypes_ptr &vartypes_module_entry

#endif
