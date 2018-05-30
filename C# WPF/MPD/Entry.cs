using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MPD
{
    enum EntryState { UNDECRYPTED, DECRYPTED, ENCRYPTED, UNENCRYPTED };

    class Entry
    {
        #region STATIC
        private const string KEY = "entry_key1234";
        private static Cryptor c = new Cryptor();
        private static string userKey = "";
        public static void setUserKey(string input)
        {
            userKey = input;
        }
        #endregion
        private int number;
        private Date date;
        private string text = "";
        private string hash = "";
        private EntryState state;
        public Entry(int num, Date d,string t){
            number = num;
            date=d;
            text=t;
            state=EntryState.UNENCRYPTED;
        }
        public Entry(string input){
            state=EntryState.UNDECRYPTED;
            hash=input;
        }
        private void encrypt(string key)
        {
            hash = c.encrypt(number + " " + date + " " + c.encrypt(text, KEY), key);
            state = EntryState.ENCRYPTED;
        }
        private void encrypt()
        {
            encrypt(userKey);
        }
        private void decrypt()
        {
            string[] tokens = c.decrypt(hash, userKey).Split(' ');
            if (tokens.Length != 3) throw new Exception("Decryption cannot be done");
            number = Convert.ToInt32(tokens[0]);
            date = new Date(tokens[1]);
            text = c.decrypt(tokens[2], KEY);
        }
        public void recrypt(string newKey)
        {
            if (state == EntryState.UNDECRYPTED) decrypt();
            encrypt(newKey);
        }
        public string getHash()
        {
            if (state == EntryState.UNENCRYPTED) encrypt();
            return hash;
        }
        public string getText()
        {
            if (state == EntryState.UNDECRYPTED) decrypt();
            return text;
        }
        public string getDate()
        {
            if (state == EntryState.UNDECRYPTED) decrypt();
            return date.ToString();
        }
        public int getNumber()
        {
            if (state == EntryState.UNDECRYPTED) decrypt();
            return number;
        }
        public void setText(string input)
        {
            text = input;
            state = EntryState.UNENCRYPTED;
        }
        public void setDate(string input)
        {
            date = new Date(input);
            state = EntryState.UNENCRYPTED;
        }
        public void setNumber(int input)
        {
            number = input;
            state = EntryState.UNDECRYPTED;
        }
    }
}