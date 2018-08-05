/**
 *  @file    Sequence.cpp
 *  @author  Corey Ford
 *  @date    17/07/2018
 *  @version 1.0
 *
 *  @brief Implementation for @see sequence.hpp
 *
 *  @section DESCRIPTION
 *
 *  Implementation for @see sequence.hpp
 *
 */

#include <midi/sequence.hpp>

namespace pcaudio{
namespace midi{
        
    Sequence::Sequence(const int sequenceSize){
        // fill the vector with the correct number of dummy sys ex messages
        for(int i = 0; i < sequenceSize; i++){
            Step messageBundle;
            messageBundle.push_back(dummySysEx);
            sequence.push_back(messageBundle);
        }
    }
    
    Sequence::~Sequence(){}
    
    Sequence::Sequence(const Sequence & rhs){
        if(this != &rhs){
            sequence = rhs.getSequence();
        }
    }
    
    Sequence& Sequence::operator =(const Sequence & rhs){
        if(this != &rhs){
            sequence = rhs.getSequence();
        }
        return *this;
    }
    
    void Sequence::addMessageToStep(const Message & message, const int step){
        
        assert("Sequence must be within range!" && step > -1 && step < sequence.size());
        
        Step messageBundle = sequence[step]; // get the current messages in step
        messageBundle.push_back(message); // add this message
        sequence[step] = messageBundle; // assign it back
        
    }
    
    void Sequence::removeMessageFromStep(const Message & message, const int step){
        
        assert("Sequence must be within range!" && step > -1 && step < sequence.size());

        bool found = false;
        Step messageBundle = sequence[step]; // get the current messages in step
        for(Message messageSearched : messageBundle)
        {
            if(messageSearched == message){ // if the message is found ...
                found = true;
                // ... remove it!
                messageBundle.erase(std::remove(messageBundle.begin(),
                                                messageBundle.end(),
                                                message),
                                        messageBundle.end());
                sequence[step] = messageBundle; // update original sequence.
            }
        }
        
        if(found == false)
            assert("Message to be removed wasn't found in this step!" && 0);
        
    }
    
    std::vector<Step> Sequence::getSequence() const{
        return sequence;
    }
    
    int Sequence::size() const{
        return sequence.size();
    }
    
    void Sequence::reset(){
        int seqSize = sequence.size(); // make note of containter size
        
        sequence.clear();
        
        // fill the vector with the correct number of dummy sys ex messages
        for(int i = 0; i < seqSize; i++){
            Step messageBundle;
            messageBundle.push_back(dummySysEx);
            sequence.push_back(messageBundle);
        }
    }

}// namespace midi
}// namespace pcaudio
