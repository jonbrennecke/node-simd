
(function ( mod ){
	if ( typeof module === "object" && typeof module.exports === "object" ) // CommonJS, Node
		module.exports = mod();
})(function(){

	"use strict"; // required for some harmony features

	// detect harmony support at a level that at least supports Proxies
	// this unfortunately excludes the otherwise wonderful npm module "es6-shim"
	// if ('object' != typeof Proxy)
	// {
	// 	throw 'Node.js must be run with the "--harmony" flag';
	// }

	return require('./build/Release/simd');
});
