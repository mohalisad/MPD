var mydate = require("./mydate");
var cryptor = require("./cryptor");

const KEY = "entry_key1234";

const EntryState = {UNDECRYPTED: 0, DECRYPTED: 1, ENCRYPTED: 2, UNENCRYPTED: 3};

var c = new cryptor.Cryptor();

var userKey = "";

function setUserKey(input) {
    userKey = input;
}

class Entry {


    constructor(num, d = "", t = "") {
        if (d != "") {
            this.number = num;
            this.date = d;
            this.text = t;
            this.state = EntryState.UNENCRYPTED;
        } else {
            this.state = EntryState.UNDECRYPTED;
            this.hash = num;
        }
    }

    encrypt(key) {
        this.hash = c.encrypt(c.encrypt(this.text, KEY) + " " + this.date + " " + this.number, key);
        this.state = EntryState.ENCRYPTED;
    }

    encrypt() {
        this.encrypt(userKey);
    }

    decrypt() {
        var tokens = c.decrypt(this.hash, userKey).split(' ');
        if (tokens.length != 3) throw "Decryption cannot be done";
        this.text = c.decrypt(tokens[0], KEY);
        this.date = new mydate.MyDate(tokens[1]);
        this.number = parseInt(tokens[2]);
        this.state = EntryState.DECRYPTED;
    }

    recrypt(newKey) {
        if (this.state == EntryState.UNDECRYPTED) this.decrypt();
        this.encrypt(newKey);
    }

    getHash() {
        if (this.state == EntryState.UNENCRYPTED) this.encrypt();
        return this.hash;
    }

    getText() {
        if (this.state == EntryState.UNDECRYPTED) this.decrypt();
        return this.text;
    }

    getDate() {
        if (this.state == EntryState.UNDECRYPTED) this.decrypt();
        return this.date.toString();
    }

    getNumber() {
        if (this.state == EntryState.UNDECRYPTED) this.decrypt();
        return this.number;
    }

    setText(input) {
        this.text = input;
        this.state = EntryState.UNENCRYPTED;
    }

    setDate(input) {
        this.date = new MyDate(input);
        this.state = EntryState.UNENCRYPTED;
    }

    setNumber(input) {
        this.number = input;
        this.state = EntryState.UNDECRYPTED;
    }
}

module.exports = {
    Entry: Entry,
    setUserKey: setUserKey
};