CC      = cc
GCOV    = gcov
CFLAGS  = $(DCFLAGS) -Wall -I. -I..
LDFLAGS += -lc $(DLDFLAGS)

SOURCES = \
	dt_accessor.c \
	dt_arithmetic.c \
	dt_core.c \
	dt_dow.c \
	dt_easter.c \
	dt_length.c \
	dt_navigate.c \
	dt_parse_iso.c  \
	dt_search.c \
	dt_tm.c \
	dt_util.c \
	dt_valid.c \
	dt_weekday.c \
	dt_workday.c

OBJECTS = \
	dt_accessor.o \
	dt_arithmetic.o \
	dt_core.o \
	dt_dow.o \
	dt_easter.o \
	dt_length.o \
	dt_navigate.o \
	dt_parse_iso.o \
	dt_search.o \
	dt_tm.o \
	dt_util.o \
	dt_valid.o \
	dt_weekday.o \
	dt_workday.o

HARNESS_OBJS = \
	t/add_years.o \
	t/add_quarters.o \
	t/add_months.o \
	t/add_weekdays.o \
	t/add_workdays.o \
	t/days_in_month.o \
	t/days_in_quarter.o \
	t/days_in_year.o \
	t/delta_weekdays.o \
	t/delta_workdays.o \
	t/delta_yd.o \
	t/delta_ymd.o \
	t/delta_yqd.o \
	t/easter_orthodox.o \
	t/easter_western.o \
	t/end_of_month.o \
	t/end_of_quarter.o \
	t/end_of_week.o \
	t/end_of_year.o \
	t/is_holiday.o \
	t/is_workday.o \
	t/next_dow.o \
	t/next_weekday.o \
	t/nth_dow.o \
	t/parse_iso_date.o \
	t/parse_iso_time.o \
	t/parse_iso_zone.o \
	t/parse_iso_zone_lenient.o \
	t/prev_dow.o \
	t/prev_weekday.o \
	t/roll_workday.o \
	t/start_of_month.o \
	t/start_of_quarter.o \
	t/start_of_week.o \
	t/start_of_year.o \
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
	t/start_of_year.t \
	t/start_of_quarter.t \
	t/start_of_month.t \
	t/start_of_week.t \
	t/end_of_year.t \
	t/end_of_quarter.t \
	t/end_of_month.t \
	t/end_of_week.t \
	t/next_dow.t \
	t/prev_dow.t \
	t/next_weekday.t \
	t/prev_weekday.t \
	t/nth_dow.t \
	t/add_years.t \
	t/add_quarters.t \
	t/add_months.t \
	t/add_weekdays.t \
	t/delta_yd.t \
	t/delta_ymd.t \
	t/delta_yqd.t \
	t/delta_weekdays.t \
	t/parse_iso_date.t \
	t/parse_iso_time.t \
	t/parse_iso_zone.t \
	t/parse_iso_zone_lenient.t \
	t/add_workdays.t \
	t/delta_workdays.t \
	t/is_holiday.t \
	t/is_workday.t \
	t/roll_workday.t

HARNESS_DEPS = \
	$(OBJECTS) \
	t/tap.o

.SUFFIXES:
.SUFFIXES: .o .c .t

.PHONY: check-asan test gcov cover clean

.o.t:
	$(CC) $(LDFLAGS) $< $(HARNESS_DEPS) -o $@

dt_accessor.o: \
	dt_accessor.h dt_accessor.c

dt_arithmetic.o: \
	dt_arithmetic.h dt_arithmetic.c

dt_core.o: \
	dt_config.h dt_core.h dt_core.c

dt_dow.o: \
	dt_dow.h dt_dow.c

dt_easter.o: \
	dt_easter.h dt_easter.c

dt_length.o: \
	dt_length.h dt_length.c

dt_navigate.o: \
	dt_navigate.h dt_navigate.c

dt_parse_iso.o: \
	dt_parse_iso.h dt_parse_iso.c

dt_search.o: \
	dt_search.h dt_search.c

dt_tm.o: \
	dt_tm.h dt_tm.c

dt_weekday.o: \
	dt_weekday.h dt_weekday.c

dt_workday.o: \
	dt_workday.h dt_workday.c

t/tap.o: \
	t/tap.h t/tap.c

t/add_years.o: \
	$(HARNESS_DEPS) t/add_years.c
