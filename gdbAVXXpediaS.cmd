
#!/bin/bash
function run_cmd () {
  echo "$*"
  $*
}
clear


export CFLAGS='-fPIC -m64 -mavx  -g  -c'
export LDLIBS_fftw='-I/usr/local/include -L/usr/local/lib -lfftw3f'
export LDLIBS_XPedia='-L./ -lXpediaBASE '


run_cmd rm -f XPedia_AMC.o
run_cmd g++ $CFLAGS  XPedia_AMC.c  -o XPedia_AMC.o


run_cmd rm -f XPedia_CODEC.o
run_cmd g++ $CFLAGS  XPedia_CODEC.c  -o XPedia_CODEC.o

run_cmd rm -f XPedia_waveform.o
run_cmd g++ $CFLAGS  XPedia_waveform.c  -o XPedia_waveform.o


run_cmd rm -f XPedia_SCMlsp.o
run_cmd g++ $CFLAGS  XPedia_SCMlsp.c  -o XPedia_SCMlsp.o



run_cmd rm -f XPedia_mimo.o
run_cmd g++ $CFLAGS  XPedia_mimo.c  -o XPedia_mimo.o

run_cmd rm -f XPedia_Uplink.o
run_cmd g++ $CFLAGS  XPedia_Uplink.c  -o XPedia_Uplink.o


run_cmd rm -f XPedia_Transceiver.o
run_cmd g++ $CFLAGS  XPedia_Transceiver.c  -o XPedia_Transceiver.o


run_cmd rm -f libXpedia.so
run_cmd g++ -shared XPedia_AMC.o  XPedia_CODEC.o XPedia_waveform.o XPedia_SCMlsp.o XPedia_mimo.o XPedia_Uplink.o  XPedia_Transceiver.o $LDLIBS_XPedia   -o libXpedia.so

