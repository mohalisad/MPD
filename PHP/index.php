<?php
include_once 'entry.php';



$key = fgets(STDIN);
$key = substr($key,0,-1);

$c = new Cryptor();

Entry::setUserKey($key);
$line = "سلام";
$e = new Entry(2,new Date(),$line);
$a = $e->getHash();
$e = new Entry($a);
//echo $e->getText()."\n";
echo $a."\n";
//echo Random::sha256_hash($key)."\n";
