//
// read_adc.js
//
// uses the gertboardlib DLL to read the value of a channel of the gertboard ADC 
//
// run using node 
// node read_adc.js  
//
// var ref = require('ref');   // required if passing pointers to lib functions
var ffi = require("ffi");


var gertboardlib = ffi.Library('libgertboardlib', {
  "atod": [ 'int', [ 'int' ] ]
});


var res = gertboardlib.atod();

console.log('Gertboard ADC is currently measuring: ' + res);
