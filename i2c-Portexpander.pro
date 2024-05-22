HEADERS += \
    MCP23017.h \
    i2c-host.h \
    pin.h \
    printS.h \
    uart_hard.h

SOURCES += \
    MCP23017.c \
    i2c-host.c \
    main.c \
    printS.c \
    uart_hard.c

DISTFILES += \
    Makefile

INCLUDEPATH += /usr/lib/avr/include