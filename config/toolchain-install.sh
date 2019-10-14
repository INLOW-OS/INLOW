#! /bin/sh

# 遇到错误即退出
set -e

if [ -z "${JOBS}" ];then
  JOBS=`grep -c ^processor /proc/cpuinfo 2>/dev/null`
  if [ -z "${JOBS}" ];then
    JOBS=1
  fi
fi

binutils_repo=https://gitee.com/qvjp/binutils-2.32.git
gcc_repo=https://gitee.com/qvjp/gcc-9.2.0.git
if [ "$CONTINUOUS_INTEGRATION" = true ]; then
    binutils_repo=https://github.com/INLOW-OS/binutils-2.32.git
    gcc_repo=https://github.com/INLOW-OS/gcc-9.2.0.git
fi

[ -z "${PREFIX+x}" ] && PREFIX="$HOME/inlow-toolchain"
[ -z "$SRCDIR" ] && SRCDIR="$HOME/src"
[ -z "$BUILDDIR" ] && BUILDDIR="$SRCDIR"
[ -z "$ARCH" ] && ARCH=i686
[ -z "$TARGET" ] && TARGET=$ARCH-elf


current_binutils=$(cat "$PREFIX/binutils-commit" || echo Not installed)
current_gcc=$(cat "$PREFIX/gcc-commit" || echo Not installed)
latest_binutils=$(git ls-remote $binutils_repo HEAD | cut -c 1-40)
latest_gcc=$(git ls-remote $gcc_repo HEAD | cut -c 1-40)

[ "$current_binutils" = "$latest_binutils" ] && \
        [ "$current_gcc" = "$latest_gcc" ] && \
        echo Cached Toolchain is already up to date. && \
        exit

rm -rf "$PREFIX"

export PATH="$PREFIX/bin:$PATH"

rm -rf "$SRCDIR/inlow-binutils" "$SRCDIR/inlow-gcc"
rm -rf "$BUILDDIR/build-binutils" "$BUILDDIR/build-gcc"

echo Downloading sources...
mkdir -p "$SRCDIR"
cd "$SRCDIR"
git clone $binutils_repo inlow-binutils
git clone $gcc_repo inlow-gcc

echo Building binutils...
mkdir -p "$BUILDDIR/build-binutils"
cd "$BUILDDIR/build-binutils"
"$SRCDIR/inlow-binutils/configure" --target=$TARGET --prefix="$PREFIX" \
    --with-sysroot --disable-nls --disable-werror
make -j"$JOBS"
make install

echo Building gcc...
mkdir -p "$BUILDDIR/build-gcc"
cd "$BUILDDIR/build-gcc"
"$SRCDIR/inlow-gcc/configure" --target=$TARGET --prefix="$PREFIX" \
    --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc all-target-libgcc -j"$JOBS"
make install-gcc install-target-libgcc

cd "$SRCDIR/inlow-binutils"
git rev-parse HEAD > "$PREFIX/binutils-commit"
cd "$SRCDIR/inlow-gcc"
git rev-parse HEAD > "$PREFIX/gcc-commit"

echo Install completed

