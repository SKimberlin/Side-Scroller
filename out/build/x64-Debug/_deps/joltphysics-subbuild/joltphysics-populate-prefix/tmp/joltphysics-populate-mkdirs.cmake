# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-src"
  "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-build"
  "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-subbuild/joltphysics-populate-prefix"
  "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-subbuild/joltphysics-populate-prefix/tmp"
  "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp"
  "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src"
  "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Seth/Desktop/Github/Side-Scroller/out/build/x64-Debug/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
