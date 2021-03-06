# tdwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c tdwm.c util.c
OBJ = ${SRC:.c=.o}

all: options tdwm tdwmbatt tdwmtemp

options:
	@echo tdwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk tdwm.h

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

tdwm: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f tdwm tdwmbatt tdwmtemp ${OBJ} tdwm-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p tdwm-${VERSION}
	@cp -R LICENSE TODO BUGS Makefile README config.def.h config.mk \
		tdwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	@tar -cf tdwm-${VERSION}.tar dwm-${VERSION}
	@gzip tdwm-${VERSION}.tar
	@rm -rf tdwm-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f tdwm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/tdwm
	@cp -f tdwmclock.sh ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/tdwmclock.sh
	@cp -f tdwmvol.sh ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/tdwmvol.sh
	@cp -f tdwmbatt ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/tdwmbatt
	@cp -f tdwmtemp ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/tdwmtemp
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < tdwm.1 > ${DESTDIR}${MANPREFIX}/man1/tdwm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/tdwm.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/tdwm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/tdwm.1

.PHONY: all options clean dist install uninstall
