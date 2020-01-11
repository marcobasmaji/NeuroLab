int calculateArrayID(int maps, int height, int width, int batch, int map, int y, int x){
	return (((batch) * maps + map) * height + y) * width + x;
}

int calculateWeightID(int inputMaps, int inputHeight, int inputWidth, int outputNeuron, int inputMap, int y, int x){
	return (((outputNeuron) * inputMaps + inputMap) * inputHeight + y) * inputWidth + x;
}

__kernel void feedforward(__global const float* inputs, __global float* outputs, __global const float* weights, __global const float* biases, const int3 inputDim, const int outputNeurons) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
	int outputNeuron = get_global_id(1);
 
	float sum=0;
 
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
 
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int y=0;y<inputHeight;y++){
			for(int x=0;x<inputWidth;x++){
				int idInput=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, y, x);
				int idWeight=calculateWeightID(inputMaps, inputHeight, inputWidth, outputNeuron, inputMap, y, x);
			
				float input=inputs[idInput];
				sum+=weights[idWeight]*input;
			}
		}
	}
	
	float bias=biases[outputNeuron];
	outputs[outputNeuron]=sum+bias;
}

__kernel void errorComp(__global float* errorInput, __global const float* errorOutput, __global const float* inputs, __global const float* weights, const int3 inputDim, const int outputNeurons) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
 
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
 
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int y=0;y<inputHeight;y++){
			for(int x=0;x<inputWidth;x++){
				float sum=0;
				
				for(int outputNeuron=0;outputNeuron<outputNeurons;outputNeuron++){
					int idOutput=calculateArrayID(outputNeurons, 1, 1, batch, outputNeuron, 0, 0);
					int idWeight=calculateWeightID(inputMaps, inputHeight, inputWidth, outputNeuron, inputMap, y, x);
					
					
					float weight=weights[idWeight];
					sum+=weight*errorOutput[idOutput];
					
				}
				
				int id=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, y, x);
				errorInput[id]=sum;
			}
		}
	}	
}

__kernel void weightsUpdate(const float learningRate, __global const float* inputs, __global const float* errorOutput, __global float* weights, __global float* biases, const int batchSize, const int outputNeurons, const int3 inputDim){
	int outputNeuron = get_global_id(0);
	
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
	
	//update weights
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int y=0;y<inputHeight;y++){
			for(int x=0;x<inputWidth;x++){
				
				int idWeight=calculateWeightID(inputMaps, inputHeight, inputWidth, outputNeuron, inputMap, y, x);
				float sum=0;
				
				for(int batch=0;batch<batchSize;batch++){
					
					int idInput=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, y, x);					
					int idOutput=calculateArrayID(outputNeurons, 1, 1, batch, outputNeuron, 0, 0);
					
					sum+=inputs[idInput]*errorOutput[idOutput];					
				}
				
				sum/=(float)batchSize;
				weights[idWeight]-=learningRate*sum;
			}
		}
	}
	
	//update biases
	float sum=0;
	for(int batch=0;batch<batchSize;batch++){
		int idOutput=calculateArrayID(outputNeurons, 1, 1, batch, outputNeuron, 0, 0);
		sum+=errorOutput[idOutput];
	}
	sum/=(float)batchSize;
	biases[outputNeuron]-=sum*learningRate;
	
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
