<?php
include_once 'cryptor.php';
include_once 'date.php';
define("KEY", "entry_key1234");

abstract class EntryState {
    const UNDECRYPTED = 0;
    const DECRYPTED = 1;
    const ENCRYPTED = 2;
    const UNENCRYPTED = 3;
}

class Entry {
    private static $userKey = "";
    public static $c;

    public static function setUserKey($input) {
        Entry::$userKey = $input;
    }

    private $number;
    private $date;
    private $text = "";
    private $hash = "";
    private $state;

    public function __construct($num, $d = "", $t = "") {
        if ($d != "") {
            $this->number = $num;
            $this->date = $d;
            $this->text = $t;
            $this->state = EntryState::UNENCRYPTED;
        } else {
            $this->state = EntryState::UNDECRYPTED;
            $this->hash = $num;
        }
    }

    private function encrypt($key = -1) {
        if ($key = -1) $key = Entry::$userKey;
        $this->hash = Entry::$c->encrypt(Entry::$c->encrypt($this->text, KEY) . " " . $this->date . " " . $this->number, $key);
        $this->state = EntryState::ENCRYPTED;
    }

    private function decrypt() {
        $tokens = explode(" ", Entry::$c->decrypt($this->hash, Entry::$userKey));
        if (count($tokens) != 3) throw new Exception("Decryption cannot be done");
        $this->text = Entry::$c->decrypt($tokens[0], KEY);
        $this->date = new Date($tokens[1]);
        $this->number = (int)($tokens[2]);
        $this->state = EntryState::DECRYPTED;
    }

    public function recrypt($newKey) {
        if ($this->state == EntryState::UNDECRYPTED) $this->decrypt();
        $this->encrypt($newKey);
    }

    public function getHash() {
        if ($this->state == EntryState::UNENCRYPTED) $this->encrypt();
        return $this->hash;
    }

    public function getText() {
        if ($this->state == EntryState::UNDECRYPTED) $this->decrypt();
        return $this->text;
    }

    public function getDate() {
        if ($this->state == EntryState::UNDECRYPTED) $this->decrypt();
        return (string)$this->date;
    }

    public function getNumber() {
        if ($this->state == EntryState::UNDECRYPTED) $this->decrypt();
        return $this->number;
    }

    public function setText($input) {
        $this->text = $input;
        $this->state = EntryState::UNENCRYPTED;
    }

    public function setDate($input) {
        $this->date = new Date(input);
        $this->state = EntryState::UNENCRYPTED;
    }

    public function setNumber($input) {
        $this->number = $input;
        $this->state = EntryState::UNDECRYPTED;
    }
}

Entry::$c = new Cryptor();