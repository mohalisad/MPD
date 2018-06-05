from hashlib import sha256 as libsha256

def sha256(strinp):
        return libsha256(strinp.encode()).hexdigest()
class MyRandom(object):
        BASE = 10
        LENGTH = 8
        MAX_STATE = 100000
        def __init__(self,seed):
                self.__state=0
                self.__hash=sha256(seed)
        def __getState(self):
                self.__state=(self.__state+1) % MyRandom.MAX_STATE
                return self.__state
        def generate(self):
                ret = 0
                arr=[0]*MyRandom.LENGTH
                for i in range(0,64):
                        arr[i % MyRandom.LENGTH] += ord(self.__hash[i]) % MyRandom.BASE
                for i in range(0,MyRandom.LENGTH):
                        ret = ret * MyRandom.BASE + arr[i]
                self.__hash = sha256(self.__hash + str(self.__getState()) + str(ret))
                return ret
