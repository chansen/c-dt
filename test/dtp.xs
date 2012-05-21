#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "dt.h"

MODULE = dtp   PACKAGE = dtp

PROTOTYPES: DISABLE

BOOT:
{
#define const_iv(name)                                      \
STMT_START {                                                \
    newCONSTSUB(stash, #name, newSViv((IV)name));           \
    av_push(export, newSVpvn(#name, sizeof(#name) - 1));    \
} STMT_END

    HV *stash  = gv_stashpv("dtp", TRUE);
    AV *export = get_av("dtp::EXPORT_OK", TRUE);

    /* dt_easter_t */
    const_iv(DT_ORTHODOX);
    const_iv(DT_WESTERN);

    /* dt_day_of_week_t */
    const_iv(DT_MONDAY);
    const_iv(DT_TUESDAY);
    const_iv(DT_WEDNESDAY);
    const_iv(DT_THURSDAY);
    const_iv(DT_FRIDAY);
    const_iv(DT_SATURDAY);
    const_iv(DT_SUNDAY);
}

int
dt_from_cjdn(n)
    int n

int
dt_from_easter(y, c)
    int y
    int c

int
dt_from_yd(y, d)
    int y
    int d

int 
dt_from_ymd(y, m, d)
    int y
    int m
    int d

int
dt_from_yqd(y, q, d)
    int y
    int q
    int d

int
dt_from_ywd(y, w, d)
    int y
    int w
    int d

bool
dt_valid_yd(y, d)
    int y
    int d

bool 
dt_valid_ymd(y, m, d)
    int y
    int m
    int d

bool
dt_valid_yqd(y, q, d)
    int y
    int q
    int d

bool
dt_valid_ywd(y, w, d)
    int y
    int w
    int d

void
dt_to_yd(dt)
    int dt
  PREINIT:
    int y, d;
  PPCODE:
    dt_to_yd(dt, &y, &d);
    EXTEND(SP, 2);
    mPUSHi(y);
    mPUSHi(d);

void
dt_to_ymd(dt)
    int dt
  PREINIT:
    int y, m, d;
  PPCODE:
    dt_to_ymd(dt, &y, &m, &d);
    EXTEND(SP, 3);
    mPUSHi(y);
    mPUSHi(m);
    mPUSHi(d);

void
dt_to_yqd(dt)
    int dt
  PREINIT:
    int y, q, d;
  PPCODE:
    dt_to_yqd(dt, &y, &q, &d);
    EXTEND(SP, 3);
    mPUSHi(y);
    mPUSHi(q);
    mPUSHi(d);

void
dt_to_ywd(dt)
    int dt
  PREINIT:
    int y, w, d;
  PPCODE:
    dt_to_ywd(dt, &y, &w, &d);
    EXTEND(SP, 3);
    mPUSHi(y);
    mPUSHi(w);
    mPUSHi(d);

int
dt_cjdn(dt)
    int dt

int
dt_year(dt)
    int dt

int
dt_quarter(dt)
    int dt

int
dt_month(dt)
    int dt

int
dt_day_of_year(dt)
    int dt

int
dt_day_of_quarter(dt)
    int dt

int
dt_day_of_month(dt)
    int dt

int
dt_day_of_week(dt)
    int dt

int
dt_week_of_year(dt)
    int dt

int
dt_year_of_week(dt)
    int dt

int
dt_first_day_of_year(dt, offset)
    int dt
    int offset

int
dt_first_day_of_quarter(dt, offset)
    int dt
    int offset

int
dt_first_day_of_month(dt, offset)
    int dt
    int offset

int
dt_first_day_of_week(dt, first_dow)
    int dt
    int first_dow

int
dt_last_day_of_year(dt, offset)
    int dt
    int offset

int
dt_last_day_of_quarter(dt, offset)
    int dt
    int offset

int
dt_last_day_of_month(dt, offset)
    int dt
    int offset

int
dt_last_day_of_week(dt, first_dow)
    int dt
    int first_dow

int
dt_nth_day_of_week(dt, nth, dow)
    int dt
    int nth
    int dow

int
dt_next_day_of_week(dt, dow, current)
    int dt
    int dow
    bool current

int
dt_prev_day_of_week(dt, dow, current)
    int dt
    int dow
    bool current

int
dt_add_quarters(dt, delta, adjust)
    int dt
    int delta
    int adjust

int
dt_add_months(dt, delta, adjust)
    int dt
    int delta
    int adjust

int
dt_delta_years(dt1, dt2)
    int dt1
    int dt2

int
dt_delta_quarters(dt1, dt2)
    int dt1
    int dt2

int
dt_delta_months(dt1, dt2)
    int dt1
    int dt2

int
dt_delta_weeks(dt1, dt2)
    int dt1
    int dt2


