const BASE = 10;
const LENGTH = 8;
const MAX_STATE = 100000;

function sha256(pwd){
  var crypto = require('crypto');
  var hash = crypto.createHash('sha256').update(pwd).digest('hex');
  return hash;
}
class Random{
  constructor(input) {
    this.state = 0;
    this.hash = sha256(input);
  }
  getState(){
    this.state = (this.state + 1) % MAX_STATE;
    return this.state;
  }
  generate(){
    var ret = 0;
    var arr= new Array(LENGTH).fill(0);
    for (var i = 0; i < 64; i++){
        arr[i % LENGTH] += this.hash.charCodeAt(i) % BASE;
    }
    for (var i = 0; i < LENGTH; i++){
        ret = ret * BASE + arr[i];
    }
    this.hash = sha256(this.hash + this.getState() + ret);
    return ret;
  }
}
module.exports = {
  Random : Random
}
