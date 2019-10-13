#!/bin/bash
php -d extension=$PWD/helloworld2/modules/hello.so -r '{ echo hello_world() . "\n"; }'
