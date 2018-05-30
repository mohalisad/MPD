/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mpd;

import java.util.Arrays;

/**
 *
 * @author mohalisad
 */
public class Date {
    public static long getLocalTime(double timezone)
    {
        long now=System.currentTimeMillis() / 1000L;
        now += (long)(timezone * 3600);
        return now;
    }
    public static String now()
    {
        Date d=new Date();
        return d + " " + clock();
    }
    public static String clock()
    {
        long now = getLocalTime(new Date().month < 7 ? 4.5 : 3.5);
        long second, minute, hour;
        second = now % 60;
        minute = (now / 60) % 60;
        hour = (now / 3600) % 24;
        return hour + ":" + minute + ":" + second;
    }

    private int year;
    private int month;
    private int day;
    private int dayOfWeek;
    @Override
    protected  Date clone()
    {
        Date d = new Date();
        d.dayOfWeek = dayOfWeek;
        d.day = day;
        d.month = month;
        d.year = year;
        return d;
    }
    private void calcDayOfWeek()
    {
        int monthDays = (month - 1) * 31 - (month < 8 ? 0 : month - 7);
        dayOfWeek = (year + year / 4 + day + monthDays) % 7;
    }
    private void setToNow(double timezone)
    {
        long now = getLocalTime(timezone);
        int dif = 0;
        now = now / 3600;
        now = now / 24;
        dif = (int)(now % (365 * 4 + 1));
        year = (int)(now / (365 * 4 + 1)) * 4 + 1348;
        day = 11;
        month = 10;
        for (int i = 0; i < dif; i++)
        {
            goNext();
        }
        dayOfWeek = (int)((5 + now) % 7);
    }
    private boolean isItKabise()
    {
        int[] arr = { 1, 5, 9, 13, 17, 22, 26, 30 };
        return Arrays.asList(arr).contains(year%33);
    }
    public Date()
    {
        setToNow(3.5);
        if (month < 7) setToNow(4.5);
    }
    public Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
        calcDayOfWeek();
    }
    public Date(String input) throws Exception
    {
        String[] tokens = input.split("/");
        if (tokens.length != 3) throw new Exception("Date String is invalid");
        year = Integer.parseInt(tokens[0]);
        month = Integer.parseInt(tokens[1]);
        day = Integer.parseInt(tokens[2]);
        calcDayOfWeek();
    }
    public void goNext()
    {
        day++;
        if (month < 7)
        {
            if (day > 31)
            {
                day = 1;
                month++;
            }
        }
        else
        {
            if (month != 12 || isItKabise())
            {
                if (day > 30)
                {
                    day = 1;
                    month++;
                }
            }
            else
            {
                if (day > 29)
                {
                    day = 1;
                    month++;
                }
            }
        }
        if (month > 12)
        {
            month = 1;
            year++;
        }
        dayOfWeek = (dayOfWeek + 1) % 7;
    }
    public void goPrev()
    {
        day--;
        if (day == 0)
        {
            day = 31;
            month--;
            if (month == 0)
            {
                month = 12;
                year--;
            }
            if (month > 6)
            {
                day--;
            }
            if (month == 12 && !isItKabise())
            {
                day--;
            }
            dayOfWeek = (dayOfWeek - 1) % 7;
        }
    }
    public Date prev()
    {
        Date d = clone();
        d.goPrev();
        return d;
    }
    public Date next()
    {
        Date d = clone();
        d.goNext();
        return d;
    }
    @Override
    public String toString()
    {
        return year + "/" + month + "/" + day;
    }
    public String getDayOfWeek() throws Exception
    {
        switch (dayOfWeek)
        {
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
