#include <iostream>
#include <algorithm>
#include <cstddef>
#include <string>

class AudioBuffer{
private:
    float* samples;
    size_t sampleCount;

public:
    // Constructo: Allocates dynamic memory on the heap
    AudioBuffer(size_t count, float initalSampleValue = 0.0f)
    : sampleCount(count), samples(new float[count]){
        for(size_t i = 0; i < sampleCount; ++i){
            samples[i] = initalSampleValue;
        }
    }


    // Destructor: Cleans up heap allocation
    ~AudioBuffer(){
        delete[] samples;
    }

    // Deep Copy Constructo
    AudioBuffer(const AudioBuffer& other):
    sampleCount(other.sampleCount), samples(new float[other.sampleCount]){
        for(size_t i = 0; i < sampleCount; ++i){
            samples[i] = other.samples[i];
        }
    }

    // Copy Assignment Operator
    AudioBuffer& operator=(const AudioBuffer& other){
        if(this != &other){
            delete[] samples; // Clean existing memory
            sampleCount = other.sampleCount;
            samples = new float[sampleCount];
            for(size_t i = 0; i < sampleCount; ++i){
                samples[i] = other.samples[i];
            }
        }
        return *this;
    }
    size_t getSampleCount() const {return sampleCount;}

    // Accessor returning a reference to allow in-place modification
    float& at(size_t index){
        return samples[index];
    }

    // Const overload for read-only access
    const float& at(size_t index) const{
        return samples[index];
    }

    void printBuffer(const std::string& name) const{
        std::cout << name <<": [";
        for(size_t i = 0; i < sampleCount; ++i){
            std::cout << samples[i] << "";
        }
        std::cout << "]\n";
    }

};


// 2. ABSTRACT BASE CLASS: AudioEffect

class AudioEffect {
public:
    //Pure Virtual method
    virtual void process(AudioBuffer& buffer) = 0;

    // Virtaul destructor ensure dervied object clean up safely
    virtual ~AudioEffect() = default;
};

// 3. CONCRETE EFFECT 1: GainEffect (Volume Scaler)
class GainEffect : public AudioEffect{
private:
    float gainFactor;
public:
    explicit GainEffect(float gain) : gainFactor(gain){};

    void process(AudioBuffer& buffer) override {
        for(size_t i = 0; i < buffer.getSampleCount(); ++i){
            buffer.at(i) *= gainFactor;
        }
    }
};

// Concrete effect 2: Clipping effect

class ClippingEffect : public AudioEffect {
private:
    float threshold;

public:
    explicit ClippingEffect(float limit) : threshold(limit) {}

    void process(AudioBuffer& buffer) override {
        for (size_t i = 0; i < buffer.getSampleCount(); ++i) {
            float currentSample = buffer.at(i);
            if (currentSample > threshold) {
                buffer.at(i) = threshold;
            } else if (currentSample < -threshold) {
                buffer.at(i) = -threshold;
            }
        }
    }
};