CC      = cc
GCOV    = gcov
CFLAGS  = $(DCFLAGS) -Wall -I. -I..
LDFLAGS += -lc $(DLDFLAGS)

HARNESS_OBJS = \
	t/add_years.o \
	t/add_months.o \
	t/days_in_month.o \
	t/days_in_quarter.o \
	t/days_in_year.o \
	t/easter_orthodox.o \
	t/easter_western.o \
	t/first_day_of_month.o \
	t/first_day_of_quarter.o \
	t/first_day_of_week.o \
	t/first_day_of_year.o \
	t/last_day_of_month.o \
	t/last_day_of_quarter.o \
	t/last_day_of_week.o \
	t/last_day_of_year.o \
	t/next_day_of_week.o \
	t/next_weekday.o \
	t/nth_day_of_week.o \
	t/parse_string.o \
	t/prev_day_of_week.o \
	t/prev_weekday.o \
	t/tm.o \
	t/yd.o \
	t/ymd.o \
	t/ymd_epochs.o \
	t/yqd.o \
	t/ywd.o \

HARNESS_EXES = \
	t/yd.t \
	t/ymd.t \
	t/ymd_epochs.t \
	t/yqd.t \
	t/ywd.t \
	t/tm.t \
	t/easter_western.t \
	t/easter_orthodox.t \
	t/days_in_year.t \
	t/days_in_month.t \
	t/days_in_quarter.t \
	t/first_day_of_year.t \
	t/first_day_of_quarter.t \
	t/first_day_of_month.t \
	t/first_day_of_week.t \
	t/last_day_of_year.t \
	t/last_day_of_quarter.t \
	t/last_day_of_month.t \
	t/last_day_of_week.t \
	t/next_day_of_week.t \
	t/prev_day_of_week.t \
	t/next_weekday.t \
	t/prev_weekday.t \
	t/nth_day_of_week.t \
	t/add_years.t \
	t/add_months.t \
	t/parse_string.t

HARNESS_DEPS = \
	dt.o \
	t/tap.o

.SUFFIXES:
.SUFFIXES: .o .c .t

.PHONY: all compile harness test gcov cover clean

.o.t:
	$(CC) $(LDFLAGS) $< dt.o t/tap.o -o $@

dt.o: \
	dtconfig.h dt.h dt.c
t/tap.o: \
	t/tap.h t/tap.c

t/add_years.o: \
	$(HARNESS_DEPS) t/add_years.c
t/add_months.o: \
	$(HARNESS_DEPS) t/add_months.c t/add_months.h
t/days_in_month.o: \
	$(HARNESS_DEPS) t/days_in_month.c
t/days_in_quarter.o: \
	$(HARNESS_DEPS) t/days_in_quarter.c
t/days_in_year.o: \
	$(HARNESS_DEPS) t/days_in_year.c
t/easter_orthodox.o: \
	$(HARNESS_DEPS) t/easter_orthodox.c t/easter_orthodox.h
t/easter_western.o: \
	$(HARNESS_DEPS) t/easter_western.c t/easter_western.h
t/first_day_of_month.o: \
	$(HARNESS_DEPS) t/first_day_of_month.c t/first_day_of_month.h
t/first_day_of_quarter.o: \
	$(HARNESS_DEPS) t/first_day_of_quarter.c t/first_day_of_quarter.h
t/first_day_of_week.o: \
	$(HARNESS_DEPS) t/first_day_of_week.c
t/first_day_of_year.o: \
	$(HARNESS_DEPS) t/first_day_of_year.c
t/last_day_of_month.o: \
	$(HARNESS_DEPS) t/last_day_of_month.c t/last_day_of_month.h
t/last_day_of_quarter.o: \
	$(HARNESS_DEPS) t/last_day_of_quarter.c t/last_day_of_quarter.h
t/last_day_of_week.o: \
	$(HARNESS_DEPS) t/last_day_of_week.c
t/last_day_of_year.o: \
	$(HARNESS_DEPS) t/last_day_of_year.c
t/next_day_of_week.o: \
	$(HARNESS_DEPS) t/next_day_of_week.c
t/next_weekday.o: \
	$(HARNESS_DEPS) t/next_weekday.c
t/nth_day_of_week.o: \
	$(HARNESS_DEPS) t/nth_day_of_week.c t/nth_day_of_week.h
t/parse_string.o: \
	$(HARNESS_DEPS) t/parse_string.c
t/prev_day_of_week.o: \
	$(HARNESS_DEPS) t/prev_day_of_week.c
t/prev_weekday.o: \
	$(HARNESS_DEPS) t/prev_weekday.c
t/tm.o: \
	$(HARNESS_DEPS) t/tm.c
t/yd.o: \
	$(HARNESS_DEPS) t/yd.c
t/ymd.o: \
	$(HARNESS_DEPS) t/ymd.c
t/ymd_epochs.o: \
	$(HARNESS_DEPS) t/ymd_epochs.c
t/yqd.o: \
	$(HARNESS_DEPS) t/yqd.c
t/ywd.o: \
	$(HARNESS_DEPS) t/ywd.c t/ywd.h


all: \
	compile

compile: \
	dt.o

harness: \
	$(HARNESS_EXES)

test: harness 
	@prove $(HARNESS_EXES)

gcov:
	@$(MAKE) DCFLAGS="-O0 -g -coverage" DLDFLAGS="-coverage" test
	@$(GCOV) dt.c

cover:
	@$(MAKE) DCFLAGS="-O0 -g --coverage" DLDFLAGS="-coverage" test
	@$(GCOV) -abc dt.c
	@gcov2perl dt.c.gcov
	@cover --no-gcov

clean:
	rm -f $(HARNESS_DEPS) $(HARNESS_OBJS) $(HARNESS_EXES) *.gc{ov,da,no} t/*.gc{ov,da,no}

