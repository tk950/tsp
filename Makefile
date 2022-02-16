CC = gcc

BINDIR = bin
INCLUDEDIR = include
SRCDIR = src

CFLAGS = -Wall -I$(INCLUDEDIR)
LDLIBS = -lm

# wildcard関数で SRCDIR以下のcファイルをリスト
SRCS = $(wildcard $(SRCDIR)/*.c)
# SRCSの拡張子を置き換える
OBJS = $(SRCS:%.c=%.o)


TARGET = $(BINDIR)/tsp
GENCITY = $(BINDIR)/gencity

all: $(TARGET) $(GENCITY)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(GENCITY): data/gencity.c
	$(CC) -o $@ $^

.PHONY: tmpclean clean

tmpclean:
	rm -f $(SRCDIR)/*~ *~
clean: tmpclean
	rm -f $(TARGET) $(GENCITY) $(OBJS)
