##
# Make documentation: http://www.gnu.org/software/make/manual/
#



##
# Global variables section.
#
BUG_ADDRESS = kurijlj@gmail.com
TARGETS = argpfrmwrk getoptfrmwrk glibfrmwrk glibprocesstream



##
# Define global flags here.
#
STD_FLAGS = -O0 -Wall -std=gnu99
STD_DBG_FLAGS = -g -O0 -Wall -std=gnu99
GLIB2CFLAGS = $(shell pkg-config --cflags glib-2.0)



##
# Define global libraries here.
#
LIBGLIB2 = $(shell pkg-config --libs glib-2.0)



##
# Print some help information.
#
.ONESHELL:
help:
	@echo -e "Usage: LANG=<LANGUAGE> RELEASE=<true> make [option]\n"
	@echo -e "Supported options:"
	@echo -e "\thelp\t\t\t\tPrint this help list"
	@echo -e "\tall\t\t\t\tMake all executables"
	@echo -e "\tprepmsgs\t\t\tPrepare .po files for translation"
	@echo -e "\ttranslations\t\t\tMake .mo translations"
	@echo -e "\tclean\t\t\t\tRemove .o and *~ files"
	@echo -e "\tcleanall\t\t\tRemove all executables, .o, *~, .ppc"
	@echo -e "\t\t\t\t\tand .pot files"
	@echo -e "\targpfrmwrk\t\t\tMake argpfrmwrk executable"
	@echo -e "\targpfrmwrk.po\t\t\tPrepare argpfrmwrk.po file"
	@echo -e "\t\t\t\t\tfor translation"
	@echo -e "\targpfrmwrk.mo\t\t\tMake argpfrmwrk.mo translation"
	@echo -e "\tgetoptfrmwrk\t\t\tMake getoptfrmwrk executable"
	@echo -e "\tgetoptfrmwrk.po\t\t\tPrepare getoptfrmwrk.po file"
	@echo -e "\t\t\t\t\tfor translation"
	@echo -e "\tgetoptfrmwrk.mo\t\t\tMake getoptfrmwrk.mo translation"
	@echo -e "\tglibfrmwrk\t\t\tMake glibfrmwrk executable"
	@echo -e "\tglibfrmwrk.po\t\t\tPrepare glibfrmwrk.po file"
	@echo -e "\t\t\t\t\tfor translation"
	@echo -e "\tglibfrmwrk.mo\t\t\tMake glibfrmwrk.mo translation"
	@echo -e "\tglibprocesstream\t\tMake glibprocesstream executable"
	@echo -e "\tglibprocesstream.po\t\tPrepare glibprocesstream.po file"
	@echo -e "\t\t\t\t\tfor translation"
	@echo -e "\tglibprocesstream.mo\t\tMake glibprocesstream.mo translation\n"
	@echo -e "Report bugs and suggestions to <$(BUG_ADDRESS)>\n"



##
# Make all executables.
#
all: $(TARGETS)



##
# Prepare all messages for translation.
#
prepmsgs: $(foreach TARGET,$(TARGETS),$(TARGET).po)



##
# Prepare all messages for translation.
#
translations: $(foreach TARGET,$(TARGETS),$(TARGET).mo)



##
# argpfrmwrk section.
#
argpfrmwrk : SOURCES = argpfrmwrk.c
argpfrmwrk : TARGET = $(SOURCES:%.c=%)
argpfrmwrk : OBJS = $(TARGET).o
argpfrmwrk : LIBS =
argpfrmwrk : EXTRA_FLAGS =
argpfrmwrk : argpfrmwrk.o
	gcc -o $(TARGET) $(OBJS) $(LIBS)

