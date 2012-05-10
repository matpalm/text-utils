PROJECT(text_utils)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(CMAKE_VERBOSE_MAKEFILE ON)

ADD_DEFINITIONS(-Wall -O2 -DNDEBUG -march=native -mtune=native `getconf LFS_CFLAGS`)

ADD_EXECUTABLE(token_document_freq
               src/token_document_freq
               )
ADD_EXECUTABLE(collate
               src/collate
               )
ADD_EXECUTABLE(chop_most_least_freq
               src/chop_most_least_freq
               )
