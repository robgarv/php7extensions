# php7extensions
A repo containing examples of PHP 7.x extensions in C and C++

This repo will contain small, sample projects to demonstrate how to implement features in PHP 7.x extensions.

Of course, I'm writing these things because a) I need to learn this stuff and b) there seems to be a shortage of clear and complete documentation on the web. I'm putting these up on github so I will always have a "cheat sheet" available. And who knows ... maybe the results of my fumbling efforts will help out some other developer some day. 

1. helloworld 

Contains some simple "helloworld" extensions. helloworld1 has been augmented
to illustrate the use of valgrind to explore memory leaks. 

2. paramparsing

Demonstrates parameter passing in both legacy and new PHP 7 styles

3. arrayhandling

Demonstrates basic array handling operations. 

4. memory

For exploring memory management issues

5. zvals

Examples demonstrating reading and writing zvals. 

Additionally, the following directories were added:

1. bin

Contains useful scripts like RunValgrind.sh

2. etc

Contains a php.ini file and a valgrind suppression file. 

