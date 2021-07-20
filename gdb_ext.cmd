set print elements 4096
set pagination off

define dd
  disable $arg0
end

define ee
  enable $arg0
end

define GDBrst
  call (void)GDBrst_CHK(1)
end

define memchk
  call (void)GDBmemchk($arg0)
end


define GDBsumI
  call (void)GDBsumIV($arg0, $arg1, 1)
end

define GDBmin
  call (void)GDBmin($arg0, $arg1)
end

define GDBmax
  call (void)GDBmax($arg0, $arg1)
end


define GDBvec
  call (void)GDBvec($arg0, $arg1)
end

define GDBivec
  call (void)GDBivec($arg0, $arg1)
end



define gIVECset
  call BlockIntCfg($arg0, $arg2,  $arg1)
end

define gVECrand
  call VEC_noise($arg0, $arg1,  $arg2)
end



define svIVECx
  call (void)GDB_IntSave("$arg0", $arg0,  $arg1,1)
end

define svIVEC
  call (void)GDB_IntSave("$arg2", $arg0, $arg1,1)
end

define svSHORTS
  call (void)GDB_ShortSave("$arg2", $arg0, $arg1,1)
end


define svFlts
  call (void)GDB_FltSave("$arg0", $arg0,  $arg1,1)
end




define svFltsx
  call (void)GDB_FltSave("$arg2", $arg0, $arg1,1)
end

define svVf
  call (void)GDB_FltSave("$arg2", $arg0, $arg1,1)
end


define svMf
  call (void)GDB_FltSave("$arg3", ($arg0), $arg2, $arg1)
end

define svMi
  call (void)GDB_IntSave("$arg3", ($arg0), $arg2, $arg1)
end


define svCxV
  call (void)GDB_CxSave("$arg0", $arg0,  1 , $arg1 )
end

define svCxVx
  call (void)GDB_CxSave("$arg2", $arg0,  1 , $arg1 )
end

define svCxM
  call (void)GDB_CxSave("$arg0", $arg0,  $arg2 , $arg1 )
end

define svCxMx
  call (void)GDB_CxSave("$arg3", $arg0,  $arg2 , $arg1 )
end

define setINT
  set *((int *) &$arg0) = $arg1
end

define setFLT
  set *((float *) &$arg0) = $arg1
end

define pm
  call (void)GDBmtx($arg0, $arg1,$arg2)
end

define pcxm
  call (void)GDBcxm($arg0, $arg1,$arg2,1)
end

define pmi
  call (void)GDBimtx($arg0, $arg1,$arg2)
end

define pmtx
  call (void)GDBmtx($arg0, $arg1,$arg2)
end

define pv
  p  *($arg0)@ $arg1
end

define pmtx_row 
  call (void)GDBfmxrow($arg0, $arg1,$arg2,$arg3) 
end

define pimtx_row 
  call (void)GDBimxrow($arg0, $arg1,$arg2,$arg3) 
end

define pvx
  p/x *($arg0)@ $arg1
end

define px
  p/x $arg0
end


define pb
  p  /t $arg0
end


define show_8xepi16
 p  *(short *)&$arg0@8
end

define show_4xepi32
 p  *(int *)&$arg0@4
end

define show_m256i
 p  *(int *)&$arg0@8
end

define pymmix
 p/x  *(int *)&$arg0@8
end

define pymmi
 p  *(int *)&$arg0@8
end

define pymmib
 p  /t *(int *)&$arg0@8
end

define show_mtx
set $vfMatrix = $arg0
set $Col = $arg2
set $Row = $arg1
set $i=0
while($i < $Row)
 p *($vfMatrix + $i*$Col)@$Col
 set $i = $i + 1
 end
end
