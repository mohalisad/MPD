<?php
include_once "random.php";
include_once "date.php";
define("_KEY", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?");
define("_KEY_LENGTH", 64);
define("SALT_LENGTH", 16);
define("MULTIPLY", 1.2);
define("DISORDER_RATE", 6);

class Cryptor {
    private $r;

    public function __construct() {
        $this->r = new Random (Date::now());
    }

    private function randomString($length) {
        $retu = "";
        for ($i = 0; $i < $length; $i++) {
            $retu .= _KEY[$this->r->generate() % _KEY_LENGTH];
        }
        return $retu;
    }

    private static function makeDisorderMoves($length, $key) {
        $loopCount = DISORDER_RATE * $length * 2;
        $arr = [];
        $ran = new Random($key);
        for ($i = 0; $i < $loopCount; $i++) {
            $arr[] = $ran->generate() % $length;
        }
        return $arr;
    }

    private static function makeDisorderArray($length, $disorderMoves) {
        $loopCount = DISORDER_RATE * $length * 2;
        $ret = [];
        for ($i = 0; $i < $length; $i++) {
            $ret[] = $i;
        }
        for ($i = 0; $i < $loopCount; $i += 2) {
            $c = $ret[$disorderMoves[$i]];
            $ret[$disorderMoves[$i]] = $ret[$disorderMoves[$i + 1]];
            $ret[$disorderMoves[$i + 1]] = $c;
        }
        return $ret;
    }

    private static function bitSet($input, $position, $toWhat) {
        $pow2 = 1;
        for ($i = 0; $i < $position; $i++) $pow2 *= 2;
        if ((($input & $pow2) != 0) == $toWhat) return $input;
        if ($toWhat) return $input | $pow2; else
            return $input & (63 - $pow2);
    }

    private static function bitGet($input, $position) {
        $pow2 = 1;
        for ($i = 0; $i < $position; $i++) $pow2 *= 2;
        return ($input & $pow2) != 0;
    }

    private static function getPossition($input) {
        return strpos(_KEY, $input);
    }

    public function encrypt($_input, $key) {
        $retu = "";
        $input = $_input;
        $pointer = 0;
        $length = (int)(MULTIPLY * (strlen($input) + 1) * 8);
        $length = $length + 6 - $length % 6;
        $salt = $this->randomString(SALT_LENGTH);
        $disorderMoves = $this->makeDisorderMoves($length, $key . $salt);
        $disorderArray = $this->makeDisorderArray($length, $disorderMoves);
        $chars = [];
        for ($i = 0; $i < $length / 6; $i++) $chars[] = 0;
        for ($i = 0; $i < strlen($input); $i++) {
            for ($j = 1; $j < 256; $j = $j * 2) {
                $chars[(int)($disorderArray[$pointer] / 6)] = $this->bitSet($chars[(int)($disorderArray[$pointer] / 6)], $disorderArray[$pointer] % 6, (ord($input[$i]) & $j) != 0);
                $pointer++;
            }
        }
        for ($j = 1; $j < 256; $j = $j * 2) {
            $chars[$disorderArray[$pointer] / 6] = $this->bitSet($chars[$disorderArray[$pointer] / 6], $disorderArray[$pointer] % 6, 0);
            $pointer++;
        }
        for (; $pointer < $length; $pointer++) {
            $chars[$disorderArray[$pointer] / 6] = $this->bitSet($chars[$disorderArray[$pointer] / 6], $disorderArray[$pointer] % 6, ($this->r->generate() % 2) != 0);
        }
        for ($i = 0; $i < $length / 6; $i++) {
            $retu .= _KEY[$chars[$i]];
        }
        return $retu . $salt;
    }

    public function decrypt($input, $key) {
        $retchars = "";
        $salt = substr($input, strlen($input) - SALT_LENGTH);
        $input = substr($input, 0, strlen($input) - SALT_LENGTH);
        $length = strlen($input) * 6;
        $disorderMoves = $this->makeDisorderMoves($length, $key . $salt);
        $disorderArray = $this->makeDisorderArray($length, $disorderMoves);
        $chars = [];
        for ($i = 0; $i < $length / 6; $i++) $chars[] = $this->getPossition($input[$i]);
        $pointer = 0;
        while ($pointer < $length) {
            $temp = 0;
            for ($j = 0; $j < 8; $j++) {
                $temp = $this->bitSet($temp, $j, $this->bitGet($chars[(int)($disorderArray[$pointer] / 6)], $disorderArray[$pointer] % 6));
                $pointer++;
                if ($pointer == $length) break;
            }
            if ($temp == 0) break;
            $retchars .= chr($temp);
        }
        return $retchars;
    }
}
/*
$line = fgets(STDIN);
$c = new Cryptor();
$a = $c->encrypt($line,"asdsdf");
echo $a."\n";
echo $c->decrypt($a,"asdsdf")."\n";*/
