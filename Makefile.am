AM_CFLAGS = -I$(top_srcdir) -Iinclude -Wall -Werror -Wextra -std=c99

#SUBDIRS = src

bin_PROGRAMS = text-analyse
text_analyse_SOURCES = \
			src/main.c \
			src/analyse.c \
			src/bst.c \
			src/fgetline.c \
			src/syllablecount.c \
			src/word.c \
			src/sen_bgn_wrd.c
noinst_HEADERS = include/text_analysis.h include/main.h include/bst.h
