NEW_VERSION=$1

REGISTRY="tkregistry"

if [ $NEW_VERSION ];then
  vpl publish --reg=${HOME}/.vpl/registries/${REGISTRY} --update-version=$NEW_VERSION
else
  vpl publish --reg=${HOME}/.vpl/registries/${REGISTRY} 
fi

NAME=`vpl scan name`
VERSION=`vpl scan version`

gh release create ${VERSION} ${NAME}-${VERSION}.zip -t "Release ${VERSION}" -n ${VERSION}
