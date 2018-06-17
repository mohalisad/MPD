/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mpd;

import java.security.MessageDigest;

/**
 * @author mohalisad
 */
public class MyRandom {
    private final static int BASE = 10;
    private final static int LENGTH = 8;
    private final static int MAX_STATE = 100000;

    public static String sha256_hash(String base) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(base.getBytes("UTF-8"));
            StringBuffer hexString = new StringBuffer();
            for (int i = 0; i < hash.length; i++) {
                String hex = Integer.toHexString(0xff & hash[i]);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } catch (Exception ex) {
            throw new RuntimeException(ex);
        }
    }

    private int state;
    private String hash;

    private int getState() {
        state = (state + 1) % MAX_STATE;
        return state;
    }

    public MyRandom(String input) {
        state = 0;
        hash = sha256_hash(input);
    }

    public int generate() {
        int ret = 0;
        int[] arr = new int[LENGTH];
        for (int i = 0; i < LENGTH; i++) {
            arr[i] = 0;
        }
        for (int i = 0; i < 64; i++) {
            arr[i % LENGTH] += hash.charAt(i) % BASE;
        }
        for (int i = 0; i < LENGTH; i++) {
            ret = ret * BASE + arr[i];
        }
        hash = sha256_hash((hash + getState()) + ret);
        return ret;
    }
}
