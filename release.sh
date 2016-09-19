#!/bin/bash
set -e

if [ $# -eq 0 ]
  then
    echo "No version number supplied"
    exit 1
fi

VERSION=$1
SVN="http://svn.km3net.de/dataformats/jppy"

git checkout develop
git pull

git flow release start "${VERSION}"

vim jppy/setup.py
git add jppy/setup.py
git commit -m "Bumps version number"

git flow release finish "${VERSION}"

python setup.py sdist register upload

git checkout master
git push
git checkout develop
git push
git push --tags

git checkout svn
git merge master
git svn dcommit
git checkout develop

svn copy "${SVN}/git" "${SVN}/tag/v${VERSION}" -m "Release ${VERSION}"
