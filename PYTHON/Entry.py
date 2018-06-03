from Cryptor import Cryptor

class EntryState:
    UNDECRYPTED, DECRYPTED, ENCRYPTED, UNENCRYPTED = range(0,4)

class Entry(object):
    __KEY = "entry_key1234"
    __c = Cryptor()
    userKey = ""
    def __init__(self,num,d,t):
        self.__number = num
        self.__date=d
        self.__text=t
        self.__state=EntryState.UNENCRYPTED
    def __init__(self,input):
        self.__state=EntryState.UNDECRYPTED
        self.__hash=input
    def __encrypt(self,key = Entry.userKey):
        self.__hash = c.encrypt(self.__number + " " + self.__date.toString() + " " + Entry.__c.encrypt(self.__text, Entry.__KEY), key)
        self.__state = EntryState.ENCRYPTED
    def __decrypt(self):
        tokens = Entry.__c.decrypt(self.__hash,Entry.userKey).Split()
        if len(tokens) != 3:
            raise Exception("Decryption cannot be done")
        number = int(tokens[0])
        date = Date(tokens[1])
        text = Entry.__c.decrypt(tokens[2], Entry.__KEY)
    def recrypt(self,newKey):
        if state == EntryState.UNDECRYPTED:
            self.__decrypt()
        self.__encrypt(newKey)
    def getHash(self):
        if state == EntryState.UNENCRYPTED:
            self.__encrypt()
        return self.__hash
    def getText(self):
        if state == EntryState.UNDECRYPTED:
            self.__decrypt()
        return self.__text
    def getDate(self):
        if state == EntryState.UNDECRYPTED:
            self.__decrypt()
        return self.__date.toString()
    def getNumber(self):
        if state == EntryState.UNDECRYPTED:
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
