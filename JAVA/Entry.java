/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mpd;


enum EntryState { UNDECRYPTED, DECRYPTED, ENCRYPTED, UNENCRYPTED };

public class Entry {
    private final static String KEY = "entry_key1234";
    private final static Cryptor c = new Cryptor();
    private static String userKey = "";
    public static void setUserKey(String input)
    {
        userKey = input;
    }
    private int number;
    private Date date;
    private String text = "";
    private String hash = "";
    private EntryState state;
    public Entry(int num, Date d,String t){
        number = num;
        date=d;
        text=t;
        state=EntryState.UNENCRYPTED;
    }
    public Entry(String input){
        state=EntryState.UNDECRYPTED;
        hash=input;
    }
    private void encrypt(String key)
    {
        hash = c.encrypt(c.encrypt(text, KEY) + " " + date + " " + number, key);
        state = EntryState.ENCRYPTED;
    }
    private void encrypt()
    {
        encrypt(userKey);
    }
    private void decrypt() throws Exception
    {
        String[] tokens = c.decrypt(hash, userKey).split(" ");
        if (tokens.length != 3) throw new Exception("Decryption cannot be done");
        text = c.decrypt(tokens[0], KEY);
        date = new Date(tokens[1]);
        number = Integer.parseInt(tokens[2]);
        state= EntryState.DECRYPTED;
    }
    public void recrypt(String newKey) throws Exception
    {
        if (state == EntryState.UNDECRYPTED) decrypt();
        encrypt(newKey);
    }
    public String getHash()
    {
        if (state == EntryState.UNENCRYPTED) encrypt();
        return hash;
    }
    public String getText() throws Exception
    {
        if (state == EntryState.UNDECRYPTED) decrypt();
        return text;
    }
    public String getDate() throws Exception
    {
        if (state == EntryState.UNDECRYPTED) decrypt();
        return date.toString();
    }
    public int getNumber() throws Exception
    {
        if (state == EntryState.UNDECRYPTED) decrypt();
        return number;
    }
    public void setText(String input)
    {
        text = input;
        state = EntryState.UNENCRYPTED;
    }
    public void setDate(String input) throws Exception
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
