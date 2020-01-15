#define FLT_MAX	0x1.fffffep127f

int calculateArrayID(int maps, int height, int width, int batch, int map, int y, int x){
	return (((batch) * maps + map) * height + y) * width + x;
}

__kernel void feedforward(__global const float* inputs, __global float* outputs, const int3 inputDim, const int3 outputDim, const int2 poolDim, const int2 strideDim) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
	int outputMap=get_global_id(1);
 
	int outputMaps=outputDim.x;
	int outputHeight=outputDim.y;
	int outputWidth=outputDim.z;
 
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
 
	int poolHeight=poolDim.x;
	int poolWidth=poolDim.y;
	
	int strideHeight=strideDim.x;
	int strideWidth=strideDim.y;
 
	for(int outputY=0;outputY<outputHeight;outputY++){
		for(int outputX=0;outputX<outputWidth;outputX++){		
			float maxValue=-FLT_MAX;
			
			for(int yPool=0;yPool<poolHeight;yPool++){
				for(int xPool=0;xPool<poolWidth;xPool++){
					int idIn=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, outputMap, outputY*strideHeight+yPool, outputX*strideWidth+xPool);
					float value=inputs[idIn];
				
					maxValue=fmax(maxValue,value);				
				}
			}
			
			int idOut = calculateArrayID(outputMaps, outputHeight, outputWidth, batch, outputMap, outputY, outputX);
			outputs[idOut] = maxValue;
		}
	}
}

__kernel void errorComp(__global float* errorInput, __global const float* errorOutput, __global const float* inputs, __global const float* outputs, const int3 inputDim, const int3 outputDim, const int2 poolDim, const int2 strideDim) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
 
	int outputMaps=outputDim.x;
	int outputHeight=outputDim.y;
	int outputWidth=outputDim.z;
 
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
 
	int poolHeight=poolDim.x;
	int poolWidth=poolDim.y;
	
	int strideHeight=strideDim.x;
	int strideWidth=strideDim.y;
 
	for(int outputMap=0;outputMap<outputMaps;outputMap++){
		for(int outputY=0;outputY<outputHeight;outputY++){
			for(int outputX=0;outputX<outputWidth;outputX++){		
				float maxValue=-FLT_MAX;
				
				int yVal;
				int xVal;
				
				for(int yPool=0;yPool<poolHeight;yPool++){
					for(int xPool=0;xPool<poolWidth;xPool++){
						int idIn=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, outputMap, outputY*strideHeight+yPool, outputX*strideWidth+xPool);
						float value=inputs[idIn];
						
						if(value>maxValue){
							maxValue=value;
							yVal=yPool;
							xVal=xPool;
						}
						
						errorInput[idIn]=0;
					}
				}
				
				int idIn=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, outputMap, outputY*strideHeight+yVal, outputX*strideWidth+xVal);
				int idOut = calculateArrayID(outputMaps, outputHeight, outputWidth, batch, outputMap, outputY, outputX);
				errorInput[idIn] = errorOutput[idOut];
			}
		}
	}
}

/*
Above code in c language:

for(int batch=0;batch<batchSize;batch++{
	for(int outMap=0;outMap<outputMaps;outMap++){
		for(int inMap=0;inMap<inputMaps;inMap++){
			for(int y=0;y<height;y++){
				for(int x=0;x<width;x++){
					
				}
			}
		}
	}
}
*/
