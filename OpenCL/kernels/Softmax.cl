int calculateArrayID(int maps, int height, int width, int batch, int map, int y, int x){
	return (((batch) * maps + map) * height + y) * width + x;
}

__kernel void feedforward(__global const float* inputs, __global float* outputs, const int3 outputDim) {
 
    // Get the index of the current element to be processed
	int batch = get_global_id(0);
	int outputMap = get_global_id(1);
	
    if(outputMap==0){		//just for simplifications of the c++ code and the OpenCLLayer class
		int outputMaps=outputDim.x;
		int outputHeight=outputDim.y;
		int outputWidth=outputDim.z;
	
		float sum=0;
		
		for(int map=0;map<outputMaps;map++){
		
			for(int y=0;y<outputHeight;y++){
				for(int x=0;x<outputWidth;x++){
					int id=calculateArrayID(outputMaps, outputHeight, outputWidth, batch, map, y, x);
					float value=inputs[id];
						
					sum+=exp(value);					
				}
			}
		}
			
		for(int map=0;map<outputMaps;map++){
			for(int y=0;y<outputHeight;y++){
				for(int x=0;x<outputWidth;x++){
					int id=calculateArrayID(outputMaps, outputHeight, outputWidth, batch, map, y, x);
					
					outputs[id]=exp(inputs[id])/sum;
				}
			}
		}
	}
}

__kernel void errorComp(__global float* errorInputs, __global const float* errorOutputs, __global const float* inputs, const int3 outputDim){
	
    // Get the index of the current element to be processed
	int batch = get_global_id(0);
	
    float sum=0;
		
	int inputMaps=outputDim.x;
	int inputHeight=outputDim.y;
	int inputWidth=outputDim.z;
		
	for(int map=0;map<inputMaps;map++){
		for(int y=0;y<inputHeight;y++){
			for(int x=0;x<inputWidth;x++){
				int id=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, map, y, x);
				float value=inputs[id];
					
				sum+=exp(value);
			}
		}
	}
			
	for(int map=0;map<inputMaps;map++){
		for(int y=0;y<inputHeight;y++){
			for(int x=0;x<inputWidth;x++){
				int id=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, map, y, x);
				float inputValue=inputs[id];
				
				float a=exp(inputValue)/sum;
				float b=exp(2*inputValue)/(sum*sum);
				errorInputs[id]=(a-b)*errorOutputs[id];
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
