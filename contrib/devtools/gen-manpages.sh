#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

MIRACLED=${MIRACLED:-$SRCDIR/miracled}
MIRACLECLI=${MIRACLECLI:-$SRCDIR/miracle-cli}
MIRACLETX=${MIRACLETX:-$SRCDIR/miracle-tx}
MIRACLEQT=${MIRACLEQT:-$SRCDIR/qt/miracle-qt}

[ ! -x $MIRACLED ] && echo "$MIRACLED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
MCAMVER=($($MIRACLECLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for miracled if --version-string is not set,
# but has different outcomes for miracle-qt and miracle-cli.
echo "[COPYRIGHT]" > footer.h2m
$MIRACLED --version | sed -n '1!p' >> footer.h2m

for cmd in $MIRACLED $MIRACLECLI $MIRACLETX $MIRACLEQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${MCAMVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${MCAMVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