t/add_quarters.o: \
	$(HARNESS_DEPS) t/add_quarters.c
t/add_months.o: \
	$(HARNESS_DEPS) t/add_months.c t/add_months.h
t/add_weekdays.o: \
	$(HARNESS_DEPS) t/add_weekdays.c
t/add_workdays.o: \
	$(HARNESS_DEPS) t/add_workdays.c
t/days_in_month.o: \
	$(HARNESS_DEPS) t/days_in_month.c
t/days_in_quarter.o: \
	$(HARNESS_DEPS) t/days_in_quarter.c
t/days_in_year.o: \
	$(HARNESS_DEPS) t/days_in_year.c
t/delta_weekdays.o: \
	$(HARNESS_DEPS) t/delta_weekdays.c
t/delta_workdays.o: \
	$(HARNESS_DEPS) t/delta_workdays.c
t/delta_yd.o: \
	$(HARNESS_DEPS) t/delta_yd.c
t/delta_ymd.o: \
	$(HARNESS_DEPS) t/delta_ymd.c
t/delta_yqd.o: \
	$(HARNESS_DEPS) t/delta_yqd.c
t/easter_orthodox.o: \
	$(HARNESS_DEPS) t/easter_orthodox.c t/easter_orthodox.h
t/easter_western.o: \
	$(HARNESS_DEPS) t/easter_western.c t/easter_western.h
t/end_of_month.o: \
	$(HARNESS_DEPS) t/end_of_month.c t/end_of_month.h
t/end_of_quarter.o: \
	$(HARNESS_DEPS) t/end_of_quarter.c t/end_of_quarter.h
t/end_of_week.o: \
	$(HARNESS_DEPS) t/end_of_week.c
t/end_of_year.o: \
	$(HARNESS_DEPS) t/end_of_year.c
t/is_holiday.o: \
	$(HARNESS_DEPS) t/is_holiday.c
t/is_workday.o: \
	$(HARNESS_DEPS) t/is_workday.c
t/next_dow.o: \
	$(HARNESS_DEPS) t/next_dow.c
t/next_weekday.o: \
	$(HARNESS_DEPS) t/next_weekday.c
t/nth_dow.o: \
	$(HARNESS_DEPS) t/nth_dow.c t/nth_dow.h
t/roll_workday.o: \
	$(HARNESS_DEPS) t/roll_workday.c
t/parse_iso_date.o: \
	$(HARNESS_DEPS) t/parse_iso_date.c
t/parse_iso_time.o: \
	$(HARNESS_DEPS) t/parse_iso_time.c
t/parse_iso_zone.o: \
	$(HARNESS_DEPS) t/parse_iso_zone.c
t/parse_iso_zone_lenient.o: \
	$(HARNESS_DEPS) t/parse_iso_zone_lenient.c
t/prev_dow.o: \
	$(HARNESS_DEPS) t/prev_dow.c
t/prev_weekday.o: \
	$(HARNESS_DEPS) t/prev_weekday.c
t/start_of_month.o: \
	$(HARNESS_DEPS) t/start_of_month.c t/start_of_month.h
t/start_of_quarter.o: \
	$(HARNESS_DEPS) t/start_of_quarter.c t/start_of_quarter.h
t/start_of_week.o: \
	$(HARNESS_DEPS) t/start_of_week.c
t/start_of_year.o: \
	$(HARNESS_DEPS) t/start_of_year.c
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

test: $(HARNESS_EXES) 
	@prove $(HARNESS_EXES)

check-asan:
	@$(MAKE) DCFLAGS="-O1 -g -faddress-sanitizer -fno-omit-frame-pointer" \
	DLDFLAGS="-g -faddress-sanitizer" test

gcov:
	@$(MAKE) DCFLAGS="-O0 -g -coverage" DLDFLAGS="-coverage" test
	@$(GCOV) $(SOURCES)

cover:
	@$(MAKE) DCFLAGS="-O0 -g --coverage" DLDFLAGS="-coverage" test
	@$(GCOV) -abc $(SOURCES) 
	@gcov2perl *.gcov
	@cover --no-gcov

clean:
	rm -f $(HARNESS_DEPS) $(HARNESS_OBJS) $(HARNESS_EXES) *.gc{ov,da,no} t/*.gc{ov,da,no}