argpfrmwrk.o : argpfrmwrk.c
ifeq ($(RELEASE), true)
	gcc $(STD_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
else
	gcc $(STD_DBG_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
endif

# argpfrmwrk localisation section.
argpfrmwrk.mo : SOURCE = argpfrmwrk.po
argpfrmwrk.mo : TARGET = $(SOURCE:%.po=%).mo
.ONESHELL:
argpfrmwrk.mo : argpfrmwrk.po
ifeq ($(strip $(LANG)),)
	mkdir -p ./$(LANG)/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	shell mv -v ./$(TARGET) ./$(LANG)/LC_MESSAGES/
else
	mkdir -p ./sr_RS@latin/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	mv -v ./$(TARGET) ./sr_RS@latin/LC_MESSAGES/
endif

argpfrmwrk.po : SOURCE = argpfrmwrk.pot
argpfrmwrk.po : TARGET = $(SOURCE:%.pot=%).po
argpfrmwrk.po : argpfrmwrk.pot
ifeq ($(strip $(LANG)),)
	msginit -l $(LANG) -o $(TARGET) -i $(SOURCE)
else
	msginit -l sr_RS@latin -o $(TARGET) -i $(SOURCE)
endif

argpfrmwrk.pot : SOURCE = argpfrmwrk.ppc
argpfrmwrk.pot : DOMAIN = $(SOURCE:%.ppc=%)
argpfrmwrk.pot : VERSION = 1.0
argpfrmwrk.pot : TARGET = $(DOMAIN).pot
argpfrmwrk.pot : argpfrmwrk.ppc
	xgettext -o $(TARGET) --package-name="$(DOMAIN)" \
		--package-version="$(VERSION)" \
		--msgid-bugs-address="$(BUG_ADDRESS)" $(SOURCE)

argpfrmwrk.ppc : SOURCE = argpfrmwrk.c
argpfrmwrk.ppc : TARGET = $(SOURCE:%.c=%).ppc
argpfrmwrk.ppc : EXTRA_FLAGS =
argpfrmwrk.ppc : argpfrmwrk.c
	cpp $(EXTRA_FLAGS) $(SOURCE) $(TARGET)



##
# getoptfrmwrk section.
#
getoptfrmwrk : SOURCES = getoptfrmwrk.c
getoptfrmwrk : TARGET = $(SOURCES:%.c=%)
getoptfrmwrk : OBJS = $(TARGET).o
getoptfrmwrk : LIBS =
getoptfrmwrk : EXTRA_FLAGS =
getoptfrmwrk : getoptfrmwrk.o
	gcc -o $(TARGET) $(OBJS) $(LIBS)

getoptfrmwrk.o : getoptfrmwrk.c
ifeq ($(RELEASE), true)
	gcc $(STD_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
else
	gcc $(STD_DBG_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
endif

# getoptfrmwrk localisation section.
getoptfrmwrk.mo : SOURCE = getoptfrmwrk.po
getoptfrmwrk.mo : TARGET = $(SOURCE:%.po=%).mo
.ONESHELL:
getoptfrmwrk.mo : getoptfrmwrk.po
ifeq ($(strip $(LANG)),)
	mkdir -p ./$(LANG)/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	mv -v ./$(TARGET) ./$(LANG)/LC_MESSAGES/
else
	mkdir -p ./sr_RS@latin/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	mv -v ./$(TARGET) ./sr_RS@latin/LC_MESSAGES/
endif

getoptfrmwrk.po : SOURCE = getoptfrmwrk.pot
getoptfrmwrk.po : TARGET = $(SOURCE:%.pot=%).po
getoptfrmwrk.po : getoptfrmwrk.pot
ifeq ($(strip $(LANG)),)
	msginit -l $(LANG) -o $(TARGET) -i $(SOURCE)
else
	msginit -l sr_RS@latin -o $(TARGET) -i $(SOURCE)
endif

getoptfrmwrk.pot : SOURCE = getoptfrmwrk.ppc
getoptfrmwrk.pot : DOMAIN = $(SOURCE:%.ppc=%)
getoptfrmwrk.pot : VERSION = 1.0
getoptfrmwrk.pot : TARGET = $(DOMAIN).pot
getoptfrmwrk.pot : getoptfrmwrk.ppc
	xgettext -o $(TARGET) --package-name="$(DOMAIN)" \
		--package-version="$(VERSION)" \
		--msgid-bugs-address="$(BUG_ADDRESS)" $(SOURCE)

getoptfrmwrk.ppc : SOURCE = getoptfrmwrk.c
getoptfrmwrk.ppc : TARGET = $(SOURCE:%.c=%).ppc
getoptfrmwrk.ppc : EXTRA_FLAGS =
getoptfrmwrk.ppc : getoptfrmwrk.c
	cpp $(EXTRA_FLAGS) $(SOURCE) $(TARGET)



##
# glibfrmwrk section.
#
glibfrmwrk : SOURCES = glibfrmwrk.c
glibfrmwrk : TARGET = $(SOURCES:%.c=%)
glibfrmwrk : OBJS = $(TARGET).o
glibfrmwrk : LIBS = $(LIBGLIB2)
glibfrmwrk : EXTRA_FLAGS = $(GLIB2CFLAGS)
glibfrmwrk : glibfrmwrk.o
	gcc -o $(TARGET) $(OBJS) $(LIBS)

glibfrmwrk.o : glibfrmwrk.c
ifeq ($(RELEASE), true)
	gcc $(STD_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
else
	gcc $(STD_DBG_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
endif

# glibfrmwrk localisation section.
glibfrmwrk.mo : SOURCE = glibfrmwrk.po
glibfrmwrk.mo : TARGET = $(SOURCE:%.po=%).mo
.ONESHELL:
glibfrmwrk.mo : glibfrmwrk.po
ifeq ($(strip $(LANG)),)
	mkdir -p ./$(LANG)/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	mv -v ./$(TARGET) ./$(LANG)/LC_MESSAGES/
else
	mkdir -p ./sr_RS@latin/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	mv -v ./$(TARGET) ./sr_RS@latin/LC_MESSAGES/
endif

glibfrmwrk.po : SOURCE = glibfrmwrk.pot
glibfrmwrk.po : TARGET = $(SOURCE:%.pot=%).po
glibfrmwrk.po : glibfrmwrk.pot
ifeq ($(strip $(LANG)),)
	msginit -l $(LANG) -o $(TARGET) -i $(SOURCE)
else
	msginit -l sr_RS@latin -o $(TARGET) -i $(SOURCE)
endif

glibfrmwrk.pot : SOURCE = glibfrmwrk.ppc
glibfrmwrk.pot : DOMAIN = $(SOURCE:%.ppc=%)
glibfrmwrk.pot : VERSION = 1.0
glibfrmwrk.pot : TARGET = $(DOMAIN).pot
glibfrmwrk.pot : glibfrmwrk.ppc
	xgettext -o $(TARGET) --package-name="$(DOMAIN)" \
		--package-version="$(VERSION)" \
		--msgid-bugs-address="$(BUG_ADDRESS)" $(SOURCE)

glibfrmwrk.ppc : SOURCE = glibfrmwrk.c
glibfrmwrk.ppc : TARGET = $(SOURCE:%.c=%).ppc
glibfrmwrk.ppc : EXTRA_FLAGS = $(GLIB2CFLAGS)
glibfrmwrk.ppc : glibfrmwrk.c
	cpp $(EXTRA_FLAGS) $(SOURCE) $(TARGET)



##
# glibprocesstream section.
#
glibprocesstream : SOURCES = glibprocesstream.c
glibprocesstream : TARGET = $(SOURCES:%.c=%)
glibprocesstream : OBJS = $(TARGET).o
glibprocesstream : LIBS = $(LIBGLIB2)
glibprocesstream : EXTRA_FLAGS = $(GLIB2CFLAGS)
glibprocesstream : glibprocesstream.o
	gcc -o $(TARGET) $(OBJS) $(LIBS)

glibprocesstream.o : glibprocesstream.c
ifeq ($(RELEASE), true)
	gcc $(STD_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
else
	gcc $(STD_DBG_FLAGS) $(EXTRA_FLAGS) -c $(SOURCES)
endif

# glibprocesstream localisation section.
glibprocesstream.mo : SOURCE = glibprocesstream.po
glibprocesstream.mo : TARGET = $(SOURCE:%.po=%).mo
.ONESHELL:
glibprocesstream.mo : glibprocesstream.po
ifeq ($(strip $(LANG)),)
	mkdir -p ./$(LANG)/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	mv -v ./$(TARGET) ./$(LANG)/LC_MESSAGES/
else
	mkdir -p ./sr_RS@latin/LC_MESSAGES
	msgfmt -c -v -o $(TARGET) $(SOURCE)
	mv -v ./$(TARGET) ./sr_RS@latin/LC_MESSAGES/
endif

glibprocesstream.po : SOURCE = glibprocesstream.pot
glibprocesstream.po : TARGET = $(SOURCE:%.pot=%).po
glibprocesstream.po : glibprocesstream.pot
ifeq ($(strip $(LANG)),)
	msginit -l $(LANG) -o $(TARGET) -i $(SOURCE)
else
	msginit -l sr_RS@latin -o $(TARGET) -i $(SOURCE)
endif

glibprocesstream.pot : SOURCE = glibprocesstream.ppc
glibprocesstream.pot : DOMAIN = $(SOURCE:%.ppc=%)
glibprocesstream.pot : VERSION = 1.0
glibprocesstream.pot : TARGET = $(DOMAIN).pot
glibprocesstream.pot : glibprocesstream.ppc
	xgettext -o $(TARGET) --package-name="$(DOMAIN)" \
		--package-version="$(VERSION)" \
		--msgid-bugs-address="$(BUG_ADDRESS)" $(SOURCE)

glibprocesstream.ppc : SOURCE = glibprocesstream.c
glibprocesstream.ppc : TARGET = $(SOURCE:%.c=%).ppc
glibprocesstream.ppc : EXTRA_FLAGS = $(GLIB2CFLAGS)
glibprocesstream.ppc : glibprocesstream.c
	cpp $(EXTRA_FLAGS) $(SOURCE) $(TARGET)



##
# Cleanup section.
#
clean :
	rm -v ./*.o ./*~

cleanall :
	rm -v $(foreach TARGET,$(TARGETS),./$(TARGET)) ./*.o ./*~ ./*.ppc ./*.pot
