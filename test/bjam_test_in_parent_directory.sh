#!/bin/bash

# Run this from the root directory of the "meta" repository.

# This script will generate a directory ../meta-test and not remove it!
# So watch out where you run it.

# Run the tests by using this repository as submodule of the "meta-test"
# repository.

# This is necessary because this repository cannot be tested by itself.


# Travis CI looks for this line.
set -ev

set -o nounset
set -o errexit

(
    # Check out the "master" branch of "meta-test" from GitHub, in the parent
    # directory.

    cd ../
    git clone git://github.com/rogiervd/meta-test.git
    cd meta-test
    git checkout master
    git submodule init
    git submodule update
    # Then replace the "meta" submodule with the one in ../meta.
    (
        cd meta
        git pull ../../meta HEAD
    )
    
    # Test it
    bjam test "$@"

)
