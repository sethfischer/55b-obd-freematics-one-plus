#!/usr/bin/env bash

set -o errexit -o noclobber -o nounset
shopt -s globstar

directory="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

git ls-files -z -- "${directory}/**.yml" | xargs --no-run-if-empty --null yamllint
