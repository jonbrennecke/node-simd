{
	"targets" : [
		{
			"target_name" : "simd",
			"sources" : ["simd.cpp"],
			"conditions" : [
				[ "OS == \"mac\"", {
					"xcode_settings": {
		                "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++","-msse4","-march=core-avx-i"],
		                "OTHER_LDFLAGS": ["-stdlib=libc++"],
		                "MACOSX_DEPLOYMENT_TARGET": "10.7"
		            }
				}]
			]
		}
	]
}