#include "dt.h"
#include "tap.h"

int 
main() {
    const dt_zone_t *zone;
    size_t len;

    {
        len = dt_zone_lookup("cst", 3, &zone);
        cmp_ok(len, "==", 3, "dt_zone_lookup(cst)");
        is(dt_zone_name(zone), "CST", "name is CST");
        ok(dt_zone_is_rfc(zone), "CST is RFC");
        ok(dt_zone_is_ambiguous(zone), "CST is ambiguous");
        ok(!dt_zone_is_utc(zone), "CST is not universal");
        ok(!dt_zone_is_military(zone), "CST is not military");
        cmp_ok(dt_zone_offset(zone), "==", -6*60, "CST offset");
    }

    {
        len = dt_zone_lookup("UTC", 3, &zone);
        cmp_ok(len, "==", 3, "dt_zone_lookup(UTC)");
        is(dt_zone_name(zone), "UTC", "name is UTC");
        ok(dt_zone_is_rfc(zone), "UTC is RFC");
        ok(!dt_zone_is_ambiguous(zone), "UTC is not ambiguous");
        ok(dt_zone_is_utc(zone), "UTC is universal");
        ok(!dt_zone_is_military(zone), "UTC is not military");
        cmp_ok(dt_zone_offset(zone), "==", 0, "UTC offset");
    }

    {
        len = dt_zone_lookup("YeKsT", 5, &zone);
        cmp_ok(len, "==", 5, "dt_zone_lookup(YeKsT)");
        is(dt_zone_name(zone), "YEKST", "name is YEKST");
    }

    done_testing();
}
