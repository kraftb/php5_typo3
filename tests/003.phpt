--TEST--
Check for icebear presence
--SKIPIF--
<?php if (!extension_loaded("icebear")) print "skip"; ?>
--FILE--
<?php 
$obj = new t3lib_div();
$res = $obj->trimExplode(',', 'wert1, wert2, wert3', true);
echo $res[1];
/*
	you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

	see php5/README.TESTING for further information on
  writing regression tests
*/
?>
--EXPECT--
wert2
