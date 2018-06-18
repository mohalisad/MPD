function getLocalTime(timezone) {
    var now = new Date().getTime() / 1000;
    now += (timezone * 3600);
    return parseInt(now);
}

class MyDate {
    static now() {
        var d = new MyDate();
        return d.toString() + " " + MyDate.clock();
    }

    static clock() {
        var now = getLocalTime(new MyDate().month < 7 ? 4.5 : 3.5);
        var second, minute, hour;
        second = now % 60;
        minute = (now / 60) % 60;
        hour = (now / 3600) % 24;
        return hour + ":" + minute + ":" + second;
    }

    clone() {
        var d = new Date();
        d.dayOfWeek = this.dayOfWeek;
        d.day = this.day;
        d.month = this.month;
        d.year = this.year;
        return d;
    }

    calcDayOfWeek() {
        var monthDays = (this.month - 1) * 31 - (this.month < 8 ? 0 : this.month - 7);
        this.dayOfWeek = (this.year + this.year / 4 + this.day + monthDays) % 7;
    }

    setToNow(timezone) {
        var now = getLocalTime(timezone);
        var dif = 0;
        now = now / 3600;
        now = parseInt(now / 24);
        dif = now % (365 * 4 + 1);
        this.year = parseInt(now / (365 * 4 + 1)) * 4 + 1348;
        this.day = 11;
        this.month = 10;
        for (var i = 0; i < dif; i++) {
            this.goNext();
        }
        this.dayOfWeek = (5 + now) % 7;
    }

    isItKabise() {
        var arr = [1, 5, 9, 13, 17, 22, 26, 30];
        return arr.indexOf(this.year % 33) == -1;
    }

    constructor(y = "", m = "", d = "") {
        if (y == "") {
            this.setToNow(3.5);
            if (this.month < 7) this.setToNow(4.5);
        } else if (m == "") {
            var tokens = y.split("/");
            if (tokens.length != 3) throw "Date string is invalid";
            this.year = parseInt(tokens[0]);
            this.month = parseInt(tokens[1]);
            this.day = parseInt(tokens[2]);
            this.calcDayOfWeek();
        } else {
            this.year = y;
            this.month = m;
            this.day = d;
            this.calcDayOfWeek();
        }
    }

    goNext() {
        this.day++;
        if (this.month < 7) {
            if (this.day > 31) {
                this.day = 1;
                this.month++;
            }
        } else {
            if (this.month != 12 || this.isItKabise()) {
                if (this.day > 30) {
                    this.day = 1;
                    this.month++;
                }
            } else {
                if (this.day > 29) {
                    this.day = 1;
                    this.month++;
                }
            }
        }
        if (this.month > 12) {
            this.month = 1;
            this.year++;
        }
        this.dayOfWeek = (this.dayOfWeek + 1) % 7;
    }

    goPrev() {
        this.day--;
        if (this.day == 0) {
            this.day = 31;
            this.month--;
            if (this.month == 0) {
                this.month = 12;
                this.year--;
            }
            if (this.month > 6) {
                this.day--;
            }
            if (this.month == 12 && !this.isItKabise()) {
                this.day--;
            }
            this.dayOfWeek = (this.dayOfWeek - 1) % 7;
        }
    }

    prev() {
        var d = this.clone();
        d.goPrev();
        return d;
    }

    next() {
        var d = this.clone();
        d.goNext();
        return d;
    }

    toString() {
        return this.year + "/" + this.month + "/" + this.day;
    }

    getDayOfWeek() {
        switch (this.dayOfWeek) {
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
        throw "DayOfWeek is wrong";
    }
}

module.exports = {
    MyDate: MyDate
};
