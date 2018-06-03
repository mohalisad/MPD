from Cryptor import Cryptor
from Date import Date

class EntryState:
    UNDECRYPTED, DECRYPTED, ENCRYPTED, UNENCRYPTED = range(0,4)

class Entry(object):
    __KEY = "entry_key1234"
    __c = Cryptor()
    userKey = ""
    def __init__(self,num,d="",t=""):
        if d=="":
            self.__state=EntryState.UNDECRYPTED
            self.__hash=num
        else:
            self.__number = int(num)
            self.__date=d
            self.__text=t
            self.__state=EntryState.UNENCRYPTED
    def __encrypt(self,key):
        self.__hash = c.encrypt(self.__number + " " + self.__date.toString() + " " + Entry.__c.encrypt(self.__text, Entry.__KEY), key)
        self.__state = EntryState.ENCRYPTED
    def __encrypt(self):
        selfEntry.__encrypt(userKey)
    def __decrypt(self):
        tokens = Entry.__c.decrypt(self.__hash,Entry.userKey).split()
        if len(tokens) != 3:
            raise Exception("Decryption cannot be done")
        self.__number = int(tokens[0])
        self.__date = Date(tokens[1])
        self.__text = Entry.__c.decrypt(tokens[2], Entry.__KEY)
        self.__state = EntryState.DECRYPTED;
    def recrypt(self,newKey):
        if self.__state == EntryState.UNDECRYPTED:
            self.__decrypt()
        self.__encrypt(newKey)
    def getHash(self):
        if self.__state == EntryState.UNENCRYPTED:
            self.__encrypt()
        return self.__hash
    def getText(self):
        if self.__state == EntryState.UNDECRYPTED:
            self.__decrypt()
        return self.__text
    def getDate(self):
        if self.__state == EntryState.UNDECRYPTED:
            self.__decrypt()
        return self.__date.toString()
    def getNumber(self):
        if self.__state == EntryState.UNDECRYPTED:
            self.__decrypt()
        return self.__number
    def setText(self,input):
        self.__text = input
        self.__state = EntryState.UNENCRYPTED
    def setDate(self,input):
        self.__date = Date(input)
        self.__state = EntryState.UNENCRYPTED
    def setNumber(self,input):
        self.__number = input
        self.__state = EntryState.UNDECRYPTED
