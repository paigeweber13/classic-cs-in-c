# No Compiler Flags

 status,sorting_algorithm,array_type,array_size,num_iterations,total_time_s,min_time_s,max_time_s,avg_time_s,avg_elements_per_second
SUCCESS,             heap,    random,      1000,            10,    0.004999,  0.000432,  0.000638,  0.000500,         2000400.080016
SUCCESS,             heap,    random,      2000,            10,    0.008280,  0.000758,  0.001024,  0.000828,         2415458.937198
SUCCESS,             heap,    random,      4000,            10,    0.012061,  0.001039,  0.001700,  0.001206,         3316474.587513
SUCCESS,             heap,    random,      8000,            10,    0.023145,  0.002102,  0.002740,  0.002314,         3456470.079931
SUCCESS,             heap,    random,     16000,            10,    0.049125,  0.004583,  0.005319,  0.004912,         3256997.455471
SUCCESS,             heap,    random,     32000,            10,    0.108031,  0.010116,  0.011912,  0.010803,         2962112.726902
SUCCESS,             heap,    random,     64000,            10,    0.228346,  0.022032,  0.023744,  0.022835,         2802764.226218
SUCCESS,        insertion,    random,      1000,            10,    0.017092,  0.001460,  0.002253,  0.001709,          585069.038147
SUCCESS,        insertion,    random,      2000,            10,    0.065332,  0.006086,  0.007047,  0.006533,          306128.696504
SUCCESS,        insertion,    random,      4000,            10,    0.255362,  0.024639,  0.027122,  0.025536,          156640.377190
SUCCESS,        insertion,    random,      8000,            10,    1.032880,  0.100187,  0.105900,  0.103288,           77453.334366
SUCCESS,        insertion,    random,     16000,            10,    4.037795,  0.375374,  0.414995,  0.403780,           39625.587728
SUCCESS,        insertion,    random,     32000,            10,   16.634650,  1.519835,  1.823092,  1.663465,           19236.954189
SUCCESS,        insertion,    random,     64000,            10,   64.613084,  6.081391,  6.958466,  6.461308,            9905.114574

# With `-O3` Flag

 status,sorting_algorithm,array_type,array_size,num_iterations,total_time_s,min_time_s,max_time_s,avg_time_s,avg_elements_per_second
SUCCESS,             heap,    random,      1000,            10,    0.006839,  0.000567,  0.000803,  0.000684,         1462202.076327
SUCCESS,             heap,    random,      2000,            10,    0.013887,  0.001262,  0.001511,  0.001389,         1440195.866638
SUCCESS,             heap,    random,      4000,            10,    0.012154,  0.000726,  0.002074,  0.001215,         3291097.581043
SUCCESS,             heap,    random,      8000,            10,    0.012248,  0.001069,  0.001575,  0.001225,         6531678.641411
SUCCESS,             heap,    random,     16000,            10,    0.025473,  0.002217,  0.003149,  0.002547,         6281160.444392
SUCCESS,             heap,    random,     32000,            10,    0.048594,  0.004533,  0.005132,  0.004859,         6585175.124501
SUCCESS,             heap,    random,     64000,            10,    0.099239,  0.009429,  0.011351,  0.009924,         6449077.479620
SUCCESS,        insertion,    random,      1000,            10,    0.008736,  0.000811,  0.000908,  0.000874,         1144688.644689
SUCCESS,        insertion,    random,      2000,            10,    0.036945,  0.003473,  0.004020,  0.003694,          541345.242929
SUCCESS,        insertion,    random,      4000,            10,    0.140164,  0.013538,  0.015677,  0.014016,          285379.983448
SUCCESS,        insertion,    random,      8000,            10,    0.556594,  0.055018,  0.058438,  0.055659,          143731.337384
SUCCESS,        insertion,    random,     16000,            10,    2.218795,  0.218231,  0.225877,  0.221880,           72111.213519
SUCCESS,        insertion,    random,     32000,            10,    9.350753,  0.885956,  1.009100,  0.935075,           34221.842883
SUCCESS,        insertion,    random,     64000,            10,   39.592121,  3.756509,  4.238245,  3.959212,           16164.832392


