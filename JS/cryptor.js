var random = require("./random.js");

const _KEY = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?";
const _KEY_LENGTH = 64;
const SALT_LENGTH = 16;
const MULTIPLY = 1.2;
const DISORDER_RATE = 6;

function makeDisorderMoves(length,key){
    var loopCount = DISORDER_RATE * length * 2;
    var arr = new Array(loopCount);
    var ran=new random.Random(key);
    for (var i = 0; i < loopCount; i++){
        arr[i] = ran.generate() % length;
    }
    return arr;
}
function makeDisorderArray(length,disorderMoves){
    var loopCount = DISORDER_RATE * length * 2;
    var ret = [];
    for (var i =0;i<length;i++)
      ret.push(i);
    for (var i =0;i<loopCount;i+=2)
        [ret[disorderMoves[i]],ret[disorderMoves[i + 1]]] = [ret[disorderMoves[i + 1]],ret[disorderMoves[i]]]
    return ret;
}
function bitSet(input,position,toWhat){
    var pow2 = 1;
    for (var i = 0; i < position; i++) pow2 *= 2;
    if (((input & pow2)!=0) == toWhat) return input;
    if (toWhat){
        return input | pow2;
    }
    else{
        return input & (63 - pow2);
    }
}

function bitGet(input,position){
    var pow2 = 1;
    for (var i = 0; i < position; i++) pow2 *= 2;
    return (input & pow2)!=0;
}

function getPossition(input){
    return _KEY.indexOf(input);
}

class Cryptor{
  constructor() {
    this.r = new random.Random("salam");
  }
  randomString(length){
      var retu="";
      for (var i = 0; i < length; i++){
          retu += _KEY[this.r.generate() % _KEY_LENGTH];
      }
      return retu;
  }
  encrypt(_input,key)
  {
      var retu="", salt ,disorderArray,disorderMoves,chars,input,length,pointer;
      input = _input;
      pointer = 0;
      length = parseInt(MULTIPLY * (input.length+1) * 8);
      length = length + 6 - length % 6;
      salt = this.randomString(SALT_LENGTH);
      disorderMoves = makeDisorderMoves(length, key + salt);
      disorderArray = makeDisorderArray(length, disorderMoves);
      chars = new Array(parseInt(length / 6)).fill(0);
      for (var i = 0; i < input.length; i++){
          for (var j = 1; j < 256; j = j * 2){
              chars[parseInt(disorderArray[pointer] / 6)] = bitSet(chars[parseInt(disorderArray[pointer] / 6)], disorderArray[pointer] % 6, (input.charCodeAt(i) & j)!=0);
              pointer++;
          }
      }
      for (var j = 1; j < 256; j = j * 2){
          chars[parseInt(disorderArray[pointer] / 6)] = bitSet(chars[parseInt(disorderArray[pointer] / 6)], disorderArray[pointer] % 6, false);
          pointer++;
      }
      for (; pointer < length; pointer++){
          chars[parseInt(disorderArray[pointer] / 6)] = bitSet(chars[parseInt(disorderArray[pointer] / 6)], disorderArray[pointer] % 6, (this.r.generate() % 2)!=0);
      }
      for (var i = 0; i < length / 6; i++){
          retu += _KEY[chars[i]];
      }

      return retu + salt;
  }
  decrypt(input,key){
      var disorderArray,disorderMoves,length,salt;
      salt = input.substr(input.length - SALT_LENGTH, SALT_LENGTH);
      input = input.substr(0, input.length - SALT_LENGTH);
      length = input.length * 6;
      disorderMoves = makeDisorderMoves(length, key + salt);
      disorderArray = makeDisorderArray(length, disorderMoves);
      var chars = [];
      for (var i = 0; i < length / 6; i++){
          chars.push(getPossition(input[i]));
      }
      var pointer = 0;
      var retchars = "";
      var temp = 0;
      while (pointer < length){
          temp = 0;
          for (var j = 0; j < 8; j++){
              temp = bitSet(temp, j, bitGet(chars[parseInt(disorderArray[pointer] / 6)], disorderArray[pointer] % 6));
              pointer++;
              if (pointer == length) break;
          }
          if (temp == 0) break;
          retchars+= String.fromCharCode(temp);
      }
      return retchars;
  }
}
var c = new Cryptor();
var e = c.encrypt("asdrwepiqd","123");
console.log(e);
console.log(c.decrypt(e,"123"));
