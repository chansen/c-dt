#include "dt.h"
#include "tap.h"

struct ymd {
    int y;
    int m;
    int d;
};

const struct ymd days[] = {
    {2013,  1,  1}, /* Tuesday, Nyårsdagen (New Year's Day) */
    {2013,  3, 29}, /* Friday, Långfredagen (Good Friday) */
    {2013,  4,  1}, /* Monday, Annandag påsk (Easter Monday) */
    {2013,  5,  1}, /* Wednesday, Första maj (First of May) */
    {2013,  5,  9}, /* Thursday, Kristi himmelsfärds dag (Ascension Day) */
    {2013,  6,  6}, /* Thursday, Sveriges nationaldag (National Day of Sweden) */
    {2013,  6, 21}, /* Friday, Midsommarafton (Midsummer's Eve) */
    {2013, 12, 24}, /* Tuesday, Julafton (Christmas Eve) */
    {2013, 12, 25}, /* Wednesday, Juldagen (Christmas Day) */
    {2013, 12, 26}, /* Thursday, Annandag jul (Boxing Day) */
    {2013, 12, 31}, /* Tuesday, Nyårsafton (New Year's Eve) */
};

const struct ymd weekdays[] = {
    {2013,  1,  2}, /* Wednesday  */
    {2013,  3, 28}, /* Thursday */
    {2013,  4,  2}, /* Tuesday */
    {2013,  5,  2}, /* Thursday */
    {2013, 12, 30}, /* Monday */
};


const struct ymd weekends[] = {
    {2013,  1,  6}, /* Sunday  */
    {2013,  2,  9}, /* Saturday */
    {2013,  4, 28}, /* Sunday */
    {2013,  5,  5}, /* Sunday */
    {2013, 12, 28}, /* Saturday */
};

int
main() {
    int ntests, nholidays;
    int i;
    dt_t holidays[20];

    nholidays = sizeof(days) / sizeof(*days);
    for (i = 0; i < nholidays; i++) {
        const struct ymd date = days[i];
        holidays[i] = dt_from_ymd(date.y, date.m, date.d);
    }

    ntests = sizeof(days) / sizeof(*days);
    for (i = 0; i < ntests; i++) {
        const struct ymd t = days[i];

        {
            dt_t dt = dt_from_ymd(t.y, t.m, t.d);
            ok(dt_is_holiday(dt, holidays, nholidays), "dt_is_holiday(%.4d-%.2d-%.2d)",
              t.y, t.m, t.d);
        }
    }

    ntests = sizeof(weekdays) / sizeof(*weekdays);
    for (i = 0; i < ntests; i++) {
        const struct ymd t = weekdays[i];

        {
            dt_t dt = dt_from_ymd(t.y, t.m, t.d);
            ok(!dt_is_holiday(dt, holidays, nholidays), "dt_is_holiday(%.4d-%.2d-%.2d)",
              t.y, t.m, t.d);
        }
    }
    
    ntests = sizeof(weekends) / sizeof(*weekends);
    for (i = 0; i < ntests; i++) {
        const struct ymd t = weekends[i];

        {
            dt_t dt = dt_from_ymd(t.y, t.m, t.d);
            ok(!dt_is_holiday(dt, holidays, nholidays), "dt_is_holiday(%.4d-%.2d-%.2d)",
              t.y, t.m, t.d);
        }
    }
    done_testing();
}

