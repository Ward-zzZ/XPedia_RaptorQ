source gdb_ext.cmd
set history save on
set breakpoint pending on
set print thread-events off
set print pretty
#source ~/interactive/gdbrun.cmd
b gdb_tool
b PerfMetric_COMMgdb.c:31
run

