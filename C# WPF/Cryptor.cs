using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MPD
{
    class Cryptor
    {
        private const string _KEY = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?";
        private const int _KEY_LENGTH = 64;
        private const int SALT_LENGTH = 16;
        private const double MULTIPLY = 1.2;
        private const int DISORDER_RATE = 6;
        MyRandom r=new MyRandom (Date.now());
        private string randomString(int length)
        {
            string retu="";
            for (int i = 0; i < length; i++)
            {
                retu += _KEY[r.generate() % _KEY_LENGTH].ToString();
            }
            return retu;
        }
        private int[] makeDisorderMoves(int length, string key)
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
        private int[] makeDisorderArray(int length, int[] disorderMoves)
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
        private int bitSet(int input, int position, bool toWhat)
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
        private bool bitGet(int input, int position)
        {
            int pow2 = 1;
            for (int i = 0; i < position; i++) pow2 *= 2;
            return (input & pow2)!=0;
        }
        private int getPossition(char input)
        {
            return _KEY.IndexOf(input);
        }
        public string encrypt(string _input, string key)
        {
            string retu="", salt;
            int[] disorderArray,disorderMoves,chars;
            byte[] input = Encoding.UTF8.GetBytes(_input);
            int pointer = 0, length = (int)(MULTIPLY * (input.Length+1) * 8);
            length = length + 6 - length % 6;
            salt = randomString(SALT_LENGTH);
            disorderMoves = makeDisorderMoves(length, key + salt);
            disorderArray = makeDisorderArray(length, disorderMoves);
            chars = new int[length / 6];
            for (int i = 0; i < length / 6; i++)
            {
                chars[i] = 0;
            }
            for (int i = 0; i < input.Length; i++)
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
                retu += _KEY[chars[i]];
            }
            return retu + salt;
        }
        public string decrypt(string input, string key)
        {
            int[] disorderArray,disorderMoves,chars;
            List<byte> retchars = new List<byte>();
            byte temp;
            int length;
            string salt = input.Substring(input.Length - SALT_LENGTH, SALT_LENGTH);
            input = input.Substring(0, input.Length - SALT_LENGTH);
            length = input.Length * 6;
            disorderMoves = makeDisorderMoves(length, key + salt);
            disorderArray = makeDisorderArray(length, disorderMoves);
            chars = new int[length / 6];
            for (int i = 0; i < length / 6; i++)
            {
                chars[i] = getPossition(input[i]);
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
                retchars.Add(temp);
            }
            return Encoding.UTF8.GetString(retchars.ToArray());
        }
    }
}
