<?php

class Date {
    public static function getLocalTime($timezone) {
        $now = time();
        $now += $timezone * 3600;
        return $now;
    }

    public static function now() {
        $d = new Date();
        return $d . " " . Date::clock();
    }

    public static function clock() {
        $now = Date::getLocalTime((new Date())->month < 7 ? 4.5 : 3.5);
        $second = $now % 60;
        $minute = (int)($now / 60) % 60;
        $hour = (int)($now / 3600) % 24;
        return $hour . ":" . $minute . ":" . $second;
    }

    private $year;
    private $month;
    private $day;
    private $dayOfWeek;

    private function calcDayOfWeek() {
        $monthDays = ($this->month - 1) * 31 - ($this->month < 8 ? 0 : $this->month - 7);
        $this->dayOfWeek = ($this->year . $this->year / 4 . $this->day . $monthDays) % 7;
    }

    private function setToNow($timezone) {
        $now = Date::getLocalTime($timezone);
        $now = $now / 3600;
        $now = $now / 24;
        $dif = (int)($now % (365 * 4 + 1));
        $this->year = (int)($now / (365 * 4 + 1)) * 4 + 1348;
        $this->day = 11;
        $this->month = 10;
        for ($i = 0; $i < $dif; $i++) {
            $this->goNext();
        }
        $this->dayOfWeek = (int)((5 + $now) % 7);
    }

    private function isItKabise() {
        $arr = [1, 5, 9, 13, 17, 22, 26, 30];
        return in_array($this->year % 33, $arr);
    }

    public function __construct($y = "", $m = "", $d = "") {
        if ($y == "") {
            $this->setToNow(3.5);
            if ($this->month < 7) $this->setToNow(4.5);
        } else if ($m == "") {
            $tokens = explode("/", $y);
            if (count($tokens) != 3) throw new Exception("Date string is invalid");
            $this->year = (int)($tokens[0]);
            $this->month = (int)($tokens[1]);
            $this->day = (int)($tokens[2]);
            $this->calcDayOfWeek();
        } else {
            $this->year = $y;
            $this->month = $m;
            $this->day = $d;
            $this->calcDayOfWeek();
        }
    }

    public function goNext() {
        $this->day++;
        if ($this->month < 7) {
            if ($this->day > 31) {
                $this->day = 1;
                $this->month++;
            }
        } else {
            if ($this->month != 12 || $this->isItKabise()) {
                if ($this->day > 30) {
                    $this->day = 1;
                    $this->month++;
                }
            } else {
                if ($this->day > 29) {
                    $this->day = 1;
                    $this->month++;
                }
            }
        }
        if ($this->month > 12) {
            $this->month = 1;
            $this->year++;
        }
        $this->dayOfWeek = ($this->dayOfWeek + 1) % 7;
    }

    public function goPrev() {
        $this->day--;
        if ($this->day == 0) {
            $this->day = 31;
            $this->month--;
            if ($this->month == 0) {
                $this->month = 12;
                $this->year--;
            }
            if ($this->month > 6) {
                $this->day--;
            }
            if ($this->month == 12 && !$this->isItKabise()) {
                $this->day--;
            }
            $this->dayOfWeek = ($this->dayOfWeek - 1) % 7;
        }
    }

    public function prev() {
        $d = clone $this;
        $d->goPrev();
        return $d;
    }

    public function next() {
        $d = clone $this;
        $d->goNext();
        return $d;
    }

    public function __toString() {
        return $this->year . "/" . $this->month . "/" . $this->day;
    }

    public function getDayOfWeek() {
        switch ($this->dayOfWeek) {
            case 0:
                return "شنبه";
            case 1:
                return "یک شنبه";
            case 2:
                return "دوشنبه";
            case 3:
                return "سه شنبه";
            case 4:
                return "چهارشنبه";
            case 5:
                return "پنج شنبه";
            case 6:
                return "جمعه";
        }
        throw new Exception("DayOfWeek is wrong");
    }
}
