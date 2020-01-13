int calculateArrayID(int maps, int height, int width, int batch, int map, int y, int x){
	return (((batch) * maps + map) * height + y) * width + x;
}

__kernel void feedforward(__global const float* inputs, __global float* outputs, const int3 outputDim) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
	int outputMap = get_global_id(1);
	
	int outputWidth=outputDim.z;
	int outputHeight=outputDim.y;
	int outputMaps=outputDim.x;
 
	for(int y=0;y<outputHeight;y++){
		for(int x=0;x<outputWidth;x++){		
			int id = calculateArrayID(outputMaps, outputHeight, outputWidth, batch, outputMap, y, x);
			
			outputs[id] = fmax(0,inputs[id]);
		}
	}
}

__kernel void errorComp(__global float* errorInput, __global const float* errorOutput, __global const float* inputs, const int3 inputDim) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
 
	int inputWidth=inputDim.z;
	int inputHeight=inputDim.y;
	int inputMaps=inputDim.x;
 
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int y=0;y<inputHeight;y++){
			for(int x=0;x<inputWidth;x++){
				int id = calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, y, x);
				
				if(inputs[id]<=0)	errorInput[id] = 0;
				else				errorInput[id] = errorOutput[id];
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
