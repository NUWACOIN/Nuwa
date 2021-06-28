
Debian
====================
This directory contains files used to package nuwacoind/nuwacoin-qt
for Debian-based Linux systems. If you compile nuwacoind/nuwacoin-qt yourself, there are some useful files here.

## nuwacoin: URI support ##


nuwacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install nuwacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your nuwacoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/nuwacoin128.png` to `/usr/share/pixmaps`

nuwacoin-qt.protocol (KDE)

