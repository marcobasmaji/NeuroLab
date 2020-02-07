import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class WeightsAndBiasesCreator{

	private final static int outputMaps=2;		//for dense layer number of output neurons
	private final static int inputMaps=2;		//for dense layer number of input neurons
	private final static int kernelHeight=2;	//for dense layer 1
	private final static int kernelWidth=2;		//for dense layer 1
	
	private static final int seed=12345;		//have to be changed for every layer, does not matter what seed you use
	private static final Random r=new Random(seed);
	
	public static void main(String args[]) {
		
		float[]weights=createWeights();
		float[]biases= createBiases();
		
		save(weights, "dirWhereWeightsFileShouldBeSaved");	//TODO
		save(biases, "dirWhereBiasesFileShouldBeSaved");	//TODO
	}
	
	private static float[] createWeights(){
		int inputNeurons=inputMaps*kernelHeight*kernelWidth;
		float []weights=new float[outputMaps*inputNeurons];
		
		for(int outputMap=0;outputMap<outputMaps;outputMap++){
			for(int inputMap=0;inputMap<inputMaps;inputMap++){
				for(int kernelY=0;kernelY<kernelHeight;kernelY++){
					for(int kernelX=0;kernelX<kernelWidth;kernelX++){
						weights[calculateId(outputMap, inputMap, kernelY, kernelX)]=(float)(r.nextGaussian()/Math.sqrt((float)inputNeurons));
					}
				}
			}
		}
		
		return weights;
	}
	
	private static float[] createBiases(){
		float[]biases=new float[outputMaps];
		
		for(int i=0;i<outputMaps;i++){
			biases[i]=(float)r.nextGaussian();
		}
		
		return biases;
	}

	private static void save(float[]values, String dir){
		try {
			BufferedWriter writer = new BufferedWriter(new FileWriter(dir));
			
			StringBuffer buffer=new StringBuffer();
			
			for(int i=0;i<values.length;i++){
				buffer.append(values[i]+" ");
			}
			writer.write(buffer.toString().trim());
			
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private static int calculateId(int outputMap, int inputMap, int kernelY, int kernelX){
		return calculateWeightID(inputMaps, kernelHeight, kernelWidth, outputMap, inputMap, kernelY, kernelX);
	}
	private static int calculateWeightID(int inputMaps, int inputHeight, int inputWidth, int outputNeuron, int inputMap, int y, int x){
		return (((outputNeuron) * inputMaps + inputMap) * inputHeight + y) * inputWidth + x;
	}
}
