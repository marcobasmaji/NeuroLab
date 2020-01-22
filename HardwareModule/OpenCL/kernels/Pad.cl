
int calculateArrayID(int outputMaps, int height, int width, int batch, int outputMap, int y, int x){
	return (((batch) * outputMaps + outputMap) * height + y) * width + x;
}


__kernel void feedforward(__global const float* inputs, __global float* outputs, const int3 inputDim, const int2 padDim) {
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
	int outputMap = get_global_id(1);
	
	int inputWidth=inputDim.z;
	int inputHeight=inputDim.y;
	int inputMaps=inputDim.x;
	
	int padHeight=padDim.x;
	int padWidth=padDim.y;
 
	for(int y=0;y<inputHeight;y++){
		for(int x=0;x<inputWidth;x++){
			int idIn = calculateArrayID(inputMaps, inputHeight, inputWidth, batch, outputMap, y, x);
			int idOut = calculateArrayID(inputMaps, inputHeight+2*padHeight, inputWidth+2*padWidth, batch, outputMap, y+padHeight, x+padWidth);
			
			outputs[idOut] = inputs[idIn];
		}
	}
}

__kernel void errorComp(__global float* errorInput, __global const float* errorOutput, __global const float* inputs, const int3 inputDim, const int2 padDim) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
	
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
	
	int padHeight=padDim.x;
	int padWidth=padDim.y;
 
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int y=0;y<inputHeight;y++){
			for(int x=0;x<inputWidth;x++){
				int idIn = calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, y, x);
				int idOut = calculateArrayID(inputMaps, inputHeight+2*padHeight, inputWidth+2*padWidth, batch, inputMap, y+padHeight, x+padWidth);
				
				errorInput[idIn] = errorOutput[idOut];
			}
		}
	}
}


/*
Above code in c language:

for(int batch=0;batch<batchSize;batch++{
	for(int outoutputMap=0;outoutputMap<outputoutputMaps;outoutputMap++){
		for(int inoutputMap=0;inoutputMap<inputoutputMaps;inoutputMap++){
			for(int y=0;y<height;y++){
				for(int x=0;x<width;x++){
					
				}
			}
		}
	}
}
*/
