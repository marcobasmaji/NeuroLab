#include <NeuroLabNet.h> 

// constuctor
NeuroLabNet::NeuroLabNet(){
	// do nothing?
}

void NeuroLabNet::init() {
    // the division (imageSize-filterSize)/stride must be an integer
	// image input is i.e. 106x106x3 so output image is (106- filterHeight)/ stride +1 with depth = numFilters. 
	// so i chose (105 - 6) / 3 +1 = 34
	// and 50 filters

	 ConvolutionLayer conv1(105,105,3,6,6,3,3,50);
	 // now the non linear function
	 ReLULayer relu1(34,34,50);
	 MaxPoolingLayer maxP1(34,34,50,2,2,2,2);
	 // output is (34 -2) / 2 + 1 = 17 
	 ConvolutionLayer conv2(17,17,50,3,3,2,2,100);
	 // output is (17-3) / 2 +1 = 8 , -> 8x8x100
	 ReLULayer relu2(8,8,100);
	 MaxPoolingLayer maxP2(8,8,100,2,2,2,2);
	 // output is (8-2)/2 +1 = 4 
	 // 4x4x100
	 DenseLayer dense(4,4,100,100);
	 // output is an array with the length 100
	 SoftmaxLayer soft(100);
	 Loss loss(100);
	 layers.push_front(conv1);
	 layers.push_front(relu1);
	 layers.push_front(maxP1);
	 layers.push_front(conv2);
	 layers.push_front(relu2);
	 layers.push_front(maxP2);
	 layers.push_front(dense);
	 layers.push_front(soft);
	 this->lossFunction = loss;



}

void NeuroLabNet::classify() {
	// TODO, parameter need to be coordinated with Jens
	conv1.forwardPass();
	relu1.forwardPass();
	// and so on

}

void NeuroLabNet::train() {
	// here foward then backward

}

void executeTransferLearning() {
	// no idea .. yet

}