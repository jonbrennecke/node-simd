// forward declaration of Proxy traps
// function proxify ( obj ) {

// 	return Proxy.createFunction(
// 		{
// 			has : function ( name ) { // name in proxy
// 				return name in obj;
// 			},
// 			hasOwn : function ( name ) { // ({}).hasOwnProperty.call(proxy, name)
// 				return ({}).hasOwnProperty.call(obj, name);
// 			},
// 			get : function ( reciever, name ) { // reciever.name
// 				console.log(name)
// 				return obj[name];
// 			},
// 			set : function ( reciever, name, value ) { // reciever.name = value
// 				obj[name] = val; return true; 
// 			},
// 			enumerate : function () { // for (name in proxy) (return array of enumerable own and inherited properties)
// 				var result = [];
// 				for (var name in obj) { result.push(name); };
// 				return result;
// 			},
// 			keys : function () { // Object.keys(proxy)  (return array of enumerable own properties only)
// 				return Object.keys(obj);
// 			},
// 			fix : function ( name ) { // Object.{freeze|seal|preventExtensions}(proxy)
// 				if (Object.isFrozen(obj)) {
// 					var result = {};
// 					Object.getOwnPropertyNames(obj).forEach(function(name) {
// 						result[name] = Object.getOwnPropertyDescriptor(obj, name);
// 					});
// 					return result;
// 				}
// 				// As long as obj is not frozen, the proxy won't allow itself to be fixed
// 				return undefined; // will cause a TypeError to be thrown
// 			},
// 			defineProperty : function ( name, desc ) {
// 				Object.defineProperty(obj, name, desc);
// 			},
// 			getOwnPropertyNames : function () {
// 				return Object.getOwnPropertyNames(obj);
// 			},
// 			getPropertyNames : function () {
// 				return Object.getPropertyNames(obj);
// 			},
// 			getOwnPropertyDescriptor : function () { // Object.getOwnPropertyDescriptor(proxy, name)
// 				var desc = Object.getOwnPropertyDescriptor(obj, name);
// 				// a trapping proxy's properties must always be configurable
// 				if (desc !== undefined) { desc.configurable = true; }
// 				return desc;
// 			},
// 			getPropertyDescriptor : function () { // Object.getPropertyDescriptor(proxy, name)   (not in ES5)
// 				var desc = Object.getPropertyDescriptor(obj, name); // not in ES5
// 				// a trapping proxy's properties must always be configurable
// 				if (desc !== undefined) { desc.configurable = true; }
// 				return desc;
// 			},
// 			delete : function () {
// 				return delete obj[name];
// 			}
// 		},
// 		function () { // call trap

// 		},
// 		function ( args ) { // construct trap
// 			return 
// 		}
// 	);
// }

// module.exports = {
// 	'Float64SIMDArray' : proxify(Native.Float64SIMDArray),
// 	// 'Int32SIMDArray' : proxify(Native.Int32SIMDArray),
// };
