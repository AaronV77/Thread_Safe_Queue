[![Build Status](https://travis-ci.com/AaronV77/Thread_Safe_Queue.svg?branch=master)](https://travis-ci.com/AaronV77/Thread_Safe_Queue)

# Thread Safe Queue

This repository is an example of a thread safe queue data structure, and that has perfect memory cleanup via Valgrind. I'm  not
entirely great at threads and needed some practice, and this is the ending result.

## Warnings

Again I'm a novice thread programmer and when I mean thread safe, I mean it worked on my machine and I didn't thourghly test 
this on all different architectures to make sure that it worked.

## Prerequisites

Need to be able to have the pthreads library available on your system.

## Testing

I have included two code mains that tell you how to run them and test using threads and not using threads. Also there is a make file to make your life easier, your welcome.

I have included two mains in this repository. One for using threads and not using threads, these are just examples. I have learned the unit test suit of libcheck to be able to test C code, on Travis Ci. Lastly, I have included make files to make youir life easier, your welcome.

## Help / Contributing
If you see anything that I could have done different or that I am missing, then by all means please submit a pull request.

# Author: Aaron A. Valoroso


## Inspiring Quotes

Programs must be written for people to read, and only incidentally for machines to execute.
 
 - Harold Abelson