# With `-O3 -march=native` Flags

 status,sorting_algorithm,array_type,array_size,num_iterations,total_time_s,min_time_s,max_time_s,avg_time_s,avg_elements_per_second
SUCCESS,             heap,    random,      1000,            10,    0.007463,  0.000684,  0.000790,  0.000746,         1339943.722364
SUCCESS,             heap,    random,      2000,            10,    0.009341,  0.000548,  0.001975,  0.000934,         2141098.383471
SUCCESS,             heap,    random,      4000,            10,    0.010016,  0.000657,  0.001521,  0.001002,         3993610.223642
SUCCESS,             heap,    random,      8000,            10,    0.012693,  0.001012,  0.001741,  0.001269,         6302686.520129
SUCCESS,             heap,    random,     16000,            10,    0.023605,  0.002148,  0.002819,  0.002361,         6778224.952341
SUCCESS,             heap,    random,     32000,            10,    0.047870,  0.004582,  0.005164,  0.004787,         6684771.255484
SUCCESS,             heap,    random,     64000,            10,    0.097442,  0.009397,  0.011202,  0.009744,         6568009.687814
SUCCESS,        insertion,    random,      1000,            10,    0.009209,  0.000877,  0.001012,  0.000921,         1085894.233902
SUCCESS,        insertion,    random,      2000,            10,    0.037463,  0.003559,  0.004209,  0.003746,          533860.075274
SUCCESS,        insertion,    random,      4000,            10,    0.142808,  0.013736,  0.015359,  0.014281,          280096.353145
SUCCESS,        insertion,    random,      8000,            10,    0.557456,  0.054629,  0.057508,  0.055746,          143509.084125
SUCCESS,        insertion,    random,     16000,            10,    2.234955,  0.219853,  0.229230,  0.223496,           71589.808296
SUCCESS,        insertion,    random,     32000,            10,    8.875322,  0.876313,  0.928601,  0.887532,           36055.029891
SUCCESS,        insertion,    random,     64000,            10,   36.663058,  3.520058,  4.054210,  3.666306,           17456.263468


# With `-O3 -march=native -mtune=native` Flags

 status,sorting_algorithm,array_type,array_size,num_iterations,total_time_s,min_time_s,max_time_s,avg_time_s,avg_elements_per_second
SUCCESS,             heap,    random,      1000,            10,    0.004382,  0.000382,  0.000551,  0.000438,         2282062.984938
SUCCESS,             heap,    random,      2000,            10,    0.009321,  0.000833,  0.001070,  0.000932,         2145692.522262
SUCCESS,             heap,    random,      4000,            10,    0.013610,  0.000862,  0.002051,  0.001361,         2939015.429831
SUCCESS,             heap,    random,      8000,            10,    0.014543,  0.001012,  0.001939,  0.001454,         5500928.281648
SUCCESS,             heap,    random,     16000,            10,    0.023242,  0.002151,  0.002987,  0.002324,         6884089.148954
SUCCESS,             heap,    random,     32000,            10,    0.047942,  0.004460,  0.005947,  0.004794,         6674731.967794
SUCCESS,             heap,    random,     64000,            10,    0.100046,  0.009380,  0.011461,  0.010005,         6397057.353617
SUCCESS,        insertion,    random,      1000,            10,    0.008986,  0.000810,  0.000960,  0.000899,         1112842.198976
SUCCESS,        insertion,    random,      2000,            10,    0.037746,  0.003420,  0.004182,  0.003775,          529857.468341
SUCCESS,        insertion,    random,      4000,            10,    0.139443,  0.013540,  0.014905,  0.013944,          286855.561054
SUCCESS,        insertion,    random,      8000,            10,    0.554906,  0.054251,  0.057717,  0.055491,          144168.561883
SUCCESS,        insertion,    random,     16000,            10,    2.211375,  0.217278,  0.226604,  0.221138,           72353.173930
SUCCESS,        insertion,    random,     32000,            10,    8.883766,  0.878562,  0.908627,  0.888377,           36020.759664
SUCCESS,        insertion,    random,     64000,            10,   37.076249,  3.596243,  3.863654,  3.707625,           17261.724615
