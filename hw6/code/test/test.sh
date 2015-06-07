time ../hw6_3 < testdata/dst_small.in > my.dst_small.out
time ../hw6_3 < testdata/dst.in > my.dst.out
time ../hw6_3 < testdata/rpt_small.in > my.rpt_small.out
time ../hw6_3 < testdata/rpt.in > my.rpt.out

diff testdata/dst_small.out my.dst_small.out
diff testdata/rpt_small.out my.rpt_small.out
diff testdata/dst.out my.dst.out
diff testdata/rpt.out my.rpt.out
