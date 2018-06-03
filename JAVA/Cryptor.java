/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mpd;

import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author mohalisad
 */
public class Cryptor {
    private final static String _KEY = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?";
    private final static int _KEY_LENGTH = 64;
    private final static int SALT_LENGTH = 16;
    private final static double MULTIPLY = 1.2;
    private final static int DISORDER_RATE = 6;
    private MyRandom r=new MyRandom (Date.now());
    private String randomString(int length)
    {
        String retu="";
        for (int i = 0; i < length; i++)
        {
            retu += _KEY.charAt(r.generate() % _KEY_LENGTH);
        }
        return retu;
    }
    private static int[] makeDisorderMoves(int length, String key)
    {
        int loopCount = DISORDER_RATE * length * 2;
        int[] arr = new int[loopCount];
        MyRandom ran=new MyRandom(key);
        for (int i = 0; i < loopCount; i++)
        {
            arr[i] = ran.generate() % length;
        }
        return arr;
    }
    private static int[] makeDisorderArray(int length, int[] disorderMoves)
    {
        int c;
        int loopCount = DISORDER_RATE * length * 2;
        int[] ret = new int[length];
        for (int i = 0; i < length; i++)
        {
            ret[i] = i;
        }
        for (int i = 0; i < loopCount; i += 2)
        {
            c = ret[disorderMoves[i]];
            ret[disorderMoves[i]] = ret[disorderMoves[i + 1]];
            ret[disorderMoves[i + 1]] = c;
        }
        return ret;
    }
    private static int bitSet(int input, int position, boolean toWhat)
    {
        int pow2 = 1;
        for (int i = 0; i < position; i++) pow2 *= 2;
        if (((input & pow2)!=0) == toWhat) return input;
        if (toWhat)
        {
            return input | pow2;
        }
        else
        {
            return input & (63 - pow2);
        }
    }
    private static boolean bitGet(int input, int position)
    {
        int pow2 = 1;
        for (int i = 0; i < position; i++) pow2 *= 2;
        return (input & pow2)!=0;
    }
    private static int getPossition(char input)
    {
        return _KEY.indexOf(input);
    }
    public String encrypt(String _input, String key)
    {
        String retu="", salt;
        int[] disorderArray,disorderMoves,chars;
        byte[] input = _input.getBytes(StandardCharsets.UTF_8);
        int pointer = 0, length = (int)(MULTIPLY * (input.length+1) * 8);
        length = length + 6 - length % 6;
        salt = randomString(SALT_LENGTH);
        disorderMoves = makeDisorderMoves(length, key + salt);
        disorderArray = makeDisorderArray(length, disorderMoves);
        chars = new int[length / 6];
        for (int i = 0; i < length / 6; i++)
        {
            chars[i] = 0;
        }
        for (int i = 0; i < input.length; i++)
        {
            for (int j = 1; j < 256; j = j * 2)
            {
                chars[disorderArray[pointer] / 6] = bitSet(chars[disorderArray[pointer] / 6], disorderArray[pointer] % 6, (input[i] & j)!=0);
                pointer++;
            }
        }
        for (int j = 1; j < 256; j = j * 2)
        {
            chars[disorderArray[pointer] / 6] = bitSet(chars[disorderArray[pointer] / 6], disorderArray[pointer] % 6, false);
            pointer++;
        }
        for (; pointer < length; pointer++)
        {
            chars[disorderArray[pointer] / 6] = bitSet(chars[disorderArray[pointer] / 6], disorderArray[pointer] % 6, (r.generate() % 2)!=0);
        }
        for (int i = 0; i < length / 6; i++)
        {
            retu += _KEY.charAt(chars[i]);
        }
        return retu + salt;
    }
    public String decrypt(String input, String key)
    {
        int[] disorderArray,disorderMoves,chars;
        ArrayList<Byte> retchars = new ArrayList<Byte>();
        byte[] _retchars;
        Byte temp;
        int length;
        String salt = input.substring(input.length() - SALT_LENGTH, input.length());
        input = input.substring(0, input.length() - SALT_LENGTH);
        length = input.length() * 6;
        disorderMoves = makeDisorderMoves(length, key + salt);
        disorderArray = makeDisorderArray(length, disorderMoves);
        chars = new int[length / 6];
        for (int i = 0; i < length / 6; i++)
        {
            chars[i] = getPossition(input.charAt(i));
        }
        int pointer = 0;
        while (pointer < length)
        {
            temp = 0;
            for (int j = 0; j < 8; j++)
            {
                temp = (byte)bitSet(temp, j, bitGet(chars[disorderArray[pointer] / 6], disorderArray[pointer] % 6));
                pointer++;
                if (pointer == length) break;
            }
            if (temp == 0) break;
            retchars.add(temp);
        }
        _retchars=new byte[retchars.size()];
        for(int i=0;i<retchars.size();i++){
            _retchars[i]=retchars.get(i).byteValue();
        }
        try {
            return new String(_retchars,"UTF-8");
        } catch (Exception ex) {
            return "";
        }
    }
}
