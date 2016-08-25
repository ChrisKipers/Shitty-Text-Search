//
// Created by chris on 8/24/16.
//

#include "SnippitCreator.h"

#include <set>
#include <cfloat>

#include <boost/algorithm/string/join.hpp>

const int MAX_SNIPPET_LENGTH = 30;
const float HIT_SCORE = 1;
const float MISS_SCORE = -.1;

inline float getScoreForHit(const bool& hit) {
    return hit ? HIT_SCORE : MISS_SCORE;
}


SnippitCreator::SnippitCreator(TextProcessor *textProcessor) : textProcessor(textProcessor){}

string SnippitCreator::createSnippet(const string &content, const string &query) const {
    vector<string> contentTokens = textProcessor->process_text(content);
    vector<string> queryTokens = textProcessor->process_text(query);
    set<string> uniqueQueryTokens(queryTokens.begin(), queryTokens.end());


    vector<bool> positionHit(contentTokens.size());
    for (int i = 0; i < contentTokens.size(); i++) {
        positionHit[i] = uniqueQueryTokens.find(contentTokens[i]) != uniqueQueryTokens.end();
    }

    int snippetLength = min<int>(contentTokens.size(), MAX_SNIPPET_LENGTH);
    int maxWindowPosition = getMaxWindowStartPosition(positionHit);
    return buildSnippet(contentTokens, positionHit, maxWindowPosition, maxWindowPosition + snippetLength);
}

int SnippitCreator::getMaxWindowStartPosition(const vector<bool> &hits) const {
    int snippetLength = min<int>(hits.size(), MAX_SNIPPET_LENGTH);
    vector<float> scores(hits.size() - snippetLength + 1);
    float initScore = 0;
    for (int i = 0; i < snippetLength; i++) {
        initScore += hits[i] ? HIT_SCORE : MISS_SCORE;
    }
    scores[0] = initScore;

    for (int i = 1; i < scores.size(); i++) {
        float previousScore = scores[i - 1];
        scores[i] = previousScore - getScoreForHit(hits[i - 1]) + getScoreForHit(hits[i + snippetLength]);
    }

    float highScore =  -FLT_MAX;
    int maxPos = -1;

    for (int i = 0; i < scores.size(); i++) {
        if (highScore < scores[i]) {
            highScore = scores[i];
            maxPos = i;
        }
    }

    return maxPos;
}

string SnippitCreator::buildSnippet(const vector<string> &contentTokens, const vector<bool> &hits, int startPos,
                                    int endPost) const {
    vector<string> enhancedTokens;

    for (int i = startPos; i < endPost; i++) {
        string enhancedToken;
        if (hits[i]) {
            enhancedToken = "<b>" + contentTokens[i] + "</b>";
        } else {
            enhancedToken = contentTokens[i];
        }
        enhancedTokens.push_back(enhancedToken);
    }

    return boost::algorithm::join(enhancedTokens, " ");
}
