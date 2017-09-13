#!/usr/bin/env zsh
set -e

if [ $# -eq 0 ]
  then
    echo "No version number supplied"
    exit 1
fi

VERSION=$1
SVN="http://svn.km3net.de/dataformats/jppy"
#export JPP_DIR=dummy
#export JPP_LIB=dummy

git co master 
git pull

git checkout develop
git pull

git flow release start "${VERSION}"

vim setup.py
git add setup.py
git commit -m "Bumps version number"

git flow release finish "${VERSION}"

#python setup.py sdist register upload
rm -rf dist/*
python setup.py sdist
twine uploadt dist/*

git checkout master
git push
git checkout develop
git push
git push --tags

set +e

git checkout svn
git merge master
git svn dcommit

svn copy "${SVN}/git" "${SVN}/tag/v${VERSION}" -m "Release ${VERSION}"
git checkout develop
