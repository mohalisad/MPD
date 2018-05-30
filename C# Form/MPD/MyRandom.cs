using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace MPD
{
    class MyRandom
    {
        #region STATIC
        private const int BASE = 10;
        private const int LENGTH = 8;
        private const int MAX_STATE = 100000;
        public static string sha256_hash(string value)
        {
            StringBuilder Sb = new StringBuilder();
            using (SHA256 hash = SHA256Managed.Create())
            {
                Encoding enc = Encoding.UTF8;
                Byte[] result = hash.ComputeHash(enc.GetBytes(value));

                foreach (Byte b in result)
                    Sb.Append(b.ToString("x2"));
            }
            return Sb.ToString();
        }
        #endregion
        private int state;
        private string hash;
        private int getState()
        {
            state = (state + 1) % MAX_STATE;
            return state;
        }
        public MyRandom(string input){
            state=0;
            hash= sha256_hash(input);
        }
        public int generate()
        {
            int ret = 0;
            int[] arr=new int[LENGTH];
            for (int i = 0; i < LENGTH; i++)
            {
                arr[i] = 0;
            }
            for (int i = 0; i < 64; i++)
            {
                arr[i % LENGTH] += hash[i] % BASE;
            }
            for (int i = 0; i < LENGTH; i++)
            {
                ret = ret * BASE + arr[i];
            }
            hash = sha256_hash(hash + getState().ToString() + ret.ToString());
            return ret;
        }
    }
}
