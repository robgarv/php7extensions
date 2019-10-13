// include the header of your extension
// the header includes php.h
#include "php_dumpstring.h"
#include <iostream>
#include <sstream>

using namespace std;

#define GDB_BLOCK \
{ \
  std::ostringstream _ssfilename; \
  _ssfilename << getenv( "HOME" ) << "/tmp/gdb.block"; \
  struct stat _gdbstat; \
  while ( stat( _ssfilename.str().c_str(), &_gdbstat ) == 0 ) \
  { \
    sleep( 1 ); \
  } \
}



// register our function to the PHP API 
// so that PHP knows, which functions are in this module
zend_function_entry dumpstring_functions[] = {
    PHP_FE(dumpstring, NULL)
    PHP_FE(dumpinput, NULL)
    PHP_FE(dumparrayval, NULL)
    PHP_FE(findhashtest, NULL)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry dumpstring_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_DUMPSTRING_EXTNAME,
    dumpstring_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_DUMPSTRING_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(dumpstring)

// Finally, we implement our "Hello World" function
// this function will be made available to PHP
// and prints to PHP stdout using printf
PHP_FUNCTION(dumpstring)
{
    // php_printf("Hello World! (from our dumpstring extension)\n");
    RETURN_STRING( "Dumpstring test" );
}

// Dump the input string using the "old API"
PHP_FUNCTION(dumpinput)
{
    // touch $HOME/tmp/gdb.block to cause execution to loop
    // rm $HOME/tmp/gdb.block to cause execution to break out of loop
    // Gives opportunity to attach debugger
    GDB_BLOCK;
    char* input;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &input, &len) == FAILURE)
    {
        std::cout << "dumpinput: Error parsing input params" << std::endl;
        RETURN_NULL();
    }
    std::cout << "dumpinput received: " << input << std::endl;
    RETURN_STRING(input);
}

// Give a key and an array (hash), return the value
PHP_FUNCTION(dumparrayval)
{
    // touch $HOME/tmp/gdb.block to cause execution to loop
    // rm $HOME/gdb.block to cause execution to break out of loop
    // Gives opportunity to attach debugger
    GDB_BLOCK;
    char* szKey;
    zend_string *zKey;
    zval *zArray;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Sa", &zKey, &zArray) == FAILURE)
    {
        std::cout << "dumparrayval: Error parsing input params" << std::endl;
    }

    szKey = ZSTR_VAL(zKey);
    std::cout << "dumparrayval fetching key: " << szKey << std::endl;

    zval *Val = zend_hash_find(Z_ARRVAL_P(zArray), zKey);
    if ( Val == NULL )
    {
        std::cout << "dumparrayval could not find key " << szKey << std::endl;
        RETURN_NULL();
    }
    char* szVal = Z_STRVAL_P(Val);
    RETURN_STRING(szVal);
}

#define _USE_STDOUT
#ifdef _USE_STDOUT
    #define _PRINTIT( __label, _x_msg_stream ) \
    do { \
        std::cout << __label << "(S): " << _x_msg_stream.str() << std::endl; \
    } while( 0 )
#else
    #define _PRINTIT( __label, _x_msg_stream ) \
    do { \
        php_printf( __label << "(P): %s", _x_msg_stream.str().c_str()); \
    } while( 0 )
#endif

#define WARNS( _Expression ) \
do { \
  std::ostringstream __x_Msg; \
  __x_Msg << _Expression; \
  _PRINTIT( "WARNING", __x_Msg ); \
} while( 0 )


#define STATUS( _Expression ) \
do { \
  std::ostringstream __x_Msg; \
  __x_Msg << _Expression; \
  _PRINTIT( "WARNING", __x_Msg ); \
} while( 0 )

int ZendHashFindImpl( const HashTable *ht,
                        const char *arKey,
                        uint nKeyLength,
                        void **pData)
{
    zend_string *zKey = zend_string_init( arKey, nKeyLength - 1, 0 );
    char* szKey = ZSTR_VAL(zKey);
    STATUS("ZendHashFindImpl: key conversion to zend_string check: " << szKey);
    *pData = (void*)zend_hash_find( ht, zKey );
    if ( *pData == NULL )
    {
      WARNS( "RCGDEBUG: ZendHashFindImpl: Failed to find key " << arKey );
      return FAILURE;
    }
    else
    {
      STATUS( "RCGDEBUG: ZendHashFindImpl: Value type is: " << (long)Z_TYPE_P( (zval *)(*pData )) );
      return SUCCESS;
    }
}


string GetStringParamByName( zval **Params, const std::string &Name,
               int &ParseResult )
{
    zval *Value = NULL;
    string StringValue;
    WARNS( "RCGDEBUG Backend: Enter GetStringParamByName");
    if( Params != NULL )
    {
      const char *NameCStr = Name.c_str();
      const size_t NameCStrSize = Name.length() + 1; // +1 for '\0';

      // TODO: verify that (char *) is safe
      if( ZendHashFindImpl
      ( Z_ARRVAL_P( *Params ), (char *)NameCStr, (uint)NameCStrSize, (void **)&Value ) == SUCCESS )
      {
        switch( Z_TYPE_P( Value ) )
        {
        case IS_LONG:
        case IS_DOUBLE:
        case _IS_BOOL:
            // PhpStubs::mConvertToStringEx( Value );
            STATUS("GetStringParamByName: Converting Value to string");
            convert_to_string_ex( Value );

            // fall-through.

        case IS_STRING:
            StringValue = Z_STRVAL_P( Value );
            WARNS( "RCGDEBUG Backend: GetStringParamByName: StringValue = " << StringValue );
            break;

        case IS_NULL:
          StringValue.clear();
          WARNS("GetStringParamByNBame: NULL detected");
          break;

        default:
          php_printf( "Non-string type(%d), Name(%s)", Z_TYPE_P( Value ), NameCStr );
          ParseResult = FAILURE;
        }
      }
      else
      {
        WARNS( "RCGDEBUG: Param(" << Name << ") not found" );
        ParseResult = FAILURE;
      }
    }

    return StringValue;
}

PHP_FUNCTION(findhashtest)
{
    // touch $HOME/tmp/gdb.block to cause execution to loop
    // rm $HOME/tmp/db.block to cause execution to break out of loop
    // Gives opportunity to attach debugger
    GDB_BLOCK;
    char* szKey;
    zend_string *zKey;
    zval *zArray;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Sa", &zKey, &zArray) == FAILURE)
    {
        WARNS("findhashtest: Error parsing input params");
        RETURN_NULL();
    }

    szKey = ZSTR_VAL(zKey);
    std::string strKey = szKey;
    int ParseResult = SUCCESS;
    STATUS("findhashtest: Calling GetStringParamByName( zArray, " << strKey << ", SUCCESS)" );
    std::string strVal = GetStringParamByName( &zArray, strKey, ParseResult );
    if (ParseResult != SUCCESS)
    {
        WARNS("findhashtest: Failed to get key: " << strVal);
        RETURN_NULL();
    }
    else
    {
        STATUS("findhashtest: Retrieved " << strKey << " => " << strVal );
    }
    RETURN_STRING( strVal.c_str());
}

