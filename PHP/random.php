<?php
define ("BASE",10);
define ("LENGTH",8);
define ("MAX_STATE",100000);

class Random{
  private $state;
  private $hash;
  public static function sha256_hash($input){
    return hash('sha256', $input);
  }
  public function __construct($input){
    $this->state = 0;
    $this->hash = Random::sha256_hash($input);
  }
  private function getState(){

    $this->state = ($this->state + 1) % MAX_STATE;
    return $this->state;
  }
  public function generate(){
    $ret = 0;
    $arr = [];
    for ($i = 0; $i < LENGTH; $i++)
        $arr[]=0;
    for ($i = 0; $i < 64; $i++)
        $arr[$i % LENGTH] += ord($this->hash[$i]) % BASE;
    for ($i = 0; $i < LENGTH; $i++)
        $ret = $ret * BASE + $arr[$i];
    $this->hash = Random::sha256_hash($this->hash . $this->getState() . ret);
    return $ret;
  }
}
$r = new Random("sss");
echo $r->generate();
