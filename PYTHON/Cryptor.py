from MyRandom import MyRandom

class Cryptor(object):
    _KEY="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?"
    _KEY_LENGTH = 64
    SALT_LENGTH = 16
    MULTIPLY = 1.2
    DISORDER_RATE = 6
    def __init__(self):
        self.r=MyRandom("a")
    def __randomString(self,length):
        retu=""
        for i in range(0,length):
            retu += Cryptor._KEY[self.r.generate() % Cryptor._KEY_LENGTH]
        return retu
    def __makeDisorderMoves(length,key):
        loopCount = Cryptor.DISORDER_RATE * length * 2
        arr = [0]*loopCount
        ran = MyRandom(key)
        for i in range(0,loopCount):
            arr[i] = ran.generate() % length
        return arr
    def __makeDisorderArray(length,disorderMoves):
        loopCount = Cryptor.DISORDER_RATE * length * 2
        ret = [i for i in range(0,length)]
        for i in range(0,loopCount,2):
            ret[disorderMoves[i]],ret[disorderMoves[i + 1]] = ret[disorderMoves[i + 1]],ret[disorderMoves[i]]
        return ret
    def __bitSet(input,position,toWhat):
        pow2 = 2**position
        if (((input & pow2)!=0) == toWhat):
            return input
        if (toWhat):
            return input | pow2
        else:
            return input & (63 - pow2)
    def __bitGet(input,position):
        pow2 = 2**position
        return (input & pow2)!=0
    def __getPossition(input):
        return Cryptor._KEY.find(input)
    def encrypt(self,input,key):
        input = input.encode("utf8")
        retu = ""
        pointer = 0
        length = int(Cryptor.MULTIPLY * (len(input)+1) * 8)
        length = length + 6 - length % 6
        salt = self.__randomString(Cryptor.SALT_LENGTH)
        disorderMoves = Cryptor.__makeDisorderMoves(length, key + salt)
        disorderArray = Cryptor.__makeDisorderArray(length, disorderMoves)
        chars = [0] * int(length / 6)
        for i in range(0,len(input)):
            for p in range(0,8):
                j = 2**p
                chars[int(disorderArray[pointer] / 6)] = Cryptor.__bitSet(chars[int(disorderArray[pointer] / 6)], disorderArray[pointer] % 6, (input[i] & j)!=0)
                pointer+=1
        for p in range(0,8):
            j = 2**p
            chars[int(disorderArray[pointer] / 6)] = Cryptor.__bitSet(chars[int(disorderArray[pointer] / 6)], disorderArray[pointer] % 6, 0)
            pointer+=1
        while pointer < length:
            chars[int(disorderArray[pointer] / 6)] = Cryptor.__bitSet(chars[int(disorderArray[pointer] / 6)], disorderArray[pointer] % 6, (self.r.generate() % 2)!=0)
            pointer+=1
        for i in range(0,int(length/6)):
            retu += Cryptor._KEY[chars[i]]
        return retu + salt
    def decrypt(self,input,key):
        retu = bytearray()
        salt = input[len(input) - Cryptor.SALT_LENGTH:]
        input = input[:len(input) - Cryptor.SALT_LENGTH]
        length = len(input) * 6
        disorderMoves = Cryptor.__makeDisorderMoves(length, key + salt)
        disorderArray = Cryptor.__makeDisorderArray(length, disorderMoves)
        chars = []
        for i in range(0,int(length/6)):
            chars.append(Cryptor.__getPossition(input[i]))
        pointer = 0
        while pointer < length:
            temp = 0
            for j in range (0,8):
                temp = Cryptor.__bitSet(temp, j, Cryptor.__bitGet(chars[int(disorderArray[pointer] / 6)], disorderArray[pointer] % 6))
                pointer+=1
                if pointer == length:
                    break
            if temp == 0:
                break
            retu.append(temp)
        return retu.decode('utf8')
