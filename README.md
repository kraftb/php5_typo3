php5_typo3
==========

PHP5 module which makes the TYPO3 API native PHP calls

The aim of this project is something which I already started again and again: To make a PHP module which allows
to have the TYPO3 API availabe in PHP as native calls. So instead of implementing every function in PHP the
various methods of the TYPO3 API are implemented in C/C++.

Of course this is an enormous effort and I never even achieved to have even a single TYPO3 core class completly
implemented as PHP module. But maybe with the help of github this could change if other people join this effor.

What are the advantages?
 * Call to PHP native classes/methods are much faster than code implemented in PHP itself.
 * Maybe one time it is possible to overcome the "Call a view" concept of PHP by directly starting a TYPO3 controller class/method
 * Less prone to bugs introduced by "admins" editing TYPO3 (module) source code

And what would be disadvantages?
 * Harder to debug
 * A lot of maybe senseless effort
 * Changes must be compiled and apache restarted
 * Handling of different TYPO3 Core/API versions
