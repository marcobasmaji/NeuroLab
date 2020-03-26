#include "PretrainedNN.h"

PretrainedNN::PretrainedNN()
{

}

void PretrainedNN::classify()
{
    cerr<<"PNN nn "<<currentNN<<endl;

    // thread per hardware. Then set images in an openVinoEnv on this hardware
    results.clear();
    int number_threads = envs.size();
    thread threads[number_threads];
    for(int i = 0; i < number_threads; i++){
        threads[i] = thread(&PretrainedNN::threading, this, envs[i]);
        cerr<<"Threads created"<<endl;
    }
    for (int i = 0; i < number_threads; i++) {
        threads[i].join();
    }
    cerr<<"Threads joined"<<endl;

    // erst nach join get reuslts
    for(int i = 0; i < number_threads; i++)
    {
        vector<Result> envResults = envs[i]->getResults();
        this->results.insert(results.end(), envResults.begin(), envResults.end());
    }

    for(int i = 0; i < number_threads; i++)
    {
        delete envs[i];
    }
    envs.clear();

    //core->~Core();
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
//    this->core = new InferenceEngine::Core();
    envs.clear();
    int count = 0;
    vector<string> imagesToDeploy;
    for(pair<string, int> dist : platforms){
        InferenceEngine::Core envCore;
        OpenVinoEnv *env;
        env = new OpenVinoEnv();
        env->setDevice(dist.first);
        env->chooseNeuralNet(currentNN);
        env->setCore(envCore);
        int dif = dist.second + count;
        imagesToDeploy.clear();
        for(int i = count; i < dif && (int)allImages.size() >= dif; i++)
        {

            imagesToDeploy.push_back(allImages.at(i));

        }
        count += dist.second;

        env->setImageNames(imagesToDeploy);
        cerr<<"env for distribution "<<dist.first<<", "<<dist.second<<"images to deploy size "<<imagesToDeploy.size()<<endl;
        envs.push_back(env);
    }
}

void PretrainedNN::setNeuralNet(string nn)
{
    currentNN = nn;
}
