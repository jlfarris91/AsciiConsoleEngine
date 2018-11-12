#include "ArgumentDeducer.h"
#include <unordered_map>
#include "Method.h"
#include "Variant.h"

namespace Meta
{
namespace ArgumentDeducer
{

typedef std::pair<int, const Method *> MethodScore;
typedef std::set<MethodScore, bool(*)(const MethodScore&, const MethodScore&)> MethodScoreSet;

bool MethodScoreSort(const MethodScore &lhs, const MethodScore &rhs)
{
    return lhs.first < rhs.first;
}

class StrictArgumentDeducer : public IArgumentDeducer
{
public:
    const Method *DeduceMethod(const MethodCollection& methods, const VariantList& args) const override
    {
        auto scores = MethodScoreSet(MethodScoreSort);

        for (auto &&method : methods)
        {
            auto &&score = this->ScoreMethod(method, args);
            if (score != 0u)
            {
                scores.insert(MethodScore(score, method));            
            }
        }

        if (scores.size() == 0)
        {
            return nullptr;
        }

        return scores.begin()->second;
    }

    int ScoreMethod(const Method* method, const VariantList& args) const override
    {
        auto score = 0u;
        auto &&params = method->Parameters;

        if (params.size() == args.size())
        {
            score += 10;
        }

        auto &&arg = args.begin();
        for (auto &&param : params)
        {
            if (param.Type->IsAssignableFrom(arg->Type))
            {
                return 0u;
            }
            score += 10;
        }

        return score;
    }
};

//class LooseArgumentDeducer : public IArgumentDeducer
//{
//public:
//    Method* DeduceMethod(const MethodCollection& methods, const VariantList& args) const override
//    {
//
//        for (auto &&method : methods)
//        {
//            auto &&score = this->ScoreMethod(method, args);
//        }
//        return nullptr;
//    }
//
//    size_t ScoreMethod(const Method* method, const VariantList& args) const override
//    {
//        auto score = 0u;
//        auto &&params = method->Parameters;
//        if (params.size() == args.size())
//        {
//            score = 10;
//        }
//
//
//    }
//};


IArgumentDeducer *Strict = new StrictArgumentDeducer();
IArgumentDeducer *Loose = new StrictArgumentDeducer();

}
}