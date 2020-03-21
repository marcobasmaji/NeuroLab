#include "PretrainedNN.h"

PretrainedNN::PretrainedNN()
{

}

void PretrainedNN::classify()
{
    cerr<<"PNN nn "<<currentNN<<endl;

    // thread per hardware. Then set images in an openVinoEnv on this hardware
    results.clear();
    vector<thread> threads;
    for(int i = 0; i < (int) envs.size(); i++){
        threads.push_back(thread(&PretrainedNN::threading, this, envs[i]));
    }
    for (auto& thread : threads) thread.join();
    // erst nach join get reuslts
    for(auto & ov : envs)
    {
        vector<Result> envResults = ov->getResults();
        this->results.insert(results.end(), envResults.begin(), envResults.end());
    }

    for(auto & ov : envs)
    {
        delete ov;
    }
    core->~Core();
}

void PretrainedNN::threading(OpenVinoEnv *env){
    vector<Result> intermidiate;
    env->classify();
}

vector<Result> PretrainedNN::getResults()
{
    return this->results;
}


void PretrainedNN::setImagePaths(vector<string> imagePaths)
{
    allImages = imagePaths;
}

void PretrainedNN::setPlatforms(vector<pair<string, int> > platforms)
{
    this->core = new InferenceEngine::Core();
    envs.clear();
    int count = 0;
    vector<string> imagesToDeploy;
    for(pair<string, int> dist : platforms){
        OpenVinoEnv *env;
        env = new OpenVinoEnv();
        env->setDevice(dist.first);
        env->chooseNeuralNet(currentNN);
        env->setCore(core);
        int dif = dist.second + count;
        imagesToDeploy.clear();
        for(int i = count; i < dif && (int)allImages.size() >= dif; i++)
        {

            imagesToDeploy.push_back(allImages.at(i));

        }
        count += dist.second;

        env->setImageNames(imagesToDeploy);

        envs.push_back(env);
    }
}

void PretrainedNN::setNerualNet(string nn)
{
    currentNN = nn;
}


