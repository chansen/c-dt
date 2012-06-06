package dtp;
use strict;
use warnings;

BEGIN {
    our $VERSION = '0.01';
    our @EXPORT_OK = qw[ dt_from_cjdn
                         dt_from_easter
                         dt_from_yd
                         dt_from_ymd
                         dt_from_yqd
                         dt_from_ywd

                         dt_valid_yd
                         dt_valid_ymd
                         dt_valid_yqd
                         dt_valid_ywd

                         dt_to_yd
                         dt_to_ymd
                         dt_to_yqd
                         dt_to_ywd

                         dt_cjdn
                         dt_year
                         dt_quarter
                         dt_month
                         dt_week
                         dt_day

                         dt_day_of_year
                         dt_day_of_quarter
                         dt_day_of_week

                         dt_first_day_of_year
                         dt_first_day_of_quarter
                         dt_first_day_of_month
                         dt_first_day_of_week

                         dt_last_day_of_year
                         dt_last_day_of_quarter
                         dt_last_day_of_month
                         dt_last_day_of_week

                         dt_nth_day_of_week

                         dt_next_day_of_week
                         dt_prev_day_of_week

                         dt_next_weekday
                         dt_prev_weekday

                         dt_add_quarters
                         dt_add_months

                         dt_delta_years
                         dt_delta_quarters
                         dt_delta_months
                         dt_delta_weeks 
                         
                         dt_leap_year
                         dt_days_in_year
                         dt_days_in_quarter
                         dt_days_in_month ];

    our %EXPORT_TAGS = ( all => \@EXPORT_OK );

    require Exporter;
    *import = \&Exporter::import;

    require XSLoader; XSLoader::load(__PACKAGE__, $VERSION);
}

1;

