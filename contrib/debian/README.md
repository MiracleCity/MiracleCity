
Debian
====================
This directory contains files used to package miracled/miracle-qt
for Debian-based Linux systems. If you compile miracled/miracle-qt yourself, there are some useful files here.

## miracle: URI support ##


miracle-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install miracle-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your miracle-qt binary to `/usr/bin`
and the `../../share/pixmaps/miracle128.png` to `/usr/share/pixmaps`

miracle-qt.protocol (KDE)

