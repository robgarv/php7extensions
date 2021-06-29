<?php

  $x = 2;
  $y = vtsquare($x);
  print "$x squared  = $y\n";
  
  $x1 = 2;
  $x2 = 3;
  $y = vtadd2square($x1, $x2);
  print "vtadd2square: x1 = $x1 x2= $x2 y = $y\n";

  $phpPid = getmypid();
  $cPid = vtgetpid();
  print"php pid: $phpPid C pid: $cPid \n";
?>
