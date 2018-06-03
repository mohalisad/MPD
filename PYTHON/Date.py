import time

class Date(object):
    def __getLocalTime(timezone):
        now = int(time.time())
        now += int(timezone * 3600)
        return now
    def now():
        d = Date()
        return d.toString() + " " + Date.clock()
    def clock():
        now = Date.__getLocalTime(4.5 if Date().__month < 7 else 3.5)
        second = now % 60
        minute = int(now / 60) % 60
        hour = int(now / 3600) % 24
        return str(hour) + ":" + str(minute) + ":" + str(second)
    def __init__(self,y=-1,m=-1,d=-1):
        if d==-1:
            if y==-1:
                self.__setToNow(3.5)
                if self.__month < 7:
                    self.__setToNow(4.5)
            else:
                tokens = y.split('/')
                if len(tokens) != 3:
                    raise Exception("Date string is invalid")
                self.__year = int(tokens[0])
                self.__month = int(tokens[1])
                self.__day = int(tokens[2])
                self.__calcDayOfWeek()
        else:
            self.__year = y
            self.__month = m
            self.__day = d
            self.__calcDayOfWeek()
    def __clone(self):
        d = Date()
        d.__dayOfWeek = self.__dayOfWeek
        d.__day = self.__day
        d.__month = self.__month
        d.__year = self.__year
        return d
    def __calcDayOfWeek(self):
        monthDays = (self.__month - 1) * 31 - (0 if self.__month < 8 else self.__month - 7)
        self.__dayOfWeek = (self.__year + int(self.__year / 4) + self.__day + monthDays) % 7
    def __setToNow(self,timezone):
        now = Date.__getLocalTime(timezone)
        now = now / 3600
        now = now / 24
        dif = int(now % (365 * 4 + 1))
        self.__year = int(now / (365 * 4 + 1)) * 4 + 1348
        self.__day = 11
        self.__month = 10
        self.__dayOfWeek = 0
        for i in range(0,dif):
            self.goNext()
        self.__dayOfWeek = (int)((5 + now) % 7)
    def __isItKabise(self):
        arr = [1, 5, 9, 13, 17, 22, 26, 30]
        return self.__year % 33 in arr
    def goPrev(self):
        self.__day -= 1
        if self.__day == 0:
            self.__day = 31
            self.__month -= 1
            if self.__month == 0:
                self.__month = 12
                self.__year -= 1
            if self.__month > 6:
                self.__day -= 1
            if self.__month == 12 and not self.__isItKabise():
                self.__day -= 1
            self.__dayOfWeek = (self.__dayOfWeek - 1) % 7
    def goNext(self):
        self.__day += 1
        if self.__month < 7:
            if self.__day > 31:
                self.__day = 1
                self.__month +=1
        else:
            if self.__month != 12 or self.__isItKabise():
                if self.__day > 30:
                    self.__day = 1
                    self.__month += 1
            else:
                if self.__day > 29:
                    self.__day = 1
                    self.__month += 1
        if self.__month > 12:
            self.__month = 1
            self.__year += 1
        self.__dayOfWeek = (self.__dayOfWeek + 1) % 7
    def prev(self):
        d = self.__clone()
        d.goPrev()
        return d
    def next(self):
        d = self.__clone()
        d.goNext()
        return d
    def toString(self):
        return str(self.__year) + "/" + str(self.__month) + "/" + str(self.__day)
    def getDayOfWeek(self):
        return ["شنبه","یک شنبه","دوشنبه","سه شنبه","چهارشنبه","پنج شنبه","جمعه"][self.__dayOfWeek]
