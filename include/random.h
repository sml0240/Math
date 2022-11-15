#pragma once
#include <random>
#include <string>


class RandomGenerator
{
private:
    std::default_random_engine engine;
    std::string m_Seed;
    bool is_ready = false;

public:
    RandomGenerator()
    {
        m_Seed = std::to_string(1337);
        std::seed_seq seq (m_Seed.begin(), m_Seed.end());
        engine.seed(seq);
    };

    RandomGenerator(std::string &seed)
        : is_ready(true), m_Seed(seed)
        {
            std::seed_seq seq (m_Seed.begin(), m_Seed.end());
            //m_Seed = seq;
            
            engine.seed(seq);
        };

    RandomGenerator(uint32_t seed)
       : is_ready(true), m_Seed(std::to_string(seed))
        {
            
            std::seed_seq seq (m_Seed.begin(), m_Seed.end());
            engine.seed(seq);
        }; 

    ~RandomGenerator(){};
    
    inline void Seed(std::string &seed) { std::seed_seq seq (seed.begin(), seed.end()); engine.seed(seq); };
    inline void Seed(uint32_t seed) { engine.seed(seed);};

    inline float Randfloat32() { std::uniform_real_distribution<double> dist(0.0, 1.0); return (float)dist(engine); };
    inline int32_t Randint32() { std::uniform_int_distribution<int32_t> dist(-2147483647, 2147483647); return dist(engine); };
    inline uint32_t Randuint32() {std::uniform_int_distribution<uint32_t> dist(0, 4294967295); return dist(engine); }; // max 2,147,483,647 // min -2,147,483,648

    template <typename Itype>
    Itype RandInt(const Itype &min, const Itype &max)
    {
        std::uniform_int_distribution<Itype> dist(min, max); return dist(engine);
    }

    inline int RandRangeInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    };
    // TODO
    // im casting to double to use uni_real_dist 
    // change to proper float func
    inline float RandRangeFloat(float min, float max)
    {
        std::uniform_real_distribution<double> dist((double)min, (double)max);
        return (float)dist(engine);
    }
};