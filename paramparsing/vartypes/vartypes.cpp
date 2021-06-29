// include the header of your extension
// the header includes php.h
#include "php_vartypes.h"
#include <iostream>
#include <sstream>
#include "pextcommon.h"

using namespace std;


// register our function to the PHP API 
// so that PHP knows, which functions are in this module
zend_function_entry vartypes_functions[] = {
    PHP_FE(vtsquare, NULL)
    PHP_FE(vtadd2square, NULL)
    PHP_FE(vtgetpid, NULL)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry vartypes_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_VARTYPES_EXTNAME,
    vartypes_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_VARTYPES_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(vartypes)

// Accept one integer and return the square
PHP_FUNCTION(vtsquare)
{
    long x;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(x)
    ZEND_PARSE_PARAMETERS_END();
    long y = x * x;
    RETURN_LONG( y );
}

// Accept two integers and and square
PHP_FUNCTION(vtadd2square)
{
    long x1, x2;
    ZEND_PARSE_PARAMETERS_START(2,2)
        Z_PARAM_LONG(x1);
        Z_PARAM_LONG(x2);
    ZEND_PARSE_PARAMETERS_END();
    long y = x1 * x2;
    long z = y * y;
    RETURN_LONG( z );
}

PHP_FUNCTION(vtgetpid)
{
    pid_t pid = getpid();
    RETURN_LONG( (long)pid);
}
