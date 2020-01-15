
int calculateArrayID(int maps, int height, int width, int batch, int map, int y, int x){
	return (((batch) * maps + map) * height + y) * width + x;
}

int calculateWeightID(int inputMaps, int height, int width, int outputMap, int inputMap, int y, int x){
	return (((outputMap) * inputMaps + inputMap) * height + y) * width + x;
}

__kernel void feedforward(__global const float* inputs, __global float* outputs, __global const float* weights, __global const float* biases, const int3 inputDim, const int3 outputDim, const int2 kernelDim, const int2 strideDim) {

    // Get the index of the current element to be processed
    int batch = get_global_id(0);
	int outputMap = get_global_id(1);
	
	int outputMaps=outputDim.x;
	int outputHeight=outputDim.y;
	int outputWidth=outputDim.z;
	
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
	
	int kernelHeight=kernelDim.x;
	int kernelWidth=kernelDim.y;
	
	int strideHeight=strideDim.x;
	int strideWidth=strideDim.y;
	
	for(int outputY=0;outputY<outputHeight;outputY++){
		for(int outputX=0;outputX<outputWidth;outputX++){
			float sum=0;
			
			for(int inputMap=0;inputMap<inputMaps;inputMap++){
				for(int kernelY=0;kernelY<kernelHeight;kernelY++){
					for(int kernelX=0;kernelX<kernelWidth;kernelX++){
						int inputY=strideHeight*outputY+kernelY;
						int inputX=strideWidth*outputX+kernelX;
					
						int idWeight=calculateWeightID(inputMaps, kernelHeight, kernelWidth, outputMap, inputMap, kernelY, kernelX);
						int idInput=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, inputY, inputX);
					
						float input=inputs[idInput];
						float weight=weights[idWeight];
						sum+=weight*input;
					}
				}
			}
			
			sum+=biases[outputMap];
			int outputId=calculateArrayID(outputMaps, outputHeight, outputWidth, batch, outputMap, outputY, outputX);
			outputs[outputId]=sum;
		}
	}
}

__kernel void errorComp(__global float* errorInput, __global const float* errorOutput, __global const float* inputs, __global const float* weights, const int3 inputDim, const int3 outputDim, const int2 kernelDim, const int2 strideDim) {
 
    // Get the index of the current element to be processed
    int batch = get_global_id(0);
 
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
 
	int outputMaps=outputDim.x;
	int outputHeight=outputDim.y;
	int outputWidth=outputDim.z;
	
	int kernelHeight=kernelDim.x;
	int kernelWidth=kernelDim.y;
	
	int strideHeight=strideDim.x;
	int strideWidth=strideDim.y;
 
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int inputY=0;inputY<inputHeight;inputY++){
			for(int inputX=0;inputX<inputWidth;inputX++){
				int inputID=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, inputY, inputX);
				errorInput[inputID]=0;
			}
		}
	}
	
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int outputMap=0;outputMap<outputMaps;outputMap++){
			for(int outputY=0;outputY<outputHeight;outputY++){
				for(int outputX=0;outputX<outputWidth;outputX++){
					int idOutput=calculateArrayID(outputMaps, outputHeight, outputWidth, batch, outputMap, outputY, outputX);
					float error=errorOutput[idOutput];
					
					for(int kernelY=0;kernelY<kernelHeight;kernelY++){
						for(int kernelX=0;kernelX<kernelWidth;kernelX++){
							int inputY=outputY*strideHeight+kernelY;
							int inputX=outputX*strideWidth+kernelX;
						
							int inputID=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, inputY, inputX);
							int weightID=calculateWeightID(inputMaps, kernelHeight, kernelWidth, outputMap, inputMap, kernelY, kernelX);
								
							float weight=weights[weightID];
							errorInput[inputID]=error*weight;
						}
					}
				}
			}
		}
	}
}

__kernel void weightsUpdate(const float learningRate, __global const float* inputs, __global const float* errorOutput, __global float* weights, __global float* biases, const int batchSize, const int3 outputDim, const int3 inputDim, const int2 kernelDim, const int2 strideDim){
	int outputMap=get_global_id(0);
	
	int outputMaps=outputDim.x;
	int outputHeight=outputDim.y;
	int outputWidth=outputDim.z;
 
	int inputMaps=inputDim.x;
	int inputHeight=inputDim.y;
	int inputWidth=inputDim.z;
	
	int kernelHeight=kernelDim.x;
	int kernelWidth=kernelDim.y;
	
	int strideHeight=strideDim.x;
	int strideWidth=strideDim.y;
	
	//update weights
	for(int inputMap=0;inputMap<inputMaps;inputMap++){
		for(int kernelY=0;kernelY<kernelHeight;kernelY++){
			for(int kernelX=0;kernelX<kernelWidth;kernelX++){
				float sum=0;
				
				for(int batch=0;batch<batchSize;batch++){
					for(int outputY=0;outputY<outputHeight;outputY++){
						for(int outputX=0;outputX<outputWidth;outputX++){
							int inputY=strideHeight*outputY+kernelY;
							int inputX=strideWidth*outputX+kernelX;
						
							int idOutput=calculateArrayID(outputMaps, outputHeight, outputWidth, batch, outputMap, outputY, outputX);
							int idInput=calculateArrayID(inputMaps, inputHeight, inputWidth, batch, inputMap, inputY, inputX);
							
							float error=errorOutput[idOutput];
							float input=inputs[idInput];
								
							sum+=error*input;
						}
					}
				}
				
				sum/=(float)(outputHeight*outputWidth*batchSize);
				int idKernel=calculateWeightID(inputMaps, kernelHeight, kernelWidth, outputMap, inputMap, kernelY, kernelX);
				weights[idKernel]-=learningRate*sum;
			}
		}
	}
	
	
	//update bias
	float sum=0;
	for(int batch=0;batch<batchSize;batch++){
		for(int outputY=0;outputY<outputHeight;outputY++){
			for(int outputX=0;outputX<outputWidth;outputX++){
				int idOutput=calculateArrayID(outputMaps, outputHeight, outputWidth, batch, outputMap, outputY, outputX);
				sum+=errorOutput[idOutput];
			}
		}
	}
	sum/=(float)(outputHeight*outputWidth*batchSize);
	biases[outputMap]-=learningRate*sum;
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
